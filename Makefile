CXX			= g++
CXXFLAGS		= -Wall --std=c++0x ${DEBUGFLAG}
OPTFLAG		= -O2
DEBUGFLAG	= -g
LINKER		= g++
LFLAGS		= -lboost_system -lboost_filesystem 
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
	$(LINKER) $(CURSESFLAGS) $(LFLAGS) $(OBJS) -o $@

clean:
	rm $(OBJS) videocrumb
