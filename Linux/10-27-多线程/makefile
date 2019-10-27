all: create join test mutex
mutex:mutex.c
	gcc $^ -o $@ -lpthread
test:test.c
	gcc $^ -o $@ -lpthread
join:join.c
	gcc $^ -o $@ -lpthread
create:create.c
	gcc $^ -o $@ -lpthread

.PHONY:clean
clean:
	rm create

