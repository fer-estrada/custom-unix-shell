CC = cc
FLAGS = -g -lreadline

.PHONY: all clean

all: fer_shell

fer_shell: shell.c
	$(CC) shell.c $(FLAGS) -o fer_shell

run:
	./fer_shell

clean:
	rm -rf fer_shell fer_shell.dSYM
