all:server client
client:client.cc;
	g++ client.cc -o client
server:server.cc
	g++ server.cc -o server

.PHONY:clean
clean:
	rm server
	rm client
