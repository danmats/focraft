/* 
 * @focraft.cpp 
 *
 * focraft
 *
 * author: Dan Matsuoka
 */

#include "focraft.h"

int main(int argc, char* argv[]) {
	try {
		Isoeng* isoeng = new Isoeng("focraft");

		do {
			isoeng->run();
		} while(isoeng->isAlive());

		delete isoeng;
	} catch(std::exception& e) {
		std::cout << "Std exception: " << e.what() << std::endl; 
//	} catch(gcn::Exception& e) {
//		std::cout << "Guichan exception: " << e.getMessage() << std::endl;
	} catch(CException& e) {
		e.report();
	} catch(...) {
		CException* e = new CException();
		e->report();
	}

	return 0;
}
