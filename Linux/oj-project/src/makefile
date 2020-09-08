oj_server:oj_server.cc oj_model.hpp oj_view.hpp
	g++ oj_server.cc -o oj_server -std=c++11 -lpthread \
	-ljsoncpp -lctemplate \
	-I ./ThirdPartLibForCpp/el7.x86_64/third_part/include \
	-L ./ThirdPartLibForCpp/el7.x86_64/third_part/lib

compile_server:compile_server.cc compile.hpp
	g++ compile_server.cc -o compile_server -std=c++11 -lpthread -ljsoncpp
test:test.cc
	g++ test.cc -o test -std=c++11 -lpthread -ljsoncpp

.PHONY:clean
clean:
	rm test
