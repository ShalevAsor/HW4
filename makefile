CC=gcc
AR=ar
OBJECTS_FREQUENCY_MAIN=frequency.o
FLAGS=-Wall -g

all: frequency

frequency.o: frequency.c 
	$(CC) $(FLAGS) -c frequency.c 

frequency: $(OBJECTS_FREQUENCY_MAIN)
	$(CC) $(FLAGS) -o frequency $(OBJECTS_FREQUENCY_MAIN)


.PHONY:clean all

clean:
	rm -f *.o frequency 