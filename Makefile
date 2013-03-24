LOCAL_SOCI_HEADERS = -Isoci/lib/include/soci -Isoci/lib/include/soci/sqlite3
LOCAL_SOCI_LFLAGS = -Lsoci/lib/lib/ -Lsoci/lib/lib32 -Lsoci/lib/lib64

CXX			= g++
#CXXFLAGS		= -Wall --std=c++0x ${DEBUGFLAG}
CXXFLAGS		= -Wall --std=c++0x $(DEBUGFLAG) -pedantic -t $(LOCAL_SOCI_HEADERS)
OPTFLAG		= -O2
DEBUGFLAG	= -g
LINKER		= g++
LFLAGS		= -lboost_system -lboost_program_options -lboost_filesystem $(LOCAL_SOCI)
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
	./soci-build.sh
	$(LINKER) $(CURSESFLAGS) $(LFLAGS) $(OBJS) -o $@


clean:
	rm -r $(OBJS) soci/bin/* videocrumb
