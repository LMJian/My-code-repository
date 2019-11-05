all:join test thread
thread:thread.cc
	g++ $^ -o $@ -lpthread -std=c++11
test:test.cc
	g++ $^ -o $@ -lpthread -std=c++11
join:join.c
	gcc $^ -o $@ -lpthread
.PHONY:clean
clean:
	rm join
