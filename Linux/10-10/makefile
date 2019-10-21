all: pipe pipe1
pipe:pipe.c
	gcc $^ -o $@
pipe1:pipe1.c
	gcc $^ -o $@

.PHONY:clean
clean:
	rm pipe
	rm pipe1
