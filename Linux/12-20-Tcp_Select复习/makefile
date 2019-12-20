all:server client
server:tcp_server.cc
	g++ $^ -o $@ -std=c++11 -lpthread
client:tcp_client.cc
	g++ $^ -o $@ -std=c++11 -lpthread;

.PHONY:clean
clean:
	rm client server
