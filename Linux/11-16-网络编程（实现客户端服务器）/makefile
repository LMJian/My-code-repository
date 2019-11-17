all:server client
client:testClient.cc
	g++ $^ -o $@
server:testServer.cc
	g++ $^ -o $@

.PHONY:clean
clean:
	rm server
