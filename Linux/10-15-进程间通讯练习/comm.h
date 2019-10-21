#ifndef COMM_H

#define COMM_H
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define PATHNAME "."
#define PROJ_ID 0x6666

int createShm(int size);
int destroyShm(int shmid);
int getShm(int size);

#endif
