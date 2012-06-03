/* 
 * @assetanim.cpp 
 *
 * assetanim class for isometric engine
 *
 * author: Dan Matsuoka
 */

#include "assetanim.h"

AssetAnim::AssetAnim(int x, int y, int img_x, int img_y, int s, int nc) : Asset(x, y, img_x, img_y, s) {
	num_cycles = nc;
	cur_cycle = 0;
}
