#include "winsock2.h"
#include "Strukture.h"
#include <stdio.h>


struct Queue* CreateQueue(unsigned kapacitet)
{
	struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
	queue->kapacitet = kapacitet;
	queue->prvi = queue->velicina = 0;
	queue->poslednji = kapacitet - 1;
	queue->niz = (TopicSub*)malloc(queue->kapacitet * sizeof(TopicSub));
	return queue;
}
int IsFull(struct Queue* queue)
{
	return (queue->velicina == queue->kapacitet);
}


int IsEmpty(struct Queue* queue)
{
	printf("Queue je prazan.\n");
	return (queue->velicina == 0);
}

void Enqueue(struct Queue* queue, char* tema)
{
	TopicSub ts;

	strcpy(ts.tema, tema);
	ts.velicina = 0;

	if (IsFull(queue)) {
		printf("Queue je pun, prosirujem...\n");
		ExpandQueue(queue);
	}
	queue->poslednji = (queue->poslednji + 1) % queue->kapacitet;
	queue->niz[queue->poslednji] = ts;
	queue->velicina = queue->velicina + 1;
	printf("%s Upisano u queue\n", ts.tema);
}

TopicSub Dequeue(struct Queue* queue)
{
	if (!IsEmpty(queue)) {
		TopicSub ts = queue->niz[queue->prvi];
		queue->prvi = (queue->prvi + 1) % queue->kapacitet;
		queue->velicina = queue->velicina - 1;
		printf("Izbacen iz queue-a.\n");
		return ts;
	}
}
int IsFullMessageQueue(struct MessageQueue* queue)
{
	return (queue->velicina == queue->kapacitet);
}

int IsEmptyMessageQueue(struct MessageQueue*  queue)
{
	printf("Queue poruka je prazan.\n");
	return (queue->velicina == 0);
}

void EnqueueMessageQueue(struct MessageQueue* queue, TopicMessage tema)
{
	if (IsFullMessageQueue(queue)) {
		printf("Queue poruka je pun, prosirujem...\n");
		ExpandMessageQueue(queue);
	}
	queue->poslednji = (queue->poslednji + 1) % queue->kapacitet;
	queue->niz[queue->poslednji] = tema;
	queue->velicina = queue->velicina + 1;
	printf("Poruka %s upisana u queue\n", tema.tema);
}

TopicMessage DequeueMessageQueue(struct MessageQueue* queue)
{
	if (!IsEmptyMessageQueue(queue)) {
		TopicMessage tm = queue->niz[queue->prvi];
		queue->prvi = (queue->prvi + 1) % queue->kapacitet;
		queue->velicina = queue->velicina - 1;
		printf("Poruka izbacena iz queue-a.\n");
		return tm;
	}
}

void ExpandQueue(struct Queue* queue) {
	queue->niz = (TopicSub*)realloc(queue->niz, queue->velicina * (sizeof(TopicSub)) + sizeof(TopicSub));
	queue->kapacitet += 1;
}

void ExpandMessageQueue(struct MessageQueue* queue) {
	queue->niz = (TopicMessage*)realloc(queue->niz, queue->velicina*(sizeof(TopicMessage)) + sizeof(TopicMessage));
	queue->kapacitet += 1;
}