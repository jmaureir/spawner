/* 
 * Simple Daemon to spawn process
 * Juan-Carlos Maureira
 * NLHPC - CMM
 * Universidad de Chile
 * Nov, 2011
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <getopt.h>

using namespace std;

#include "Spawner.h"

#define DETACH     false

Spawner* theSpawner; 

void sig_trapper(int sig) {
	theSpawner->stop();
}

void usage(int argc,char** argv) {
	std::cout << "usage: " << argv[0] << " -n name -d command -- args" << std::endl;
}

int main(int argc, char *argv[]) {

	if (DETACH) {

		// detach the main routine	
		int p = fork();
		if (p) exit(0);
	
		int pid = setsid();
	}

	int c = 0;
	std::string name;
	std::string cmd;
	std::vector<std::string> args;

	while ((c = getopt(argc, argv, "n:d:")) != -1) {
		switch (c) {
			case 'n':
				// get the name of the daemon
				name = std::string(optarg);
				break;
			case 'd':
				// get the daemon (binary) to run
				cmd = std::string(optarg);
				break;
			default:
				usage(argc,argv);
				exit(1);
		}
	}

	// process the arguments for the daemon
	for (int index = optind; index < argc; index++) {
		args.push_back(argv[index]);
	}

	theSpawner = new Spawner(name);

	signal(SIGINT,&sig_trapper);
	signal(SIGTERM,&sig_trapper);
	signal(SIGQUIT,&sig_trapper);
	signal(SIGKILL,&sig_trapper);

	try {
		theSpawner->setCommand(cmd,args);
	} catch(Exception& e) {
		std::cout << e.what() << std::endl;
	}
	theSpawner->start();

	// wait for all the children to join before exit
	theSpawner->join();
	
	delete(theSpawner);

	return(0);	
}
