#include "headers/Episode.h"

Episode::Episode () {}

Episode::Episode (const Episode& e) {
	number = e.number;
	items = new vector<Item>( *e.items );
}

Episode::Episode(const int& n, const string& file) {
	number = n;
	items = new vector<Item>();
	items->push_back( *(new Item(file)) );
}

Episode::Episode(const int& n, const vector<Item>& l) {
	number = n;
	items = new vector<Item>(l);
}

Episode::~Episode() {
//items->clear();
	delete(items);
}

Episode& Episode::operator=(const Episode& e) {
	if (this == &e)
		return *this;

	number = e.number;
	items = new vector<Item>( *e.items );
	return *this;
}

void Episode::add(const string& i) {
	items->reserve( items->size() + 1 );
	items->push_back( * new Item(i) );
}

void Episode::play() {

	vector<Item>::iterator i;
	for (i = items->begin(); i < items->end(); ++i)
		(*i).open();
}

string Episode::print() {
	string str;
	vector<Item>::iterator it;
	for( it = items->begin(); it < items->end(); ++it)
		str += it->print();
	return str;
}
