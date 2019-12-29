all:insert select
select:select.cpp
	g++ $^ -o $@ -L/usr/lib64/mysql -lmysqlclient
insert:insert.cpp
	g++ $^ -o $@ -L/usr/lib64/mysql -lmysqlclient

.PHONY:clean
clean:
	rm insert select
