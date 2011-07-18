#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Player{

	private:
		std::string command, args;

	public:

		Player(std::string c = "", std::string a = "") :
			command(c), args(a) {}

		~Player() {}

		int play(const std::string &filename);
		void setarguments(std::string a);
		void setplayer(std::string c);
		std::string exportsettings();

};

#endif
