oj_server:oj_server.cc oj_model.hpp oj_view.hpp compile.hpp util.hpp
	g++ oj_server.cc -o oj_server -std=c++11 -lpthread \
	-ljsoncpp -lctemplate \
	-I ./third_part/include \
	-L ./third_part/lib

.PHONY:clean
clean:
	rm oj_server