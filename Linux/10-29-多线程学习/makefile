all:test cond
cond:cond.c
	gcc $^ -o $@ -lpthread
test:test.c
	gcc $^ -o $@ -lpthread

.PHONY:clean
clean:
	rm test
