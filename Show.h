#ifndef SHOW_H
#define SHOW_H

#include <iostream>
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
			showtype t = EPISODE, unsigned int w = 0) :
		 	file(f), name(n), type(t), watched(w) {
		}

		Show(const Show& other);
		Show(Show& other);
		std::string print();
		void printdetail(std::ostream& o);
		void watch();
		const unsigned int getwatched();

		static showtype gettype(const std::string& t);

	private:
		unsigned int watched;
};

#endif 
