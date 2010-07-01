CXX			= g++
CXXFLAGS		= -Wall ${DEBUGFLAG}
OPTFLAG		= -O2
DEBUGFLAG	= -g
LINKER		= g++
LFLAGS		= -o
CURSESFLAGS	= -lncurses

OBJS			= Anime.o \
				  Show.o \
				  Season.o \
				  OAV.o \
				  Movie.o \
				  Special.o \
				  Episode.o \
				  Item.o \
				  helperfunctions.o 

vpath %.h headers

ncurses: ncurses.o ${OBJS}
	${CXX} ${CURSESFLAGS} ${LFLAGS} $@ ${OBJS} ncurses.o

test: test.o  ${OBJS}
	${CXX} ${LFLAGS}  $@ ${OBJS} test.o

clean:
	rm ${OBJS} test.o ncurses.o test ncurses
