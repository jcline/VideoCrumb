CXX			= g++
CXXFLAGS		= -Wall --std=c++0x ${OPTFLAG}
OPTFLAG		= -O2
DEBUGFLAG	= -g
LINKER		= g++
LFLAGS		= -lboost_system -lboost_filesystem 
CURSESFLAGS	= -lncurses 

SRC = \
			helperfunctions.cpp \
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
			ncurses.cpp

OBJS = $(SRC:.cpp=.o)

ncurses: $(OBJS)
	$(LINKER) $(CURSESFLAGS) $(LFLAGS) $(OBJS) -o $@

clean:
	rm $(OBJS) ncurses
