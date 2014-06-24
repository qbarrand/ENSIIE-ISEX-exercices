#include <fcntl.h>
#include <stdio.h>

int redirect(
	char* newStdin, 
	char* newStdout, 
	int* oldStdin, 
	int* oldStdout)
{
	// On duplique stdin
	*oldStdin = dup(0);

	// Fermeture stdin
	close(0);

	// Redirection stdin
	if(open(newStdin, O_RDONLY))
	{
		fprintf(stderr, "Impossible de rediriger stdin\n");
		return 1;
	}

	// On duplique stdout
	*oldStdout = dup(1);

	// Fermeture stdout
	close(1);

	// Redirection stdout
	if(open(newStdout, O_WRONLY) != 1)
	{
		fprintf(stderr, "Impossible de rediriger stdout\n");
		return 1;
	}

	return 0;
}

int restore(int resStdin, int resStdout)
{
	// Restauration stdin
	close(0);

	if(dup(resStdin))
	{
		fprintf(stderr, "Impossible de restaurer stdin\n");
		return 1;
	}

	close(resStdin);

	// Restauration stdout
	close(1);

	if(dup(resStdout) != 1)
	{
		fprintf(stderr, "Impossible de restaurer stdout\n");
		return 1;
	}
	
	close(resStdout);

	return 0;
}