all: cs

cs: cs.o script.o parser.o
	gcc -g -std=c11 -Wall -Werror -o cs cs.o script.o parser.o

cs.o: cs.c
	gcc -g -std=c11 -Wall -Werror -c -o cs.o cs.c;

script.o: script.c script.h
	gcc -g -std=c11 -Wall -Werror -c -o script.o script.c;

parser.o: parser.c parser.h
	gcc -g -std=c11 -Wall -Werror -c -o parser.o parser.c;

clean:
	rm cs *.o
