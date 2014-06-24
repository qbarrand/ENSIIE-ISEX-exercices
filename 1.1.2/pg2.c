#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	// int op1, op2;

	// Fermeture entrée standard
	if(close(0))
	{
		printf("Impossible de fermer stdin\n");
		return 1;
	}

	// Ouverture entrée standard "test.data"
	if(open("./test.data", O_RDONLY))
	{
		printf("Impossible d'ouvrir test.data en tant que stdin\n");
		return 1;
	}

	// Fermeture sortie standard
	if(close(1))
	{
		printf("Impossible de fermer stdout\n");
		return 1;
	}

	// Ouverture sortie standard "res.data"
	if(open("./res.data", O_WRONLY) != 1)
	{
		printf("Impossible d'ouvrir res.data en tant que stdout\n");
		return 1;
	}

	if(execlp("./pg1", "./pg1", (void *) NULL) == -1)
	{
		perror("Erreur lors de l'exécution de pg1");
		return 1;
	}

	return 0;
}