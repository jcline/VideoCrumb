#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Show.h"
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "soci/soci.h"

class Playlist {
	private:
		bool printstrchanged, changed;
		std::string printstr, name, old_name;
		std::vector<Show> items;

	public:

		Playlist();
		Playlist(std::string& n);
		// Only use this constructor when initializing from the database
		Playlist(std::string& n, const Playlist& b);
		Playlist(std::string& n, Show& s);

		~Playlist() {}

		// Add a new show to the playlist
		void add(Show& s);
		// Add a new show to the playlist at a given position
		void add(Show& s, size_t pos);

		// Get the iterator to the first element in the playlist
		auto begin() -> decltype(items.end());
		// Get the iterator to the last element in the playlist + 1
		auto end() -> decltype(items.end());
		// Get the first unplayed element in the playlist for this session
		// If there is none, returns begin()
		auto first() -> decltype(items.end());

		// Marks this playlist as modified, for methods that can be more efficient with this knowledge
		void change();
		// Remove the selected item from the playlist
		void deleteselection(decltype(items.begin()) s);
		// Get the number of times played?
		unsigned int played();
		// Remove an item at a given position from the playlist
		void remove(size_t pos);

		// Print the playlist for output of some kind
		std::string print();
		// Print a more detailed version of the playlist to a given stream (mainly for saving to a file)
		void printdetail(std::ostream& o);
		// Print an element at a given position in the playlist
		std::string print(size_t pos);

		// Return a const reference to the name
		const std::string& getname() const;
		// If the name is changed and we need to update it in the database
		const std::string& getoldname() const;
		// Return the size of the playlist
		const size_t size();

		// Return if the playlist data has changed
		bool haschanged();

		// Database type conversion for named identifiers, needs private access
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
		}

};
}

#endif
