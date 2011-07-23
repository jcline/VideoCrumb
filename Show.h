#ifndef SHOW_H
#define SHOW_H

#include <string>

class Show {
	public:
		std::string name,
			file;
		unsigned short type;

		Show( std::string n = "", std::string f = "",
				unsigned short t = 0 ) : name(n), file(f), type(t) {}
		
		Show(const Show& other);
		std::string print();


};

#endif 
