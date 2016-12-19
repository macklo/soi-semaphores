#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h> 
#include <unistd.h>

#include "const.h"
#include "message.h"
#include "shm.h"
#include "sem.h"
#include "msgq.h"
#include "ex.h"

int ms = 1000;

struct queue* messageQueue[3];
int semID[3];

int *ex;
int exSemID;

int pFirst[3];
int pLast[3];
int printFlag = 0;




int main(int argc, char * argv[]){
	if(argc!=2){
		printf("No arguments\n");
		return 0;
	}

	msgQInit(messageQueue);
	semIDInit(semID);

	ex = exInit();
	exSemID = semEXInit();


	while (1){
		/*Chcek if exit*/
		down(exSemID, 0);
		if(*ex == 1) break;
		up(exSemID, 0 );
		//printf("check\n");


		int i = 0;
		while(i<3){
			down(semID[i], MUTEX);
			if(messageQueue[i]->first != pFirst[i] ){
				pFirst[i] = messageQueue[i]->first;
				printf("flag\n");
				printFlag = 1;
			}
			if(messageQueue[i]->last != pLast[i] ){
				pLast[i] = messageQueue[i]->last;
				printf("flag\n");
				printFlag = 1;
			}
			up(semID[i], MUTEX);
			i++;
		}
		if(printFlag){
			printFlag = 0;
			int j = 0;
			printf("\033[2J\033[1;1H");
			while(j<3){
				struct queue* q = messageQueue[j];
				if(q->empty) {
					printf("\n");
					j++;
					continue;
				}
				int i = q->first;
				do{
					printf("%-3s %d  ", q->queue[i].str, q->queue[i].priority);
					i = i+1;
					i = i%SIZE;
				}while (i!= q->last);
				printf("\n");
				j++;

			}
		}


	}

/*
	semEXKill(exSemID);
	exKill(ex);

	semIDKill(semID);
	msgQKill(messageQueue);
*/
	return 0;
}