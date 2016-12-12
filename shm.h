#include "const.h"
#include "message.h"

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