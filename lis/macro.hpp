#pragma once

#include <exception>





#define TRY try {

#define CATCH \
	} \
	catch(std::string const &e) \
	{ \
		std::cerr << "Error: " << e << endl; \
	} \
	catch(char const *e) \
	{ \
		std::cerr << "Error: " << e << endl; \
	} \
	catch(std::exception const &e) \
	{ \
		std::cerr << "Error: " << e.what() << endl; \
	}





// end
