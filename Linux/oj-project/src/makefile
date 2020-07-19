all:oj_server hello
hello:hello.cc
	g++ hello.cc -o hello -std=c++11
oj_server:oj_server.cpp
	g++ $^ -o $@ -g -L /root/ThirdPartLibForCpp/el7.x86_64/third_part/lib -lctemplate -ljsoncpp -lpthread -std=c++11

.PHONY:clean
clean:
		rm oj_server
