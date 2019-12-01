all:calc_server calc_client
calc_server:calc_server.cc
	g++ $^ -o $@ -std=c++11 -lpthread -ljsoncpp
calc_client:calc_client.cc
	g++ $^ -o $@ -std=c++11 -lpthread -ljsoncpp

.PHONY:clean
clean:
	rm calc_client  calc_server
