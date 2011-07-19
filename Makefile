CXX			= g++
CXXFLAGS		= -Wall --std=c++0x ${DEBUGFLAG}
OPTFLAG		= -O2
DEBUGFLAG	= -g
LINKER		= g++
LFLAGS		= -o
CURSESFLAGS	= -lncurses

SRC = \
			helperfunctions.cpp \
			Show.cpp \
			Player.cpp \
			Playlist.cpp \
			Window.cpp \
			PlaylistWindow.cpp \
			Settings.cpp \
			ncurses.cpp

OBJS = $(SRC:.cpp=.o)

ncurses: $(OBJS)
	$(CXX) $(CXXFLAGS) $(CURSESFLAGS) $(OBJS) -o $@

.h.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(OBJS) ncurses.o ncurses
