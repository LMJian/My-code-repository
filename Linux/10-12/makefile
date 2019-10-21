all:shm_read   shm_write
shm_write:shm_write.c
	gcc $^ -o $@
shm_read:shm_read.c
	gcc $^ -o $@
pipe:pipe.c
	gcc $^ -o $@
.PHONY:clean
clean:
	rm pipe
