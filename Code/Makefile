GCC      = gcc
FLAGS  = -std=gnu99 -Wall

all: main
	
main: generatorFile.c selector.c ../ErrorHandling/errorHandling.c
	$(GCC) $^ -o $@ $(FLAGS)

clean:
	rm -f main *.o

.PHONY: all clean