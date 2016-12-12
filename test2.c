#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h> 

#include "message.h"
#include "const.h"

int memoryId[3];

key_t getKey(char qID[2]){
	char src[8];
	strcpy(src, "files/");
	strcat(src, qID);
	key_t key;
	if ((key = ftok(src, 'p')) == -1) /*Here the file must exist */ 
	{
        return -1;
    }
    return key;
}

int getShmID(key_t key){
	int shmid = shmget(key, sizeof(struct queue), IPC_CREAT | 0660);
	return shmid;
}

struct queue* attachShm(int shmid){
	struct queue *q = (struct queue*)shmat(shmid,NULL,0);
	return q;
}

int detachShm(struct queue* q){
	int f = shmdt(q);
	return f;
}

int removeShm (int shmid){
	return shmctl(shmid, IPC_RMID, NULL);
}

struct queue messageQueue[3];

int main(){
	/*int semid = semget(45281,2, IPC_CREAT);
	if(semid != -1)
		printf("Utworzono semafor\n");
	printf("%d\n", semid);



	int i;
	for(i = 0; i<3; i++){
		int id = 45281;
		while (id){
			int shmid = shmget(45281-id, SIZE*sizeof(int), 0600);
			if(shmid != -1){
				printf("%d Utworzono pamiec dzielona %d\n", id, shmid);
				memoryId[i] = shmid;
				break;
			}
			id--;
		}
	}*/

	char qID[2] = C;

	key_t key = getKey(qID);

    printf("%d\n", key);

    /*size_t tmp = sizeof(struct queue);
    printf("%d\n", (int)tmp);*/

    struct queue *tmp;

	int shmid = shmget(key, sizeof(struct queue), IPC_CREAT | 0660);
	if(shmid != -1){
		printf("Utworzono pamiec dzielona %d\n", shmid);
	}

	int shmid1 = shmget(key, sizeof(struct queue), IPC_CREAT | IPC_EXCL | 0660);
	if(shmid1 != -1){
		printf("Utworzono pamiec dzielona %d\n", shmid);
	}

	tmp = (struct queue*)shmat(shmid,NULL,0);
	if(tmp!=NULL){
		printf("Przyłączono pamiec dzielona %d wskaznik %p\n", shmid,tmp);
	}

	int f1;
	f1 = shmdt(tmp);
	if(f1!=-1){
		printf("Odlaczono segment pamieci %p\n", tmp);
	}


	int f2;
	f2 = shmctl(shmid, IPC_RMID, NULL);
	if(f2!=-1){
		printf("Usunieto segment pamieci %d\n", shmid);
	}

	f2 = shmctl(shmid, IPC_RMID, NULL);
	if(f2!=-1){
		printf("Usunieto segment pamieci %d\n", shmid);
	}

	/*test*/

	return 0;
}