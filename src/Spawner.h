#ifndef __SPAWNER__
#define __SPAWNER__

#include "Daemon.h"

#include <stdio.h> 
#include <vector>

class Spawner : public Daemon {
	private:
		std::string name;
		std::string cmd;
		std::vector<std::string> args;

		FILE* fd;

		pid_t pid;

	public:

		Spawner(std::string name);
		~Spawner();

		void setCommand(std::string cmd, std::vector<std::string> args);

		virtual void run();
		virtual void stop();

		virtual void actionPerformed(ActionEvent* evt);

};

#endif
