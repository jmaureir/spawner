#include "Spawner.h"
#include "CommandNotFoundException.h"

#include <fstream>
#include <cstdio>
#include <string.h>
#include <syslog.h>
#include <signal.h>
#include <libgen.h> 
#include <errno.h>


int _killpg(pid_t pid, int signal) {
	return(killpg(getpgid(pid),signal));
}

Spawner::Spawner(std::string name) {
	this->name = name;
	openlog (this->name.c_str(), LOG_CONS | LOG_PID | LOG_NDELAY, LOG_DAEMON);
}

Spawner::~Spawner() {
	syslog(LOG_INFO,"Spawner exiting");
	closelog();
}

void Spawner::setCommand(std::string cmd, std::vector<std::string> args) {
	this->cmd = cmd;
	
	// check whether the given command exists or not

	if (!access(this->cmd.c_str(), F_OK) == 0) {
		throw CommandNotFoundException();
	}

	this->args = args;

}

void Spawner::run() {

	syslog(LOG_INFO,"Spawner main loop starting");

	int     pfd[2];  // pipes descriptors
	int     status = 0; // status for wait for child

	if (pipe(pfd)) {
		std::cout << "problems when creating the pipe to the process. aborting" << std::endl;
		return;
	}

	this->pid = fork();
	if (this->pid < 0) {
		std::cout << "fork Failed. aborting" << std::endl;
		return;
	}

	if (this->pid==0) {
		// Child process: execution of the process
		 
		if (pfd[1] != STDOUT_FILENO) {
		 dup2(pfd[1], STDOUT_FILENO);
 		}
		if (pfd[0] != STDIN_FILENO) {
			dup2(pfd[0], STDIN_FILENO);
		}

		// create the arguments array
		// first argument: executable
		// then, the arguments
		// and finishing with a NULL

		char* c_args[this->args.size()+2];
		c_args[0] = (char*)this->cmd.c_str();
		for(int i=1;i<this->args.size()+1;i++) {
			c_args[i] = (char*)(this->args[i-1].c_str());
		}
		c_args[this->args.size()+1] = NULL;

		// build the command line to show it into the log
		std::stringstream cmd_line;
		for(int i=0;i<this->args.size()+1;i++) {
			cmd_line << c_args[i] << " ";
		}

		syslog(LOG_INFO,"child pid %d\n",getpid());

		if (setpgid(0,getpid())!=0) {
			syslog(LOG_INFO,"cannot asign group process for pid %d: %s\n",getpid(),strerror(errno));
			_exit(0);
		}

		syslog(LOG_INFO,"executing %s\n",cmd_line.str().c_str());

		execv(this->cmd.c_str(),c_args);

		syslog(LOG_INFO,"child process ending");

		// close the pipes in this context when the process ends
		close(pfd[0]);
		close(pfd[1]);

		syslog(LOG_INFO,"spawned process ending");
		_exit(0);
	
	} else {
		// parent process: logging the output of the process
		if ((this->fd = fdopen(pfd[0], "r")) == NULL) {
			std::cout << "could not get the pipe to the spawned process. aborting" << std::endl;
			return;
		}

		syslog(LOG_INFO,"control process started watching pid: %d",this->pid);

		// close the writer pipe
		close(pfd[1]);

		char line[1024];

		while (fgets( line, sizeof line, fd)) {
			syslog(LOG_INFO,"%s",line);
		}

		pclose(this->fd);

		// be sure the child process has finished
		// only 10 times.
		for(int i=0;i<10;i++) {
			if (_killpg(pid,SIGINT)==0) {
				break;
			}
			sleep(10);
		}

		syslog(LOG_INFO,"Spawner control ending");
	}
}

void Spawner::stop() {
	if (this->fd!=0) {
		syslog(LOG_INFO,"spawner signaling SIGINT to child process pid %d",this->pid);
		_killpg(this->pid,SIGINT);
	}
}

void Spawner::actionPerformed(ActionEvent* evt) {

}
