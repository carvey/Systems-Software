/*
This file should create 2 threads which produce and create cupcakes in unison.
10 items should be produced, and consumers shold consume all 10 of these items
The produce should sleep 2 seconds after each produced product, and consumers should visit at random
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *produce(void *count);
void *consume(void *count);

int COUNT_MAX = 10;


int main()
{
	//set a seed for the random number generator
	srand(time(NULL));

	int count = 0;

	//Init the two threads
	pthread_t produce_thread;
	pthread_t consume_thread;

	//start each thread with its respective function as a start routine and pass it the memory address of count to mess with
	pthread_create(&produce_thread, NULL, produce, &count);
	pthread_create(&consume_thread, NULL, consume, &count);


	if (pthread_join(consume_thread, NULL)) {
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}
	printf("Final count (for confirmation): %d\n", count);
}

//This function will increment count up to 10 with 2 seconds inbetween each increment
void *produce(void *counter)
{
	//this is cast to an int pointer the pthread_create needs to be have a void function and the arg needs to void
	int *count = (int *)counter;
	int i;
	for (i = 0; i < COUNT_MAX; ++i)
	{
		//increment count
		*count = ++(*count);
		printf("Produced! Count is now: %d\n", *count);
		sleep(2);
	}
	return NULL;
}

//This function will decrement count to 0 with random intervals (between 0-6 seconds)
//If the count is 0, the loop will keep checking until the count is not 0. Then it will sleep -> decrement -> print
void *consume(void *counter)
{
	int *count = (int *)counter;
	int i; 
	for (i=0; i < COUNT_MAX; i++)
	{
		if (*count == 0)
		{
			i--;
			continue;
		}
		else
		{
			//sleep a random num of second between 0 and 6
			sleep(rand() % 7);
			//decrement count
			*count = --(*count);
			printf("Consumed! Count is now: %d\n", *count);
		}
	}

}