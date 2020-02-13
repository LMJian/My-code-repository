all:fork vfork thread clone
fork:fork.c
	g++ $^ -o $@
vfork:vfork.c
	g++ $^ -o $@
thread:thread.c
	g++ $^ -o $@ -lpthread
clone:clone.c
	g++ $^ -o $@ -lpthread

.PHONY:clean
clean:
	rm fork
	rm vfork
	rm thread
