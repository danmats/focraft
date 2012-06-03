/* 
 * @isoeng.cpp 
 *
 * isometric engine
 *
 * author: Dan Matsuoka
 */

#include "isoeng.h"

Isoeng::Isoeng(char* caption) {
	int img_init;

	srand(time(NULL));
	m_x = m_y = x_offset = y_offset = 0;

	/*	initialize SDL`*/
	putenv("SDL_VIDEO_WINDOW_POS");
	putenv("SDL_VIDEO_CENTERED=1");
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		err = new char[256];
		sprintf(err, "Unable to initialize SDL: %s", SDL_GetError());
		throw CException("isoeng.cpp", err);
	}
	
	/* create main window SDL drawing surface */
	window_main = SDL_SetVideoMode(WM_WIDTH, WM_HEIGHT, 32, SDL_DOUBLEBUF);
	if(window_main == NULL) {
		err = new char[256];
		sprintf(err, "Unable to set %dx%d video mode: %s", WM_WIDTH, WM_HEIGHT, SDL_GetError());
		throw CException("isoeng.cpp", err);
	}
	SDL_WM_SetCaption(caption, caption);

	/* initialize SDL_Image */
	img_init = IMG_Init(IMG_INIT_PNG);
	if((img_init & IMG_INIT_PNG) != IMG_INIT_PNG) {
		err = new char[256];
		sprintf(err, "Failed to initialize PNG support: %s", IMG_GetError());
		throw CException("isoeng.cpp", err);
	}

	loadCursorImages();
	loadTileImages();
	IMG_Quit();

	createSurfaces();
	alive = true;
}

Isoeng::~Isoeng() {
	int i;

	delete err;
	delete cursors;
	for(i = 0; i < TILE_SHEETS; i++) {
		SDL_FreeSurface(tile_sheets[i]);
	}
	delete[] tile_sheets;
	for(i = 0; i < X_TILES; i++) {
		delete[] tile[i];
	}
	delete[] tile;
	SDL_Quit();
}

void Isoeng::run() {
	SDL_Event event;

	if(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				alive = false;
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_ESCAPE:
						alive = false;
						break;

					case SDLK_LCTRL:
					case SDLK_RCTRL:
						SDL_ShowCursor(SDL_DISABLE);
						cursor_style = 0;
						break;

					default:
						break;
				}
				break;

			case SDL_KEYUP:
				switch(event.key.keysym.sym) {
					case SDLK_LCTRL:
					case SDLK_RCTRL:
						SDL_ShowCursor(SDL_ENABLE);
						break;

					default:
						break;
				}
				break;

			case SDL_MOUSEMOTION:
				if(cursor_style) {
					x_offset += event.motion.xrel;
					y_offset += event.motion.yrel;
				} else if(m_x && m_y) {
					SDL_GetMouseState(&c_x, &c_y);
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				if(!SDL_ShowCursor(SDL_QUERY)) {
					cursor_style = 1;
				} else {
					SDL_GetMouseState(&m_x, &m_y);
					c_x = m_x + 1;
					c_y = m_y + 1;
				}
				break;

			case SDL_MOUSEBUTTONUP:
				cursor_style = 0;
				m_x = m_y = 0;
				break;
		}
	}

	renderBackground();

	if(!SDL_ShowCursor(SDL_QUERY)) {
		grabBackground();
	} else if(m_x && m_y) {
		selectAssets();
	}

	SDL_Flip(window_main);
}

void Isoeng::loadCursorImages() {
	char* cursor_filename = "images/cursors.png";
	SDL_Surface* load_surface = NULL;

	load_surface = IMG_Load(cursor_filename);
	if(load_surface == NULL) {
		err = new char[256];
		sprintf(err, "Failed to load cursors: %s", cursor_filename);
		throw CException("isoeng.cpp", err);
	}
	cursors = SDL_DisplayFormatAlpha(load_surface);
	SDL_FreeSurface(load_surface);
	cursor_style = 0;
}

void Isoeng::loadTileImages() {
	int i, j;
	SDL_Surface* load_surface = NULL;
	char* tile_filenames[TILE_SHEETS] = {
		"images/my_tile.png",
		"images/tile.png",
		"images/tile2.png",
		"images/tile3.png",
	};

	tile_sheets = new SDL_Surface*[TILE_SHEETS];
	for(i = 0; i < TILE_SHEETS; i++) {
		load_surface = IMG_Load(tile_filenames[i]);
		if(load_surface == NULL) {
			err = new char[256];
			sprintf(err, "Failed to load image: %s", tile_filenames[i]);
			throw CException("isoeng.cpp", err);
		}
		tile_sheets[i] = SDL_DisplayFormatAlpha(load_surface);
	}
	SDL_FreeSurface(load_surface);

	tile = new Tile**[X_TILES];
	for(i = 0; i < X_TILES; i++) {
		tile[i] = new Tile*[Y_TILES];
		for(j = 0; j < Y_TILES; j++) {
			tile[i][j] = new Tile(i, j);
//			tile[i][j] = new Tile(i, j, 0, 0, (rand() % 3));
		}
	}
}

void Isoeng::createSurfaces() {
	bool even_row = false;
	int i, j;
	SDL_Rect src, dest;

	area_select = SDL_CreateRGBSurface(SDL_SRCALPHA, WM_WIDTH, WM_HEIGHT, 32, window_main->format->Rmask, window_main->format->Gmask, window_main->format->Bmask, 0);
	SDL_SetAlpha(area_select, SDL_SRCALPHA, 42);
	SDL_FillRect(area_select, NULL, SDL_MapRGB(window_main->format, 0, 255, 32));

	background = SDL_CreateRGBSurface(SDL_SRCALPHA, MAP_WIDTH, MAP_HEIGHT, 32, window_main->format->Rmask, window_main->format->Gmask, window_main->format->Bmask, 0);
	src.w = TILE_WIDTH;
	src.h = TILE_HEIGHT;
	for(j = 0; j < Y_TILES; j++) {
		for(i = 0; i < X_TILES; i++) {
			src.x = tile[i][j]->image_x;
//			src.x = (rand() % 2) * 32;
			src.y = tile[i][j]->image_y;
			dest.x = (16 * even_row) + (i * 32);
			dest.y = j * 8;
			SDL_BlitSurface(tile_sheets[tile[i][j]->sheet], &src, background, &dest);
		}
		even_row = !even_row;
	}
}

void Isoeng::renderBackground() {
	SDL_Rect dest;

	SDL_FillRect(window_main, NULL, 0);
	dest.x = x_offset;
	dest.y = y_offset;
	SDL_BlitSurface(background, NULL, window_main, &dest);
}

void Isoeng::grabBackground() {
	SDL_Rect src, dest;

	SDL_GetMouseState(&c_x, &c_y);
	src.x = cursor_style * 16;
	src.y = 0;
	src.w = src.h = 16;
	dest.x = c_x;
	dest.y = c_y;
	SDL_BlitSurface(cursors, &src, window_main, &dest);
}

void Isoeng::selectAssets() {
	SDL_Rect src, dest;

	src.x = src.y = 0;
	if((c_x - m_x) < 0) {
		dest.x = c_x;
		src.w = m_x - c_x;
	} else {
		dest.x = m_x;
		src.w = c_x - m_x;
	}
	if((c_y - m_y) < 0) {
		dest.y = c_y;
		src.h = m_y - c_y;
	} else {
		dest.y = m_y;
		src.h = c_y - m_y;
	}
	SDL_BlitSurface(area_select, &src, window_main, &dest);
}
