#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 100

static int bakStdin, bakStdout;

int redirect()
{
	// On duplique stdin
	bakStdin = dup(0);

	// Fermeture stdin
	close(0);

	// Redirection stdin
	if(open("test.data", O_RDONLY))
	{
		fprintf(stderr, "Impossible de rediriger stdin\n");
		return 1;
	}

	// On duplique stdout
	bakStdout = dup(1);

	// Fermeture stdout
	close(1);

	// Redirection stdout
	if(open("res.data", O_WRONLY) != 1)
	{
		fprintf(stderr, "Impossible de rediriger stdout\n");
		return 1;
	}

	return 0;
}

int restore()
{
	// Restauration stdin
	close(0);

	if(dup(bakStdin))
	{
		fprintf(stderr, "Impossible de restaurer stdin\n");
		return 1;
	}

	close(bakStdin);

	// Restauration stdout
	close(1);

	if(dup(bakStdout) != 1)
	{
		fprintf(stderr, "Impossible de restaurer stdout\n");
		return 1;
	}
	
	close(bakStdout);

	return 0;
}

int lire()
{
	// Traitement
	// +1 pour '\0'
	char buffer[BUFFER_SIZE + 1];
	int readChar;

	readChar = read(0, buffer, BUFFER_SIZE);

	if(readChar == -1)
	{
		printf("Aucun caractère lu.\n");
		return 1;
	}

	printf("%d caractères lus\n", readChar);
	write(1, buffer, readChar);
}