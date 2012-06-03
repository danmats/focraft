/* 
 * @tile.cpp 
 *
 * tile class for isometric engine
 *
 * author: Dan Matsuoka
 */

#include "tile.h"

Tile::Tile(int x, int y, int img_x, int img_y, int s, t_byte n) : Asset(x, y, img_x, img_y, s) {
	occupied = false;
	neighbors = n;
}

void Tile::function_t() {
}
