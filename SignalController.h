#ifndef SIGNALCONTROLLER_H
#define SIGNALCONTROLLER_H

#include <vector>

#include <signal.h>

class SignalController {

	private:
		std::vector<struct sigaction> actions;

		bool sigint;

		void sigint_handler();

	public:
		SignalController();
		~SignalController();

		bool check();
};

#endif
