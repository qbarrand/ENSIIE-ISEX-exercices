#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define BYTES_TO_READ 10
char charlu[100];

void pere(FILE* fd)
{
	char* read_strings;
	int nb_read;

	nb_read = lireFichier(fd, BYTES_TO_READ, &read_strings);

	printf("%d père : %d caractères lus - %s\n", getpid(), nb_read, read_strings);

	free(read_strings);
	//fclose(fd);

	exit(0);
}

void fils(FILE* fd)
{
	char* read_strings;
	int nb_read;

	//nb_read = lireFichier(fd, BYTES_TO_READ, &read_strings);
	nb_read = fread(charlu,1,10, fd);

	printf("%d fils : %d caractères lus - %s\n", getpid(), nb_read, charlu);

	free(read_strings);
	//fclose(fd);

	exit(0);
}

int main(int argc, char** argv)
{
	FILE* fd = fopen("test.data", "r");

	int pid;
	switch(pid = fork())
	
	{
		case -1: 
			perror("Echec du fork");
			exit(1);
			break;

		case 0:
			fils(fd);
			break;

		default: 
			pere(fd);
	}
}