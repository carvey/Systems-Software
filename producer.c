/*
This file should create 2 threads which produce and create cupcakes in unison.
10 items should be produced, and consumers shold consume all 10 of these items
The produce should sleep 2 seconds after each produced product, and consumers should visit at random
*/
/*By (Group 1) Charles Arvey, Alexandria Sanders, Shannon Sergeant, Chris Hanson, and Garrett Edwards*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *produce(void *count);
void *consume(void *count);

int COUNT_MAX = 10;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;


int main()
{
	//set a seed for the random number generator
	srand(time(NULL));

	//the count variable will be used to track the number of items
	int count = 0;

	//Init the two threads
	pthread_t produce_thread;
	pthread_t consume_thread;

	//start each thread with its respective function as a start routine and pass it the memory address of count to mess with
	pthread_create(&produce_thread, NULL, produce, &count);
	pthread_create(&consume_thread, NULL, consume, &count);


	pthread_join(consume_thread, NULL);
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
		pthread_mutex_lock(&m);
		*count = ++(*count);
		printf("Produced! Count is now: %d\n", *count);
		pthread_mutex_unlock(&m);

		//sleep for 2 seconds
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
			//sleep is first here so that produce() and consume() don't both try and increment/decrement simultaneously at first
			sleep(rand() % 7);

			//decrement count
			pthread_mutex_lock(&m);
			*count = --(*count);
			printf("Consumed! Count is now: %d\n", *count);
			pthread_mutex_unlock(&m);

		}
	}

}
