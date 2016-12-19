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

	srand(time(NULL));

	msgQInit(messageQueue);
	semIDInit(semID);
	int i;
	for (int i = 0; i < 1; ++i)
	{
		struct message msg;

		msg = createRandomMessage(pri);
		down(semID[qID], EMPTY);
		down(semID[qID], MUTEX);
		putMessage(messageQueue[qID], msg);
		printQ(messageQueue[qID]);
		printf("\n");
		up(semID[qID], MUTEX);
		up(semID[qID], FULL);
	}

	semEXKill(exSemID);
	exKill(ex);

	semIDKill(semID);
	msgQKill(messageQueue);
	return 0;
}