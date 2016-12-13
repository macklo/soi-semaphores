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
#include "sem.h"
#include "msgq.h"

struct queue* messageQueue[3];
int semID[3];

int main(){
	srand(time(NULL));

	msgQInit(messageQueue);
	semIDInit(semID);
	struct message msg;
	while (messageQueue[0]->full != 1){
		msg = createRandomMessage(0);
		down(semID[0], EMPTY);
		down(semID[0], MUTEX);
		putMessage(messageQueue[0], msg);
		up(semID[0], MUTEX);
		up(semID[0], FULL);
	}
	// popMessage(messageQueue[0]);
	printf("%d %d\n", messageQueue[0]->full, messageQueue[0]->empty);
	printf("%d %d\n", messageQueue[0]->first, messageQueue[0]->last);
	printQ(messageQueue[0]);
	semIDKill(semID);
	msgQKill(messageQueue);
	return 0;
}