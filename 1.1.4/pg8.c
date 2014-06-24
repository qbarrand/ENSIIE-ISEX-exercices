#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>	
#include <unistd.h>

int pipe_child[2], parent_pid, child_pid;

/*
 * Signal handling functions
 */

void
SIGPIPE_parent_handler(int sig)
{
	printf("SIGPIPE\n");
	exit(0);
}

void
SIGUSR1_child_handler(int sig)
{
	// Send SIGUSR2 to parent
	printf("Child received SIGUSR1, sending SIGUSR2 to parent\n");
	kill(parent_pid, SIGUSR2);
	exit(1);
	// pause();
}

void
SIGUSR2_parent_handler(int sig)
{
	char B;
	int i;

	B = 'B';
	i = 0;

	// Pipe overflow handling
	signal(SIGPIPE, SIGPIPE_parent_handler);

	printf("Parent received SIGUSR2, stopping child and starting writing B's in pipe\n");

	while(write(pipe_child[1], &B, sizeof(char)) > 0)
	{
		printf("B sent %d times\n", ++i);
	}

	// Never reached as write is blocking
}

/*
 * Child functions
 */

int
child()
{
	child_pid = getpid();
	printf("Child (PID %d) alive\n", child_pid);

	// Close the write side of the inherited pipes so read() can return 0
	close(pipe_child[1]);

	// Catch SIGUSR1
	signal(SIGUSR1, SIGUSR1_child_handler);

	int bytes_read;

	while(read(pipe_child[0], &bytes_read, sizeof(int))> 0)
	{

		if(bytes_read == 0)
		{
			break;
		}

		printf("Child : read %d\n", bytes_read);
	}

	printf("Child (PID %d, PPID %d) dying in 5s\n", child_pid, parent_pid);
	sleep(5);
	exit(0);
}

/*
 * Main
 */

int
main(int argc, char** argv)
{
	int nb_read, child_pid;

	parent_pid = getpid();

	// signal handling
	signal(SIGUSR2, SIGUSR2_parent_handler);
	signal(SIGPIPE, SIGPIPE_parent_handler);

	if(pipe(pipe_child) == -1)
	{
		perror("pipe_child");
		exit(EXIT_FAILURE);
	}

	// Fork
	switch(child_pid = fork())
	{
		case -1:
			perror("fork_son");
			exit(EXIT_FAILURE);

		case 0:
			child();
	}

	close(pipe_child[0]);

	printf("Entrez des nombres :\n");

	while(scanf("%d",&nb_read) != EOF) 
	{
		if(nb_read == 5)
		{
			// send SIGUSR1
			printf("Sending SIGUSR1 to child #%d\n", child_pid);
			kill(child_pid, SIGUSR1);
		}
		else
		{
			printf("Sending %d to son\n", nb_read);
			write(pipe_child[1], &nb_read, sizeof(int));
		}
	}

	nb_read = 0;

	// Close write side of the pipe in the parent process
	close(pipe_child[1]);	

	printf("Parent process waiting for his sons to exit\n");
	wait(NULL);

	printf("Parent process exiting\n");
	return 0;
}