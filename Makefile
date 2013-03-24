LOCAL_SOCI_HEADERS = -Isoci/lib/include/soci -Isoci/lib/include/soci/sqlite3
LOCAL_SOCI_LFLAGS = libsoci_core.a libsoci_sqlite3.a

CURSESFLAGS	= -lncurses

CXX			= g++
#CXXFLAGS		= -Wall --std=c++0x ${DEBUGFLAG}
CXXFLAGS		= -Wall \
							--std=c++0x \
							$(DEBUGFLAG) \
							-pedantic \
							-t \
							$(LOCAL_SOCI_HEADERS)
OPTFLAG		= -O2
DEBUGFLAG	= -g
LINKER		= $(CXX)
LFLAGS		= \
						$(LOCAL_SOCI_LFLAGS) \
						$(CURSESFLAGS) \
						-lboost_system \
						-lboost_program_options \
						-lboost_filesystem

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

.PHONY: all soci clean

all: videocrumb

OBJS = $(SRC:.cpp=.o)

videocrumb: soci $(OBJS) 
	$(LINKER) $(LFLAGS) $(OBJS) -o $@

soci:
	./soci-build.sh
	cp soci/lib/lib*/libsoci_core.a .
	cp soci/lib/lib*/libsoci_sqlite3.a .

clean:
	rm -r $(OBJS) soci/bin/ soci/lib/ libsoci_core.a libsoci_sqlite3.a videocrumb
