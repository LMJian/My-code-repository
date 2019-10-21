all:fifo_read fifo_write
fifo_write:fifo_write.c
	gcc $^ -o $@
fifo_read:fifo_read.c
	gcc $^ -o $@
fifo:fifo.c
	gcc $^ -o $@
.PHONY:clean
clean:
	rm fifo
