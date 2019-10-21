all:loop signal mask
mask:mask.c
	gcc $^ -o $@
signal:signal.c
	gcc $^ -o $@
loop:loop.c
	gcc $^ -o $@
.PHONY:clean
clean:
	rm loop
