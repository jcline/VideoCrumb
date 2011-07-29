CXX			= g++
CXXFLAGS		= -Wall --std=c++0x ${DEBUGFLAG}
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
			Settings.cpp \
			ShowsWindow.cpp \
			ncurses.cpp

OBJS = $(SRC:.cpp=.o)

ncurses: $(OBJS)
	$(CXX) $(CXXFLAGS) $(CURSESFLAGS) $(LFLAGS) $(OBJS) -o $@

.h.o:
	$(CXX) $(CXXFLAGS) $(LFLAGS) -c $< -o $@

clean:
	rm $(OBJS) ncurses.o ncurses
