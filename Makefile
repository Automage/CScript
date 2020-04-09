all: cs

cs: cs.o script.o parser.o debug.o
	gcc -g -Wall -Werror -o cs cs.o script.o parser.o debug.o

cs.o: cs.c
	gcc -g -Wall -Werror -c -o cs.o cs.c;

script.o: script.c script.h
	gcc -g -Wall -Werror -c -o script.o script.c;

parser.o: parser.c parser.h
	gcc -g -Wall -Werror -c -o parser.o parser.c;

debug.o: debug.c debug.h
	gcc -g -Wall -Werror -c -o debug.o debug.c;

clean:
	rm cs *.o
