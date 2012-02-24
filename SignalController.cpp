#include "SignalController.h"

void SignalController::sigint_handler() {
	sigint = true;
}

SignalController::SignalController() {

	sigint = false;

	struct sigaction sa;

	actions.push_back(sa);
	//actions.back().sa_handler = this->sigint_handler;
	//sigaction(SIGINT, &actions.back(), NULL);
}

SignalController::~SignalController() {
	actions.clear();
}

bool SignalController::check() {
	if(sigint) {

	}

	return true;
}


