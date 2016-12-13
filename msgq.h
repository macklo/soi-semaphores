#ifndef MSGQ_H
#define MSGQ_H

#include "const.h"
#include "message.h"
#include "shm.h"

void msgQInit(struct queue **q){
	int i = 0;
	for(i=0;i<3;i++){
		key_t key = getKey(mFileID[i]);
		int shmid = getShmID(key);
		if(shmid != -1){
			printf("Utworzono pamiec dzielona %d\n", shmid);
		}
		q[i] = attachShm(shmid);
		if(q[i]!=NULL){
			printf("Przyłączono pamiec dzielona %d wskaznik %p\n", shmid,q[i]);
		}
		initQ(q[i]);
	}
}

void msgQKill(struct queue **q){
	int i = 0;
	for(i=0;i<3;i++){
		key_t key = getKey(mFileID[i]);
		int shmid = getShmID(key);
		int f1;
		f1 = detachShm(q[i]);
		if(f1!=-1){
			printf("Odlaczono segment pamieci %p\n", q[i]);
		}
		int f2;
		f2 = removeShm(shmid);
		if(f2!=-1){
			printf("Usunieto segment pamieci %d\n", shmid);
		}
	}
}

#endif