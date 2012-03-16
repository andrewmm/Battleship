# Makefile
# Battleship

CC=g++
CFLAGS=
SRC=battleship.cpp bshipmain.cpp
OBJ=battleship.o bshipmain.o

bship: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o bship

depend:
	makedepend -Y ${SRC} &> /dev/null

clean:
	rm -f ${OBJ} bship Makefile.bak

install: bship


battleship.o: battleship.h

bshipmain.o: battleship.h