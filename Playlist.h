#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Show.h"
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "soci/soci/src/core/soci.h"

class Playlist {
	private:
		//! Keep track of whether or not our string caches need to be updated
		bool printstrchanged, changed;
		//! String cache of detailed info, name of playlist, prior name of playlist
		std::string printstr, name, old_name;
		//! List of shows in this playlist
		std::vector<Show> items;

	public:

		Playlist();
		Playlist(const std::string& n);
		/**
		 * Only use this constructor when initializing from the database
		 */
		Playlist(const std::string& n, const Playlist& b);
		Playlist(const std::string& n, Show& s);

		~Playlist() {}

		/**
		 * Add a new show to the playlist
		 */
		void add(Show& s);
		/**
		 * Add a new show to the playlist at a given position
		 */
		void add(Show& s, size_t pos);

		/**
		 * Get the iterator to the first element in the playlist
		 */
		auto begin() -> decltype(items.end());
		/**
		 * Get the iterator to the last element in the playlist + 1
		 */
		auto end() -> decltype(items.end());
		/**
		 * Get the first unplayed element in the playlist for this session
		 * If there is none, returns begin()
		 */
		auto first() -> decltype(items.end());

		//! Operator for sorting
		bool operator< (const Playlist& o) const;

		/**
		 * Marks this playlist as modified, for methods that can be more efficient
		 * with this knowledge
		 */
		void change();
		/**
		 * Remove the selected item from the playlist
		 */
		void deleteselection(decltype(items.begin()) s);
		/**
		 * Get the number of times played?
		 */
		unsigned int played();
		/**
		 * Remove an item at a given position from the playlist
		 */
		void remove(size_t pos);

		/**
		 * Print the playlist for output of some kind
		 */
		std::string print();
		/**
		 * Print a more detailed version of the playlist to a given stream
		 * (mainly for saving to a file)
		 */
		void printdetail(std::ostream& o);
		/**
		 * Print an element at a given position in the playlist
		 */
		std::string print(size_t pos);

		/**
		 * Return a const reference to the name
		 */
		const std::string& getname() const;
		/**
		 * If the name is changed and we need to update it in the database
		 */
		const std::string& getoldname() const;
		/**
		 * Return the size of the playlist
		 */
		const size_t size();

		/**
		 * Return if the playlist data has changed
		 */
		bool haschanged();

		/**
		 * Database type conversion for named identifiers, needs private access
		 */
		template<class Playlist> friend struct soci::type_conversion;
};

/**
 * SOCI type conversion code for database access ease
 */
namespace soci {
	template<>
	struct type_conversion<Playlist> {

		typedef values base_type;

		static void from_base(const values& v, indicator /* ind */, Playlist p) {
			p.name = v.get<std::string>("NAME");
		}

		static void to_base(const Playlist& p, values& v, indicator& ind) {
			v.set("NAME", p.name);
			v.set("OLDNAME", p.old_name);
			ind = i_ok;
		}

};
}

#endif
