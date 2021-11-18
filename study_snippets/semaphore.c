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

	index = *(int *)p_index;
	while (1)
	{
		usleep(200000);
		sem_wait(sem_test);
		str = index + '0';
		ft_putstr(str);
		sem_post(sem_test);
	}
	return;
}


void run_child(int index, pid_t *pid, sem_t *sem_test)
{
	*pid = fork();
	// printf("index: %d pid: %d\n", index, &pid);
	if (*pid == 0)
	{
		use_system(&index, sem_test);
			
		// char cindex = index + '0';
		// write(1, &cindex, 1);
		// exit(0);
	}
}

int main(void)
{
	pid_t pid;
	int num_users = 9;
	int status;

	sem_t *sem_test;
	int sem_value = 1;
	sem_unlink("sem_name");
	sem_test = sem_open("sem_name", O_CREAT | O_EXCL, 0644, sem_value);
	if (sem_test == SEM_FAILED)
		fprintf(stderr, "sem_open() failed.  errno:%d : %s\n", errno, strerror(errno));

	int u_index = 0;
	for (int i = 0; i < num_users; i++)
	{
		
		// usleep(200000);
		u_index++;
		run_child(u_index, &pid, sem_test);
		if (pid == 0)
			break;
		
	}
	
	if (pid > 0)
	{
		waitpid(pid, &status, WUNTRACED);
	}

	sem_unlink("sem_name");
	sem_close(sem_test);

}