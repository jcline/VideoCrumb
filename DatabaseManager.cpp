#include "soci/soci.h"
#include "soci/sqlite3/soci-sqlite3.h"

#include "Playlist.h"
#include "Show.h"

#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() {
}

DatabaseManager::~DatabaseManager() {
}

bool DatabaseManager::create_db(bool exists, session& db) {

	const double version = .2;
	double v = 0;
	indicator ind;
	bool init = true, caught = false;


	// TODO: remove exists once we drop old database stuff
	if(exists) {
		try {
			db << "SELECT Number FROM Version", into(v, ind);
		}
		catch (const std::exception& e) {
			init = true;
			caught = true;
		}

		if(!caught && db.got_data()) {
			switch(ind) {
				case i_ok:
					init = false;
					break;
				case i_null:
					break;
				case i_truncated:
					break;
			}

			if(v < version) {
				init = true;
			}
		}
	}
	else
		init = true;
	// Do we need to worry about a table existing but not having
	// all the columns we care about?
	if(init) {
		db << "CREATE TABLE IF NOT EXISTS Playlists ("
			"Name TEXT PRIMARY KEY ASC NOT NULL"
			")";
		db << "CREATE TABLE IF NOT EXISTS Version ("
			"Number REAL NOT NULL"
			")";

		db << "CREATE TABLE IF NOT EXISTS Shows ("
			"File TEXT PRIMARY KEY ASC NOT NULL, "
			"Name TEXT, "
			"ID INT NOT NULL, "
			"Watched INT DEFAULT 0, "
			"Type TEXT NOT NULL DEFAULT EPISODE, "
			"Playlist REFERENCES Playlists (Name) ON DELETE CASCADE ON UPDATE CASCADE"
			")";

		if(exists && !caught && v < version) {
			db << "UPDATE Version SET Number = :version", use(version);
		}
		else
			db << "INSERT INTO Version (Number) VALUES(:version)", use(version);

		// TODO: remove this once we drop old database stuff
		if(!exists) {
#if __GNUC__ <= 4 && __GNUC_MINOR__ < 6
			int order = 0;
			for(auto i = playlists.begin(); i < playlists.end(); ++i) {
				db << "INSERT INTO Playlists VALUES(:NAME)", use(playlists[i]);

				for(auto j = playlists[i].begin(); j < playlists[i].end(); ++j) {
					db << "INSERT INTO Shows VALUES(:FILE,:NAME,:WATCHED,:TYPE,:PLAYLIST)",
						 use(*j), use((*j).getname(), "PLAYLIST");

				}
			}
#else
			int order = 0;
			for(Playlist& p : playlists) {
				db << "INSERT INTO Playlists VALUES(:NAME)", use(p);

				for(Show& s : p) {

					db << "INSERT INTO Shows VALUES(:FILE,:NAME,:WATCHED,:TYPE,:PLAYLIST)",
						 use(s), use(p.getname(), "PLAYLIST");

				}
			}
#endif
		}

		db << "SELECT Number FROM Version", into(v, ind);

		if(db.got_data()) {
			switch(ind) {
				case i_ok:
					return true;
					break;
				case i_null:
					return false;
					break;
				case i_truncated:
					break;
			}
		}
	}

	return false;
}

bool PlaylistController::save_db() {
	bool exists = boost::filesystem::exists(sc.db);
	session db(sqlite3, sc.db.native());

	// TODO: remove exists once we drop old database stuff
	assert(db_create(exists, db));

#if __GNUC__ <= 4 && __GNUC_MINOR__ < 6
	size_t size = playlists.size();
	for(size_t i = 0; i < size; ++i) {
		if(playlists[i].haschanged()) {
			std::string name;
			indicator ind;
			db << "SELECT Name FROM Playlists WHERE Name == :OLDNAME", use(playlists[i]), into(name, ind);
			if(ind == i_ok && db.got_data()) {
				db << "UPDATE Playlists SET "
					"Name=:NAME "
					"WHERE Name == :OLDNAME", use(playlists[i]);
			}
			else {
				db << "INSERT INTO Playlists VALUES(:NAME)", use(playlists[i]);
			}
		}


		size_t shows_size = p.size();
		for(size_t j = 0; j < shows_size; ++j) {
			//s.printdetail(db);
			//db << '\n';
		}
	}
#else
	for(Playlist& p : playlists) {
		if(p.haschanged()) {
			std::string name;
			indicator ind;
			db << "SELECT Name FROM Playlists WHERE Name == :OLDNAME", use(p), into(name, ind);
			if(ind == i_ok && db.got_data()) {
				db << "UPDATE Playlists SET "
					"Name=:NAME "
					"WHERE Name == :OLDNAME", use(p);
			}
			else {
				db << "INSERT INTO Playlists VALUES(:NAME)", use(p);
			}
		}


		for(Show& s : p) {
			//s.printdetail(db);
			//db << '\n';
		}
	}
#endif

	return true;
}

