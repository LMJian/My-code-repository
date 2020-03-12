all:pro_server client thr_server
pro_server:process_server.cpp tcp.hpp
	g++ process_server.cpp -o pro_server

thr_server:thread_server.cpp tcp.hpp
	g++ thread_server.cpp -o thr_server -lpthread

client:client.cpp tcp.hpp
	g++ client.cpp -o client

.PYONHY:clean
clean:
	rm pro_server client
