#include "headers/Anime.h"

Anime::Anime(const string& n,
	  	const string& s):
	name(n),
  	subtext(s) {

}

Anime::~Anime() {
}

void Anime::editName(const string& n) {
	name = n;
}

void Anime::editSubtext(const string& s) {
	subtext = s;
}

const string& Anime::printName() {
	return name;
}
