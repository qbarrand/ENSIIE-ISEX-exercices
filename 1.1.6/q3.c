#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char tabc[] = {'a', 'b', 'c'};
int n0 = 0, n1 = 1, n2 = 2, tour;

pthread_t tabthread[3];

void* start(void* ptn)
{
	int i = *(int*)ptn;

	while(1)
	{
		if(tour == i)
		{
			write(1, &tabc[i], 1);
			tour += 1;
			tour = tour % 3;
		}
	}
}

int main(int argc, char** argv)
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

	usleep(100000);
	sleep(1);

	return 0;
}