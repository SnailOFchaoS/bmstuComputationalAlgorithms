CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wpedantic
RM = rm

app.exe: main.o
	$(CC) -o $@ $^ -O0 -g3
	
main.o: main.c
	gcc -std=c99 -Wall -Werror -Wpedantic -c main.c -O0 -g3
clean:
	$(RM) *.o *.exe