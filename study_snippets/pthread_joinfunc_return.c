#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void*	roll_dice()
{
	int value;
	int *result;
	
	value = (rand() % 6) + 1;
	result = malloc(sizeof(int));
	printf("%d\n", value);
	*result = value;
	return ((void*) result);
}

int main(int argc, char** argv)
{
	int* res;
	pthread_t t1;

	srand(time(NULL));
	// res = malloc(sizeof(int));
	if (pthread_create(&t1, NULL, &roll_dice, NULL))
	{
		return 1;
	}
	if (pthread_join(t1, (void**) &res))
	{
		return 3;
	}
	printf("Result %d\n", *res);
	free(res);
	return (0);
}