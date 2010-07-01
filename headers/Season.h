#ifndef SEASON_H
#define SEASON_H
#include "includes.h"
#include "Anime.h"
#include "Episode.h"

class Season : public Anime {

	public:
		Season(const int& c,
			const string& n="no name",
	  		const string& s="");
		Season(const int& c,
			const vector<Episode>& e,
	  		const string& n="no name",
			const string& s="");
		~Season();

		void add(const string& e);
		void addAt(int n,const Episode& e);
		string getType() const;
		int getCurrent() const;
		int getTotal() const;
		bool playNext();
		bool unPlay();
		const string& print() const;
		void setNext(const int& n);

	protected:

	private:
		int episode_count;
		int total_episode_count;
		vector<Episode>::iterator next_episode;
		vector<Episode> *episodes;

};

#endif
