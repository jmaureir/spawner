/*
 * Daemon.h
 *
 *  Created on: Mar 31, 2009
 *      Author: JcM
 */

#ifndef DAEMON_H_
#define DAEMON_H_

#include "Thread.h"
#include "ActionListener.h"

class Daemon : public Thread, public ActionListener {
protected:
	bool running;

public:
	Daemon() : Thread() {
		// std::cout << "Daemon Constructor" << endl;
	}

	~Daemon(){
		// std::cout << "Daemon Destructor" << endl;
	}

	void setRunning(bool b);
	bool isRunning();

	virtual void run()=0;

};

#endif /* DAEMON_H_ */
