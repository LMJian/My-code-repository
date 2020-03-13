all:client server
server:server.cpp threadpool.cpp
	g++ server.cpp -o server -lpthread

client:client.cpp
	g++ client.cpp -o client

.PYONHY:clean
clean:
	rm server client
