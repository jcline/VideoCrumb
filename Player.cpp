#include "Player.h"
#include <string>

using std::string;

int Player::play(const string& filename) {
	return 0;
}

void Player::setplayer(string c) {
	command = c;
}

void Player::setarguments(string a) {
	args = a;
}

string Player::exportsettings() {
	return command + '\n' + args + '\n';
}
