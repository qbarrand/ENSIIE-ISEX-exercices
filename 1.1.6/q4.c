#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>

char tabc[] = {'a', 'b', 'c'};
int n0 = 0, n1 = 1, n2 = 2;

pthread_t tabthread[3];

void*
start(void* ptn)
{
	int i = *(int*)ptn;
	int next = (i + 1) % 3;
	int sig;

	sigset_t set;

	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);

    pthread_sigmask(SIG_BLOCK, &set, NULL);

	while(1)
	{
		#ifdef DEBUG
		printf("Thread #%d waiting for SIGUSR1\n", i);
		#endif

		// Wait for a signal
		sigwait(&set, &sig);

		if(sig == SIGUSR1) {
			#ifdef DEBUG
			printf("Thread #%d received SIGUSR1\n", i);
			#endif

			// Write char
			write(1, &tabc[i], 1);
			
			// Wake up next thread
			pthread_kill(tabthread[next], SIGUSR1);
		}
	}
}

int
main(int argc, char** argv)
{
	int ret;

	ret = pthread_create(&tabthread[0], NULL, start, &n0);
	ret += pthread_create(&tabthread[1], NULL, start, &n1);
	ret += pthread_create(&tabthread[2], NULL, start, &n2);

	if(ret < 0)
	{
		perror("Problème de création threads");
		exit(1);
	}

	#ifdef DEBUG
	printf("Sending SIGUSR1 to thread #0\n");
	#endif

	pthread_kill(tabthread[0], SIGUSR1);

	usleep(10000);
	sleep(1);

	return 0;
}