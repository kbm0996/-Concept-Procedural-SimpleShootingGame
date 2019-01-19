#include "Queue.h"

int Queue[dfMAX_QUEUE];

int Front = 0;
int Rear = 0;
int Temp = 0;

bool Enqueue(int iInData)
{
	if ((Rear + 1) % dfMAX_QUEUE == Front)
		return false;
	Rear = (Rear + 1) % dfMAX_QUEUE;
	Queue[Rear] = iInData;
	return true;
}

bool Dequeue(int *pOutData)
{
	if (Front == Rear)
		return false;
	Front = (Front + 1) % dfMAX_QUEUE;
	*pOutData = Queue[Front];
	return true;
}

bool Peek(int *pOutData)
{
	if (Front == Rear)
		return false;
	*pOutData = Queue[Front];
	return true;
}