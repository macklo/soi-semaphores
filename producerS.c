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

int qID;
int pri;

int main(int argc, char * argv[]){
	/*Check for arguments*/
	if(argc!=3){
		printf("No arguments\n");
		return 0;
	}
	else{
		qID = atoi(argv[1]);
		pri = atoi(argv[2]);
	}
	printf("qID: %d, pri: %d\n", qID, pri);

	srand(time(NULL) + qID+pri*3);

	msgQInit(messageQueue);
	semIDInit(semID);

	ex = exInit();
	exSemID = semEXInit();

	struct message msg;

	while (1){
		/*Chcek if exit*/

		msg = createRandomMessage(pri);
		down(semID[qID], EMPTY);
		down(semID[qID], MUTEX);
		putMessage(messageQueue[qID], msg);
		printQ(messageQueue[qID]);
		printf("%d %d\n", messageQueue[qID]->first, messageQueue[qID]->last);
		up(semID[qID], MUTEX);
		up(semID[qID], FULL);

		down(exSemID, 0);
		if(*ex == 1) break;
		up(exSemID, 0 );
		printf("\n");

		usleep(ms*3000);
	}
	semEXKill(exSemID);
	exKill(ex);

	semIDKill(semID);
	msgQKill(messageQueue);
	return 0;
}