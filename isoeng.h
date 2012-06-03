/*
 * @isoeng.h
 *
 * isometric engine header file
 *
 * author: Dan Matsuoka
 */

#ifndef ISOENG_H
#define ISOENG_H

#include <cstdlib>
#include <time.h>
#include "SDL.h"
#include "SDL_image.h"
#include "cexception.h"
#include "tile.h"

class Isoeng {
	public:
		Isoeng(char* = "isoeng");	// constructor
		~Isoeng();	// destructor

		bool isAlive() { return alive; }
		void run();

	private:
		/* main window dimensions; asset values */
		static const int WM_WIDTH = 480; //848;
		static const int WM_HEIGHT = 272; //480;
		static const int MAP_WIDTH = 848;
		static const int MAP_HEIGHT = 480;
		static const int X_TILES = 26;
		static const int Y_TILES = 48;
		static const int TILE_WIDTH = 32;
		static const int TILE_HEIGHT = 32;
		static const int TILE_SHEETS = 4;
		static const int UNIT_SHEETS = 1;
		
		bool alive;
		char* err;
		int cursor_style, c_x, c_y, m_x, m_y;
		int x_offset, y_offset;
		SDL_Surface* window_main;
		SDL_Surface* background;
		SDL_Surface* cursors;
		SDL_Surface* area_select;
		SDL_Surface** tile_sheets;
		SDL_Surface** unit_sheets;
		Tile*** tile;

		void loadCursorImages();
		void loadTileImages();
		void createSurfaces();
		void renderBackground();
		void grabBackground();
		void selectAssets();
};

#endif
