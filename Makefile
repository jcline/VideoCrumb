CXX			= g++
#CXXFLAGS		= -Wall --std=c++0x ${DEBUGFLAG}
CXXFLAGS		= -Wall --std=c++0x ${DEBUGFLAG} -pedantic -t
OPTFLAG		= -O2
DEBUGFLAG	= -g
LINKER		= g++
LFLAGS		= -lboost_system -lboost_filesystem ./soci/bin/lib/libsoci_core.a ./soci/bin/lib/libsoci_sqlite3.a
CURSESFLAGS	= -lncurses 

SRC = \
			Color.cpp \
			Show.cpp \
			Player.cpp \
			Playlist.cpp \
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
	./soci-build.sh
	$(LINKER) $(CURSESFLAGS) $(LFLAGS) $(OBJS) -o $@


clean:
	rm -r $(OBJS) soci/bin/* videocrumb
