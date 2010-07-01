#include "headers/OAV.h"

OAV::OAV(const int& c,
		const string& n,
		const string& s):
  	Season(c,n,s) {

}

OAV::OAV(const int& c,
		const vector<Episode>& e,
		const string& n,
		const string& s):
  	Season(c,e,n,s) {

}

OAV::~OAV() {
}

string OAV::getType() {
	return "OAV";
}
