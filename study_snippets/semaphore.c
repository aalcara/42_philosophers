#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <errno.h>
#include <string.h>

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

void use_system(void *p_index, sem_t *sem_test)
{
	int index;
	char str;
	int i = 0;

	index = *(int *)p_index;
	while (i++ < 2)
	{
		usleep(200000);
		sem_wait(sem_test);
		// str = index + '0';
		// ft_putstr(str);
		printf("user [%d] is using the system\n", getpid());
		sem_post(sem_test);
	}
	return;
}


void run_child(int index, pid_t *pid, sem_t *sem_test)
{
	pid[index] = fork();
	// printf("index: %d pid: %d\n", index, &pid);
	if (pid[index] == 0)
	{
		use_system(&index, sem_test);
		// char cindex = index + '0';
		// write(1, &cindex, 1);
		exit(0);
	}
}
#define SEM_FLAGS O_CREAT | O_EXCL

int main(void)
{
	pid_t pid[10];
	int num_users = 9;
	int status;

	sem_t *sem_test;
	int sem_value = 1;
	sem_unlink("sem_name");
	sem_test = sem_open("sem_name", SEM_FLAGS, 0644, sem_value);
	if (sem_test == SEM_FAILED)
		fprintf(stderr, "sem_open() failed.  errno:%d : %s\n", errno, strerror(errno));

	for (int i = 0; i < num_users; i++)
	{
		
		// usleep(200000);
		// printf("%d\n", i);
		run_child(i, pid, sem_test);
	}


	for (int i = 0; i < num_users; i++)
	{
		// printf("%d\n", i);
		pid_t waiter = waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			printf("Child %d terminated with status: %d. [%d][%d]\n",waiter, WEXITSTATUS(status), pid[i], getpid());
	}

	sem_unlink("sem_name");
	sem_close(sem_test);
	printf("fim\n");
}