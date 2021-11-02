// gcc -pthread create_and_join.c && ./a.out

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *myturn() {
	int i;
	for (i = 0; i < 5; i++) {
		sleep(1);
		printf("My turn!\n");
	}
	return NULL;
}

void yourturn() {
	int i;
	for (i = 0; i < 4; i++) {
		sleep(2);
		printf("Your turn!\n");
	}
}

int main() {
	pthread_t newthread;

	// printf("Start!\n");
	pthread_create(&newthread, NULL, myturn, NULL);
	// myturn();
	pthread_join(newthread, NULL);
	yourturn();


	return 0;

}