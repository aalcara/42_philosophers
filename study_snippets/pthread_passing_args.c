#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

char* primes[10] = {".", "..", "...", "....", ".....", "......", ".......",
"........", ".........", ".........."};


void *routine(void* arg)
{
	int index = *(int*)arg;
	printf("%s\n",primes[index]);
	free(arg);
}

int main(int argc, char **argv)
{
	pthread_t th[10];
	int i = 0;
	int j = 0;

	while (i < 10)
	{
		usleep(600);
		int* a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a))
		{
			perror("Failed to create thread");
			return 1;
		}
		i++;
	}
	while (j < 10)
	{
		if (pthread_join(th[j], NULL))
		{
			perror("Failed to end thread");
			return 2;
		}
		j++;
	}
	return (0);
}