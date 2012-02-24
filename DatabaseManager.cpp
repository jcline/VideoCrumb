#include "soci/soci.h"
#include "soci/sqlite3/soci-sqlite3.h"

DatabaseManager::DatabaseManager() {
}

DatabaseManager::~DatabaseManager() {
}

bool DatabaseManager::db_create(bool exists, session& db) {

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
			int order = 0;
			for(Playlist& p : playlists) {
				db << "INSERT INTO Playlists VALUES(:NAME)", use(p);

				for(Show& s : p) {

					db << "INSERT INTO Shows VALUES(:FILE,:NAME,:WATCHED,:TYPE,:PLAYLIST)",
						 use(s), use(p.getname(), "PLAYLIST");

				}
			}
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
