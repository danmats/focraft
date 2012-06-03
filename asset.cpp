/* 
 * @asset.cpp 
 *
 * asset base class for isometric engine
 *
 * author: Dan Matsuoka
 */

#include "asset.h"

Asset::Asset(int x, int y, int img_x, int img_y, int s) {
	this->x = x;
	this->y = y;
	image_x = img_x;
	image_y = img_y;
	sheet = s;
}
