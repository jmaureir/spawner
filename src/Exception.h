#ifndef __Exception__
#define __Exception__

#include <iostream>
#include <exception>
#include <string>

#define EXCEPTION_HEADER    "Exception Raised:"

class Exception : public std::exception {

	private:
		std::string error;

	public:

		Exception():exception() {
			this->error = "uncaught exception";
		}

		Exception(std::string e):exception() {
			this->error = e;
		}

		~Exception() throw () {

		}

		const char* what() {
			return(this->error.c_str());
		}

		std::string toString() {
			return(this->error);
		}

		void printStackTrace() {
			std::cout << EXCEPTION_HEADER << this->error << std::endl;
		}

		friend std::ostream& operator << (std::ostream& os, Exception* e) {
			os << e->toString();
			return os;
		}

};

#endif
