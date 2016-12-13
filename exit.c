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

int *ex;
int exSemID;

int main(){
	ex = exInit();
	exSemID = semEXInit();

	printf("%d\n", *ex);

	down(exSemID, 0);
	*ex = 1;
	up(exSemID, 0 );

	printf("%d\n", *ex);

	semEXKill(exSemID);
	exKill(ex);

	return 0;
}