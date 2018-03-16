CC = gcc

all:
	make static
	make shared
	make clean

static:
	$(CC) -c -Wall library.c					#Wall - warn all
	ar cr library.a library.o					#cr - create, ar - archive - utwórz archiwum, czyli bibliotekê statycznê

shared:
	$(CC) -c -Wall -fPIC library.c				#fPIC - position independent code
	$(CC) -shared -fPIC -o library.so library.o

clean:
	rm -f *.o									#rm - remove, *.o - wszystkie pliki z rozszerzeniem *.o





CC = gcc
CFLAGS = -g -O 						# tutaj mo¿na dodawaæ inne flagi kompilatora
LIBS = -lm library.h 				# tutaj mo¿na dodawaæ biblioteki
OBJ = main.o library.o

all: main

main: $(OBJ)
       $(CC) $(OBJ) $(LIBS) -o test

clean:
       rm -f *.o test

.c.o:
       $(CC) -c $(INCLUDES) $(CFLAGS) $<

