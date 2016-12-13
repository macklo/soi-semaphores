#ifndef SEM_H
#define SEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h> 

#include "const.h"
#include "message.h"
#include "shm.h"

static struct sembuf buf;

int up(int semid, int semnum){
	buf.sem_num = semnum;
	buf.sem_op = 1;
	buf.sem_flg = 0;
	if (semop(semid, &buf, 1) == -1)
		return -1;
	return 0;
}

int down(int semid, int semnum){
	buf.sem_num = semnum;
	buf.sem_op = -1;
	buf.sem_flg = 0;
	if (semop(semid, &buf, 1) == -1)
		return -1;
	return 0;
}

int getSemID(key_t key){
	int tmp = semget(key, 3, IPC_CREAT|0660);
	return tmp;
}

int removeSem(int semid){
	int tmp = semctl(semid, 3 ,IPC_RMID, 0);
	return tmp;
}

void semIDInit(int *semID){
	int i = 0;
	for(i=0;i<3;i++){
		key_t key = getKey(sFileID[i]);
		int semid = semget(key, 3, IPC_CREAT|IPC_EXCL|0660);

		if(semid != -1){
			printf("Utworzono semafor %d\n", semid);
			if (semctl(semid, 0, SETVAL, (int)SIZE) != -1){
				printf("Nadanie wartosci semaforowi 0 empty\n");
			}
			if (semctl(semid, 1, SETVAL, (int)0) != -1){
				printf("Nadanie wartosci semaforowi 1 full\n");
			}
			if (semctl(semid, 2, SETVAL, (int)1) != -1){
				printf("Nadanie wartosci semaforowi 2 mutex\n");
			}
		}
		else{
			semid = semget(key, 3, IPC_CREAT|0660);
			if(semid != 0)
				printf("Pobrano semafor %d\n", semid);
		}
		semID[i] = semid;
	}
}

void semIDKill(int *semID){
	int i = 0;
	for(i=0;i<3;i++){
		int f1 = removeSem(semID[i]);
		if(f1 != -1){
			printf("Usunieto semafor %d\n", semID[i]);
		}
	}
}

int semEXInit(){
	key_t key = getKey(exFileID);
	int semid = semget(key, 1, IPC_CREAT|IPC_EXCL|0660);
	if(semid != -1){
		printf("Utworzono semafor %d\n", semid);
		if (semctl(semid, 0, SETVAL, (int)1) != -1){
				printf("Nadanie wartosci semaforowi 0 mutex\n");
		}
	}
	else{
		semid = semget(key, 1, IPC_CREAT|0660);
		if(semid != -1)
			printf("Pobrano semafor ex %d\n", semid);
	}
	return semid;
}

void semEXKill(int semid){
	int tmp = semctl(semid, 1 ,IPC_RMID, 0);
	if(tmp != -1){
		printf("Usunieto semafor %d\n", semid);
	}
}

#endif