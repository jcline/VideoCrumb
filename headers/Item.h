#ifndef ITEM_H
#define ITEM_H

#include "includes.h"

class Item {
	public:
		Item();
		Item(const string& f);
		~Item();

		int open();
		string print();

	protected:
		string file;

	private:

};

#endif
