/*
 * @assetanim.h
 *
 * assetanim header file
 *
 * author: Dan Matsuoka
 */

#ifndef ASSETANIM_H
#define ASSETANIM_H

#include "asset.h"

class AssetAnim : public Asset {
	public:
		AssetAnim(int, int, int = 0, int = 0, int = 0, int = 1);

		int num_cycles, cur_cycle;
};

#endif
