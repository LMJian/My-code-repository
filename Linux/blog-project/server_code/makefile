all:db_test
db_test:db_test.cc db.hpp
	g++ $^ -o $@ -std=c++11 -L/usr/lib64/mysql -lmysqlclient -ljsoncpp

.PHONY:clean
clean:
	rm db_test
