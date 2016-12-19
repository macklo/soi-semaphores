#ifndef MESSAGE_H
#define MESSAGE_H

#include <time.h>
#include <stdlib.h>

#include "const.h"
#include <string.h>
#include <stdio.h>

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
		if(q->empty){
			q->queue[q->first] = msg;
			q->last++;
			q->last = q->last%SIZE;
			q->empty = 0;
		}
		else if(msg.priority == 1){
			q->queue[q->last] = msg;
			q->last++;
			q->last = q->last%SIZE;
			q->empty = 0;
		}
		else{

			if(q->queue[q->first].priority == 1){
				if (q->first == 0) q->first = SIZE - 1;
				else q->first = q->first - 1;
				q->queue[q->first] = msg;
			}
			else{
				int i = q->first;
				int toSave;
				if (q->first == 0) toSave = SIZE - 1;
				else toSave = q->first - 1;
				while ( q->queue[i].priority == 0 && i!=q->last){
					//printf("i: %d, toSave: %d\n",i, toSave);
					q->queue[toSave] = q->queue[i];
					toSave++;
					i++;
					toSave = toSave % SIZE;
					i = i % SIZE;
				}
				if (q->first == 0) q->first = SIZE - 1;
				else q->first = q->first - 1;
				q->queue[toSave] = msg;
			}
		}
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

struct message createRandomMessage(int pri){
	char str[4];
	int i;
	for (i = 0; i<3; i++){
		int r = rand()%3;
		char c = 65+r;
		str[i] = c;
	}
	str[3] = '\0';
	struct message msg;
	strcpy(msg.str, str);
	msg.priority = pri;
	return msg;
}

void printQ(struct queue *q){
	int i;
	int last;
	if(q->empty) return;
	i = q->first;
	do{
		printf("%s %d\n", q->queue[i].str, q->queue[i].priority);
		i = i+1;
		i = i%SIZE;
	}while (i!= q->last);

}

char getRandomLetter(){
	int r = rand()%3;
	char c = 65+r;
	return c;
}


#endif