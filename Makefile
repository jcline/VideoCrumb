CXX			= g++
CXXFLAGS		= -Wall ${DEBUGFLAG}
OPTFLAG		= -O2
DEBUGFLAG	= -g
LINKER		= g++
LFLAGS		= -o
CURSESFLAGS	= -lncurses

OBJS	= \
	helperfunctions.o

ncurses: ncurses.o ${OBJS}
	${CXX} ${CURSESFLAGS} ${LFLAGS} $@ ${OBJS} ncurses.o

clean:
	rm ${OBJS} ncurses.o ncurses
