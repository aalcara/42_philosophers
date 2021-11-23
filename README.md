# 42_philosophers

the objective of this project is to solve the `dinning philosophres` problem, using multi-thread and mutex in C.
In this project I could have the first contact with multi-thread, mutex and semaphores and deepen knowledge in multi-process.

## Mandatory Part

### Description

- Each philosopher is a thread;
- One fork between each philosopher, protected by mutex.
- Allowed Functions : memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, thread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock;

### usage

in `philo` directory:

```bash
//to create executable philo file
make

//to run the program
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## Bonus Part

### Description

- Each philosopher is a process in addition to the main process;
- All the forks in the middle of the table, protected by only one semaphore;
- Allowed Functions:  memset, printf, malloc, free, write, fork, kill, exit, pthread_create, pthread_detach, pthread_join, usleep, gettimeofday, waitpid, sem_open, sem_close, sem_post, sem_wait, sem_unlink.

### usage

in `philo_bonus` directory:

```bash
//to create executable philo file
make

//to run the program
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]