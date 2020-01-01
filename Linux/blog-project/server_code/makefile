all:db_test blog_server
FLAG=-std=c++11 -L/usr/lib64/mysql -lmysqlclient -ljsoncpp -lpthread

.PHONY:all
db_test:db_test.cc db.hpp
	g++ db_test.cc -o db_test $(FLAG)

blog_server:blog_server.cc;
	g++ blog_server.cc -o blog_server $(FLAG)
	
.PHONY:clean
clean:
	rm db_test blog_server
