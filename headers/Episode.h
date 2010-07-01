#ifndef EPISODE_H
#define EPISODE_H

#include "includes.h"
#include "Item.h"

class Episode {

	public:
		Episode();
		Episode(const Episode& e);
		Episode(const int& n, const string& file);
		Episode(const int& n, const vector<Item>& l);
		~Episode();

		Episode& operator=(const Episode& e);

		void add(const string& i);
		void play();
		string print();

	protected:

	private:
		vector<Item> *items;
		int number;

};

#endif

