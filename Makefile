.PHONY: clean

processflow: main.c task.c parser.c exec.c job.c
	gcc main.c task.c parser.c exec.c job.c -o processflow

clean:
	rm -f processflow