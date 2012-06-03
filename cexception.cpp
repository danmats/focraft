/* 
 * @cexception.cpp 
 *
 * cexception class
 *
 * author: Dan Matsuoka
 */

#include "cexception.h"

CException::CException(char* src, char* msg) {
	source = src;
	message = msg;
}

void CException::report() {
	printf("[%s exception] %s\n", source, message);
}
