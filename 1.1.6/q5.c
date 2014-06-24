#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

char tabc[] = {'a', 'b', 'c'};
int n0 = 0, n1 = 1, n2 = 2, threadToInterrupt = 0;

pthread_t tabthread[3];

void
sigint_handler() {
	printf("Killing thread #%d", threadToInterrupt);
	pthread_cancel(tabthread[threadToInterrupt++]);
}

void*
start(void* ptn)
{
	int i = *(int*)ptn;
	int next = (i + 1) % 3;
	int sig;

    sleep(2);

	while(1)
	{
		printf("%d\n", i);
		sleep(1);
	}
}

int
main(int argc, char** argv)
{
	int sig, ret;

	sigset_t set;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);

    pthread_sigmask(SIG_BLOCK, &set, NULL);

	ret = pthread_create(&tabthread[0], NULL, start, &n0);
	ret += pthread_create(&tabthread[1], NULL, start, &n1);
	ret += pthread_create(&tabthread[2], NULL, start, &n2);

	if(ret < 0)
	{
		perror("Problème de création threads");
		exit(1);
	}

	printf("Waiting for interrupts\n");
	while(threadToInterrupt < 3)
	{
		sigwait(&set, &sig);

		if(sig == SIGINT)
		{
			sigint_handler();
		}
	}

	printf("Exiting main thread\n");

	return 0;
}