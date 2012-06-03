/*
 * @cexception.h
 *
 * cexception header file
 *
 * author: Dan Matsuoka
 */

#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#include <cstdio>

class CException {
	public:
		CException(char* src = "Unknown", char* msg = "Unknown exception thrown");	// constructor
		~CException() {}	// destructor

		void report();

	private:
		char* source;
		char* message;
};

#endif
