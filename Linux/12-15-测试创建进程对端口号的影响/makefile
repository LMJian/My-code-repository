all:server client
server:dict_server.cc tcp_thread_server.hpp
	g++ $^ -o $@ -std=c++11 -lpthread
client:dict_client.cc
	g++ $^ -o $@ -std=c++11 -lpthread
