#include "Player.h"
#include <string>
#include <iostream>

using std::string;

string Player::exportsettings() {
	return command + '\n' + args + '\n';
}

int Player::play(const string& filename) {
	return system( (command + args + "\"" + filename + "\"" + late).c_str());
}

void Player::setarguments(string a) {
	args = a;
}

void Player::setlatearguments(string l) {
	late = l;
}

void Player::setplayer(string c) {
	command = c;
}
