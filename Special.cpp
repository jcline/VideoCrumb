#include "headers/Special.h"

Special::Special (const int& c,
		const string& file,
		const string& n,
		const string& s):
  	Movie(c,file,n,s) {

}

Special::Special (const int& c,
		const vector<Item>& l,
		const string& n,
		const string& s):
  	Movie(c,l,n,s) {

}

Special::~Special() {
}

string Special::getType() {
	return "Special";
}
