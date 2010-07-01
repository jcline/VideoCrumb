#include "headers/Season.h"

Season::Season(const int& c,
		const string& n,
	  	const string& s):
  	Anime(n,s),
  	total_episode_count(c) {

	episode_count = 0;
	episodes = new vector<Episode>();
	episodes->reserve(total_episode_count);
}

Season::Season(const int& c,
	  	const vector<Episode>& e,
		const string& n,
	  	const string& s):
  	Anime (n,s),
  	total_episode_count(c) {

	episodes = new vector<Episode>(e);
	episodes->reserve(c);
	episode_count = episodes->size();
	next_episode = episodes->begin();
}

Season::~Season() {
	episodes->clear();
   delete(episodes);
}

void Season::add (const string& i) {
	if (episode_count == total_episode_count)
		return;
	++episode_count;
	Episode e(episode_count,i);
	episodes->push_back(e);
	if ( episode_count == 1)
		next_episode = episodes->begin();
}

/* Broken */
void Season::addAt (int n,const Episode& e) {
	vector<Episode>::iterator i = episodes->begin() + n;
	episodes->insert(i,1,e);
}

string Season::getType() const {
	return "Season";
}

int Season::getCurrent() const {
	return distance( episodes->begin(), next_episode );
}

int Season::getTotal() const {
	return total_episode_count;
}

bool Season::playNext() {
	if (episode_count == 0)
		return true;
	if (next_episode < episodes->end())	{
		(*next_episode).play();
		++next_episode;
		return false;
	}
	return true;
}

const string& Season::print() const {
	string *str = new string();
	stringstream out;
	out << name << endl 
		<< distance( episodes->begin(), next_episode ) <<
		" " << episode_count << " " << total_episode_count << endl;
	*str = out.str();
	
	vector<Episode>::iterator it;
	for( it = episodes->begin(); it < episodes->end(); ++it)
		*str += it->print() + "\n";

	return *str;
}

bool Season::unPlay() {
	if( next_episode > episodes->begin() )
		--next_episode;
	else
		return false;
	return true;
}

void Season::setNext( const int& n ) {
	next_episode = episodes->begin() + n;
}
