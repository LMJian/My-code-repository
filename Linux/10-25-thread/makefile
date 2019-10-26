all:create test test1 test2 test3
test3:test3.c
	gcc $^ -o $@ -lpthread
test2:test2.c
	gcc $^ -o $@ -lpthread
test1:test1.c
	gcc $^ -o $@ -lpthread
test:test.c
	gcc $^ -o $@ -lpthread -g
create:create.c
	gcc $^ -o $@ -lpthread


.PHONY:clean
clean:
	rm create
