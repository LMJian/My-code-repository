all:epoll client
client:tcp_client.cc;
	g++ $^ -o $@ -std=c++11 -lpthread

epoll:epoll.cpp
	g++ $^ -o $@ -std=c++11 -lpthread

.PHONY:clean
clean:
	rm epoll
