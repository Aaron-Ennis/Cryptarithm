CC=gcc
CFLAGS=-Wall -std=gnu99
LIBS += -lm

all: cryptarithm

cryptarithm: cryptarithm.o linkedList.o crypt.o
	gcc -g $(CFLAGS) -o cryptarithm cryptarithm.o crypt.o linkedList.o $(LIBS)

linkedList.o: linkedList.c linkedList.h
	gcc -g $(CFLAGS) -c linkedList.c

crypt.o: crypt.c crypt.h
	gcc -g ${CFLAGS} -c crypt.c

cryptarithm.o: cryptarithm.c linkedList.h
	gcc -g $(CFLAGS) -c cryptarithm.c

clean:
	-rm *.o

cleanall: clean
	-rm cryptarithm