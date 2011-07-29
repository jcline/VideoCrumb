#ifndef SHOW_H
#define SHOW_H

#include <string>

enum showtype{ 
	COMMENTARY,
	EPISODE,
	MOVIE,
	SPECIAL
};

class Show {
	public:
		std::string file,
			name;
		showtype type;

		Show(std::string f = std::string(), std::string n = std::string(),
			showtype t = EPISODE, size_t w = 0) : file(f), name(n), type(t), watched(w) {
		}

		Show(const Show& other);
		Show(Show& other);
		std::string print();
		std::string printdetail();


	private:
		size_t watched;
};

#endif 
