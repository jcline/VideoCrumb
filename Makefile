CXX			= g++
CXXFLAGS		= -Wall --std=c++0x ${DEBUGFLAG}
OPTFLAG		= -O2
DEBUGFLAG	= -g
LINKER		= g++
LFLAGS		= -lboost_system -lboost_filesystem -lsoci_core -lsoci_sqlite3
CURSESFLAGS	= -lncurses 

SRC = \
			Color.cpp \
			Show.cpp \
			Player.cpp \
			Playlist.cpp \
			DatabaseManager.cpp \
			PlaylistController.cpp \
			Window.cpp \
			PlaylistWindow.cpp \
			SettingsController.cpp \
			SettingsWindow.cpp \
			ShowsWindow.cpp \
			SignalController.cpp \
			ncurses.cpp

OBJS = $(SRC:.cpp=.o)

videocrumb: $(OBJS) 
	$(LINKER) $(CURSESFLAGS) $(LFLAGS) $(OBJS) -o $@

clean:
	rm $(OBJS) videocrumb
