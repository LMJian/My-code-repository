all:server client test
test:test_inet_ntoa.cc
	g++ $^ -o $@ -std=c++11 -lpthread
server:dict_server.cc
	g++ $^ -o $@ -std=c++11
client:dict_client.cc
	g++ $^ -o $@ -std=c++11



