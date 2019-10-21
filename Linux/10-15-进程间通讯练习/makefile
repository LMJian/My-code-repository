all:testpipe shell mkfifo_read mkfifo_write clientPipe serverPipe client server shm_read shm_write
shm_read:shm_read.c
	gcc $^ -o $@
shm_write:shm_write.c
	gcc $^ -o $@
client:client.c comm.c
	gcc $^ -o $@
server:server.c comm.c
	gcc $^ -o $@
clientPipe:clientPipe.c
	gcc $^ -o $@
serverPipe:serverPipe.c
	gcc $^ -o $@
mkfifo_read:mkfifo_read.c
	gcc $^ -o $@
mkfifo_write:mkfifo_write.c
	gcc $^ -o $@
shell:shell.c
	gcc $^ -o $@
testpipe:testpipe.c
	gcc $^ -o $@

.PHONY:clean
clean:
	rm testpipe
	rm shell
