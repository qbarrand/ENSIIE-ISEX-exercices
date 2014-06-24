#include <stdio.h>
#include <stdlib.h>	
#include <unistd.h>

int pipe_son0[2];
int pipe_son1[2];

// Pairs
int son0()
{
	printf("Son0 (PID %d) alive\n", getpid());

	int bytes_read;

	while(read(pipe_son0[0], &bytes_read, sizeof(int)) > 0)
	{
		if(bytes_read == 0)
		{
			break;
		}

		printf("Son 0: read %d\n", bytes_read);
	}

	printf("Son0 (PID %d, PPID %d) dying in 5s\n", getpid(), getppid());
	sleep(5);
	exit(0);
}

//Impairs
int son1()
{
	printf("Son1 (PID %d) alive\n", getpid());

	int bytes_read;

	while(read(pipe_son1[0], &bytes_read, sizeof(int)) > 0)
	{
		if(bytes_read == 0)
		{
			break;
		}

		printf("Son 1: read %d\n", bytes_read);
	}

	printf("Son1 (PID %d, PPID %d) dying in 5s\n", getpid(), getppid());
	sleep(5);
	exit(0);
}

int main(int argc, char** argv)
{
	int nb_read;

	if(pipe(pipe_son0) == -1)
	{
		perror("pipe_son0");
		exit(EXIT_FAILURE);
	}

	if(pipe(pipe_son1) == -1)
	{
		perror("pipe_son1");
		exit(EXIT_FAILURE);
	}

	// Son0
	switch(fork())
	{
		case -1:
			perror("fork_son0");
			exit(EXIT_FAILURE);

		case 0:
			son0();
	}

	// Son1
	switch(fork())
	{
		case -1:
			perror("fork_son1");
			exit(EXIT_FAILURE);

		case 0:
			son1();
	}

	printf("Entrez des nombres :\n");

	while(scanf("%d",&nb_read) != EOF) 
	{
		if(nb_read % 2 == 0)
		{
			if(nb_read == 0)
			{
				break;
			}

			printf("Sending %d to son0\n", nb_read);
			write(pipe_son0[1], &nb_read, sizeof(int));
		}
		else
		{
			printf("Sending %d to son1\n", nb_read);
			write(pipe_son1[1], &nb_read, sizeof(int));
		}
	}

	nb_read = 0;

	// Send 0 to sons so they kill themselves
	write(pipe_son0[1], &nb_read, sizeof(int));
	write(pipe_son1[1], &nb_read, sizeof(int));

	printf("Parent process waiting for his sons to exit\n");
	wait(NULL);

	printf("Parent process exiting\n");
	return 0;
}