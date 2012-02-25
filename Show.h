#ifndef SHOW_H
#define SHOW_H

#include <iostream>
#include <string>

#include "soci/soci/src/core/soci.h"

enum showtype{ 
	// Commentaries, like from DVD/BDs
	COMMENTARY,
	// An episode from a series
	EPISODE,
	// A movie
	MOVIE,
	// A special feature from a DVD, BD, etc
	SPECIAL
};

class Show {
	public:
		//! File where this show can be played from
		std::string file;
		//! The name of this show
		std::string name;
		//! The type of this show, as described in enumeration
		showtype type;

		/**
		 * The constructor that should be use.
		 *
		 * @param f the path to this show's file
		 * @param n the name of this show
		 * @param t the type of the show
		 * @param w the number of times the show has been watched
		 */
		Show(std::string f = std::string(), std::string n = std::string(),
			showtype t = EPISODE, unsigned int w = 0) :
		 	file(f), name(n), type(t), watched(w) {
		}

		/**
		 * Copy constructors.
		 */ 
		Show(const Show& other);
		Show(Show& other);

		/**
		 * Return a string of information about this show.
		 */
		std::string print();

		/**
		 * Print detailed information about this show to ostream o.
		 */
		void printdetail(std::ostream& o);

		/**
		 * Start associatied Player to play this show.
		 */
		void watch();
		
		/**
		 * Getter for number of times this show has been watched.
		 */
		const unsigned int getwatched();

		/**
		 * Getter for the type of show as listed in the enumeration.
		 */
		static showtype gettype(const std::string& t);

	private:
		//! The number of times this show has been watched.
		unsigned int watched;

	/**
	 * Friend for serializing a Show for the database.
	 */
	template<class Show> friend struct soci::type_conversion;
};


/**
 * SOCI type conversion code for database access ease
 */
namespace soci {
	template<>
	struct type_conversion<Show> {

		typedef values base_type;

		static void from_base(const values& v, indicator /* ind */, Show s) {
			s.name = v.get<std::string>("NAME");
			s.file = v.get<std::string>("FILE");
			s.watched = v.get<int>("WATCHED");

			std::string t = v.get<std::string>("TYPE");

			if(t == "EPISODE")
				s.type = EPISODE;
			else if(t == "MOVIE")
				s.type = MOVIE;
			else if(t == "SPECIAL")
				s.type = SPECIAL;
			else if(t == "COMMENTARY")
				s.type = COMMENTARY;


		}

		static void to_base(const Show& s, values& v, indicator& ind) {
			v.set("NAME", s.name);
			v.set("FILE", s.file);
			v.set("WATCHED", s.watched);

			switch(s.type) {
				case COMMENTARY:
					v.set("TYPE", std::string("COMMENTARY"));
					break;
				case EPISODE:
					v.set("TYPE", std::string("EPISODE"));
					break;
				case MOVIE:
					v.set("TYPE", std::string("MOVIE"));
					break;
				case SPECIAL:
					v.set("TYPE", std::string("SPECIAL"));
					break;
			}

			ind = i_ok;
		}

	};
}
#endif 
