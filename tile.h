/*
 * @tile.h
 *
 * tile header file
 *
 * author: Dan Matsuoka
 */

#ifndef TILE_H
#define TILE_H

#include "asset.h"

class Tile : public Asset {
	public:
		typedef unsigned char t_byte;

		Tile(int, int, int = 0, int = 0, int = 0, t_byte = 255);	// constructor
		~Tile() {}	// destructor
		
		bool occupied;
		t_byte neighbors;

		void function_t();
};

#endif
