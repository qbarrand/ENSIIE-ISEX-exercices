#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void fils(int father_pid, int fork_value)
{
	sleep(5);

	printf("PID : %d\tFather PID : %d (now : %d)\tFork value : %d\n",
		getpid(),
		father_pid,
		getppid(),
		fork_value);

	exit(0);
}

int main(int argc, char** argv)
{
	int father_pid, fork_value, i;

	father_pid = getpid();

	for(i = 0; i < 2; i++)
	{
		switch(fork_value = fork())
		{
			case -1: 
				perror("Echec du fork");
				exit(1);
				break;

			case 0:
				fils(father_pid, fork_value);
				break;
		}
	}

	printf("Dying, son processes will print stuff in 5s\n");
	return 0;
}