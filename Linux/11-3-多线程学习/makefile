all:cond test _test
_test:test.cc
	g++ $^ -o $@ -lpthread -std=c++11
test:test.cpp
	g++ $^ -o $@ -lpthread
cond:cond.c
	gcc $^ -o $@ -lpthread
.PHONY:clean
clean:
	rm cond
