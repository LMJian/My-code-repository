all:fifo_read fifo_write pipe2 pipe 
fifo_write:fifo_write.c
	gcc $^ -o $@
fifo_read:fifo_read.c
	gcc $^ -o $@
pipe:pipe.c
	gcc $^ -o $@
pipe2:pipe2.c
	gcc $^ -o $@
.PHONY:clean
clean:
	rm fifo
