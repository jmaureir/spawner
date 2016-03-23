#include "Daemon.h"

void Daemon::setRunning(bool b) {
	this->running = true;
}

bool Daemon::isRunning() {
	return this->running;
}
