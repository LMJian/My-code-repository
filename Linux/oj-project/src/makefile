all:test compile_server
compile_server:compile_server.cc compile.hpp
	g++ compile_server.cc -o compile_server -std=c++11 -lpthread -ljsoncpp
test:test.cc
	g++ test.cc -o test -std=c++11 -lpthread -ljsoncpp

.PHONY:clean
clean:
	rm test
