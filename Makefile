CXX			= g++
CXXFLAGS		= -Wall ${DEBUGFLAG}
OPTFLAG		= -O2
DEBUGFLAG	= -g
LINKER		= g++
LFLAGS		= -o
CURSESFLAGS	= -lncurses

OBJS  = \
        helperfunctions.o
#OBJS			= Anime.o \
				  Show.o \
				  Season.o \
				  OAV.o \
				  Movie.o \
				  Special.o \
				  Episode.o \
				  Item.o \
				  helperfunctions.o 

#path %.h headers

ncurses: ncurses.o ${OBJS}
	${CXX} ${CURSESFLAGS} ${LFLAGS} $@ ${OBJS} ncurses.o

clean:
	rm ${OBJS} ncurses.o ncurses
