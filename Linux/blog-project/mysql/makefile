all:insert select;
select:select.cc
	g++ $^ -o $@ -L/usr/lib64/mysql  -lmysqlclient

insert:insert.cc
	g++ $^ -o $@ -L/usr/lib64/mysql  -lmysqlclient

.PHONY:clean
clean:
	rm insert select
