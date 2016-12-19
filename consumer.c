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
int priCount = 0;
int putQID;


int main(int argc, char * argv[]){
	/*Check for arguments*/
	if(argc!=2){
		printf("No arguments\n");
		return 0;
	}
	else{
		qID = atoi(argv[1]);
	}
	printf("qID: %d, pri: %d\n", qID, pri);

	srand(time(NULL));

	msgQInit(messageQueue);
	semIDInit(semID);

	ex = exInit();
	exSemID = semEXInit();

	struct message msg;
	
	char c;

	while (1){
		down(exSemID, 0);
		if(*ex == 1) break;
		up(exSemID, 0 );

		//printf("\n");
		//printf("waiting\n");

		down(semID[qID], FULL);
		//printf("msg recieved\n");
		down(semID[qID], MUTEX);

		msg = popMessage(messageQueue[qID]);
		//printf("%s\n", messageQueue[qID]->queue[0].str);
		//printf("%s\n", msg.str);

		up(semID[qID], MUTEX);
		up(semID[qID], EMPTY);

		usleep(ms*1000);
		//printf("%s\n", msg.str);
		c = msg.str[0];
		//printf("%c\n", c);

		if(c == '\0')
			continue;
		putQID = c - 65;
		//printf("%d\n", putQID);

		if(msg.priority == 1){
			int i = 0;
			while(i<3 && msg.str[i+1] != '\0'){
				msg.str[i] = msg.str[i+1];
				i++;
			}
			if(priCount == 0)
				msg.str[i] = getRandomLetter();
			else{
				msg.str[i] = '\0';
				priCount--;
			}
		}
		else{
			priCount = priCount + 10;
			int i = 0;
			while(i<3 && msg.str[i+1] != '\0'){
				msg.str[i] = msg.str[i+1];
				i++;
			}
			msg.str[i] = '\0';
		}
		//printf("%s\n", msg.str);

		down(semID[putQID], EMPTY);
		down(semID[putQID], MUTEX);
		//printf("test3\n");
		putMessage(messageQueue[putQID], msg);
		//printQ(messageQueue[putQID]);
		up(semID[putQID], MUTEX);
		up(semID[putQID], FULL);

	}
	semEXKill(exSemID);
	exKill(ex);

	semIDKill(semID);
	msgQKill(messageQueue);
	return 0;
}