/*
 * @asset.h
 *
 * asset header file
 *
 * author: Dan Matsuoka
 */

#ifndef ASSET_H
#define ASSET_H

class Asset {
	public:
		Asset(int, int, int = 0, int = 0, int = 0);	// constructor
		~Asset() {}	// destructor

		int x, y, image_x, image_y, sheet;
};

#endif
