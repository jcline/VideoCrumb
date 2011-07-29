#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Player{

	private:
		std::string command, args, late;

	public:

		Player(std::string c = "", std::string a = "", std::string l = "") :
			command(c), args(a), late(l) {}

		~Player() {}

		int play(const std::string &filename);
		void setarguments(std::string a);
		void setlatearguments(std::string l);
		void setplayer(std::string c);
		std::string exportsettings();

};

#endif
