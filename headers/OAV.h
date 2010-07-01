#ifndef OAV_H
#define OAV_H
#include "includes.h"
#include "Season.h"

class OAV : public Season {

	public:
		OAV(const int& c,
				const string& n="no name",
				const string& s="");
		OAV(const int& c,
				const vector<Episode>& e,
				const string& n="no name",
				const string& s="");
		~OAV();

		string getType();

	protected:

	private:

};

#endif

