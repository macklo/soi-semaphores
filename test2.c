#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h> 
#include <unistd.h>

#include "message.h"
#include "const.h"
#include "shm.h"
#include "sem.h"
#include "msgq.h"
#include "ex.h"

int memoryId[3];

struct queue* messageQueue[3];

int ms = 1000;
int *ex;
int exSemID;

int main(){
	ex = exInit();
	exSemID = semEXInit();
	printf("%d\n", *ex);
	int i = 1;
	while(i<10){
		down(exSemID, 0);
		if(*ex == 1) break;
		up(exSemID, 0 );
		printf("%d\n", i);
		usleep(ms*1000);
		i++;
	}

	semEXKill(exSemID);
	exKill(ex);
/*
	mFileID[0] = "AM";
	mFileID[1] = "BM";
	mFileID[2] = "CM";*/
	//char tmp[3] = mFileID[0];
	/*key_t mykey = getKey(mFileID[0]);
	printf("%s %d\n", mFileID[2], mykey);
*/
	/*char qID[3] = "CS";

	key_t key = getKey(qID);

	printf("%d\n", key);
	
	//int semid = semget(key, 3, IPC_CREAT);
	int semid = getSemID(key);
	if(semid != -1)
		printf("Utwo	rzono semafor %d\n", semid);

	int fl1 = removeSem(semid);//semctl (semid, 3 ,IPC_RMID, 0);
	if(fl1 != -1)
		printf("Usunieto semafor %d\n", semid);

*/
    /*struct queue *tmp;
    msgQInit(messageQueue);
    char teststr[4] = "AAA";
	struct message msgtest = createRandomMessage(0);
	//messageQueue[0]->queue[0] = msgtest;
	printf("%d %d\n", messageQueue[0]->first, messageQueue[0]->last);
    printf("%d %d\n", messageQueue[0]->empty, messageQueue[0]->full);
	putMessage(messageQueue[0], msgtest);
    printf("%s priority %d\n", messageQueue[0]->queue[0].str, messageQueue[0]->queue[0].priority);
    printf("%d %d\n", messageQueue[0]->first, messageQueue[0]->last);
    printf("%d %d\n", messageQueue[0]->empty, messageQueue[0]->full);
    msgQKill(messageQueue);*/


/*
	int shmid = getShmID(key);
	if(shmid != -1){
		printf("Utworzono pamiec dzielona %d\n", shmid);
	}

	tmp = attachShm(shmid);
	if(tmp!=NULL){
		printf("Przyłączono pamiec dzielona %d wskaznik %p\n", shmid,tmp);
	}

	char teststr[4] = "AAA";
	struct message msgtest = createMessage(teststr, 0);
	tmp->queue[0] = msgtest;
	printf("%s priority %d\n", tmp->queue[0].str, tmp->queue[0].priority);

	int f1;
	f1 = detachShm(tmp);
	if(f1!=-1){
		printf("Odlaczono segment pamieci %p\n", tmp);
	}

	
	int f2;
	f2 = removeShm(shmid);
	if(f2!=-1){
		printf("Usunieto segment pamieci %d\n", shmid);
	}

*/
	return 0;
}