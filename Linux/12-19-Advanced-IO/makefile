all:client select
client:client.cpp;
	g++ $^ -o $@ -std=c++11
select:select.cpp
	g++ $^ -o $@ -std=c++11

.PHONY:clean;
clean:
	rm select
