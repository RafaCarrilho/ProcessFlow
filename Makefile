.PHONY: clean


main: main.c task.c parser.c exec.c job.c
	gcc main.c task.c parser.c exec.c job.c -o main

clean:
	rm -f main