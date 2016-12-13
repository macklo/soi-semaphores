#ifndef EX_H
#define EX_H

#include "shm.h"
#include "const.h"

int* exInit(){
	int *ex;
	key_t key = getKey(exFileID);
	int shmid = shmget(key, sizeof(int), IPC_CREAT | 0660);
	if(shmid != -1)
		printf("Utworzono segment ex %d\n", shmid);
	ex = (int*)shmat(shmid,NULL,0);
	if(ex != NULL)
		printf("Dolaczono segment ex %d wskaznik %p\n",shmid, ex);
	return ex;
}

void exKill (int *ex){
	key_t key = getKey(exFileID);
	int shmid = shmget(key, sizeof(int), IPC_CREAT | 0660);
	int f1 = shmdt(ex);
	if(f1 != -1)
		printf("Odlaczono segment ex %p\n", ex);
	
	int f2 = shmctl(shmid, IPC_RMID, NULL);
	if(f2 != -1){
		printf("Usunieto segment ex %d\n", shmid);
	}
}

#endif