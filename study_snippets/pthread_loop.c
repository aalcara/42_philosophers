#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void	*routine()
{
	int i = 0;
	
	while (i < 10000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		i++;
		pthread_mutex_unlock(&mutex);
	}
}

int main(int argc, char **argv)
{
	pthread_t th[8];
	int i = 0;

	pthread_mutex_init(&mutex, NULL);
	while (i < 8)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL))
		{
			perror("Failed to  create a thread");
			return 1;
		}
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (pthread_join(th[i], NULL))
			return 2;
		printf("Thread %d has finished execution\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}