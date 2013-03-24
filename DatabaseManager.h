#ifndef DATABSEMANAGER_H
#define DATABASEMANAGER_H

#include "soci.h"
#include "sqlite3/soci-sqlite3.h"

class DatabaseManager {
	public:
		DatabaseManager();
		~DatabaseManager();

		/**
		 * Create the SQLite database file and create all the tables.
		 */
		bool create_db(bool exists, soci::session& db);

		/**
		 * Save/update the data in the database when requested.
		 */
		bool save_db();
	private:

};

#endif
