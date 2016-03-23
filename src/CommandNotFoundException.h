#ifndef __COMMANDNOTFOUNDEXCEPTION__
#define __COMMANDNOTFOUNDEXCEPTION__

#include "Exception.h"

class CommandNotFoundException : public Exception {
	public:
		CommandNotFoundException() : Exception("Command Not Found") {}

};

#endif
