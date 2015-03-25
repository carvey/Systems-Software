#include <pthread.h>

void produce(int count);
void consume(int count);

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
COUNT_MAX = 10;

int main()
{

int count = 0;

pthread_t produce_thread;
pthread_t consume_thread;

pthread_create(&produce_thread, NULL, produce, count);

pthread_create(&consume_thread, NULL, consume, count);


}

void produce(int count)
{

	if (++count <= COUNT_MAX)
	{
		
	}

}


void consume(int count)
{



}