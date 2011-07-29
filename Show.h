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
		std::string name,
			file;
		showtype type;

		Show(std::string f = std::string(), std::string n = std::string(),
			showtype t = EPISODE, size_t w = 0) : file(f), type(t), watched(w) {
			name = (n.length()) ?  n : f;
		}

		Show(const Show& other);
		Show(Show& other);
		std::string print();


	private:
		size_t watched;
};

#endif 
