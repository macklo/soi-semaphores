#include "const.h"
#include <string.h>

struct message { 
	char str[4];
	int priority;
};

struct queue {
	struct message queue[SIZE];
	int first;
	int last;
	int empty;
	int full;
};

struct message popMessage(struct queue *q){
	if (!q->empty){
		struct message tmp = q->queue[q->first];
		q->first++;
		q->first = q->first%SIZE;
		q->full = 0;
		if(q->first == q->last)
			q->empty = 1;
		return tmp;
	}
}

int putMessage (struct queue *q, struct message msg){
	if(!q->full){
		q->queue[q->last] = msg;
		q->last++;
		q->last = q->last%SIZE;
		q->empty = 0;
		if (q->last == q->first)
			q->full = 1;
		return 0;
	}
	return -1;
}

void initQ(struct queue *q){
	q->empty = 1;
	q->full = 0;
	q->first = 0;
	q->last = 0;
}

struct message createMessage(char str[4], int pri){
	struct message msg;
	strcpy(msg.str, str);
	msg.priority = pri;
	return msg;
}