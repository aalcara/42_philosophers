#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putstr(char str)
{
	
	ft_putchar('u');
	ft_putchar('s');
	ft_putchar('e');
	ft_putchar('r');
	ft_putchar(str);
	ft_putchar(' ');
	ft_putchar('i');
	ft_putchar('s');
	ft_putchar(' ');
	ft_putchar('u');
	ft_putchar('s');
	ft_putchar('i');
	ft_putchar('n');
	ft_putchar('g');
	ft_putchar(' ');
	ft_putchar('t');
	ft_putchar('h');
	ft_putchar('e');
	ft_putchar(' ');
	ft_putchar('s');
	ft_putchar('y');
	ft_putchar('s');
	ft_putchar('t');
	ft_putchar('e');
	ft_putchar('m');
	ft_putchar('\n');
}

void *use_system(void *p_index)
{
	int index;
	char str;
	sem_t sem_test;

	sem_test = *sem_open("sem_name", 1);
	if (&sem_test == SEM_FAILED)
		printf("Error opening Semaphore");

	index = *(int *)p_index;
	while (1)
	{
		sem_wait(&sem_test);
		if (index == 1)
			str = '1';
		else
			str = '2';
		// sleep(1);
		ft_putstr(str);
		sem_post(&sem_test);
	} 

	sem_close(&sem_test);
	sem_unlink("sem_name");
	return NULL;
}

int main(void)
{
	pthread_t user1;
	pthread_t user2;
	
	int u_ind1 = 1;
	int u_ind2 = 2;

	int *u_index1 = &u_ind1;
	int *u_index2 = &u_ind2;


	pthread_create(&user1, NULL, &use_system, u_index1);
	pthread_create(&user1, NULL, &use_system, u_index2);


	pthread_join(user1, NULL);
	pthread_join(user2, NULL);

}