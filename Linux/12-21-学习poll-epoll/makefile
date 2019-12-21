all:pollserver client epollserver
epollserver:tcp_epoll_server.cc
	g++ $^ -o $@ -std=c++11 -lpthread
pollserver:tcp_poll_server.cc
	g++ $^ -o $@ -std=c++11 -lpthread
client:tcp_client.cc
	g++ $^ -o $@ -std=c++11 -lpthread;

.PHONY:clean
clean:
	rm client pollserver epollserver
