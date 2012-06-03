/*
 * @unit.h
 *
 * unit header file
 *
 * author: Dan Matsuoka
 */

#ifndef UNIT_H
#define UNIT_H

#include "assetanim.h"

class Unit : public AssetAnim {
	public:
		Unit(int, int, int = 0, int = 0, int = 0, int = 1);	// constructor
		~Unit() {}	// destructor

		int x_offset, y_offset;
};

#endif
