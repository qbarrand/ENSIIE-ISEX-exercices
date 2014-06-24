#include <stdio.h>
#include <stdlib.h>

extern char charlu[];

// int lire(int nb)
// {
// 	// Traitement
// 	// +1 pour '\0'
// 	char* buffer = malloc(nb * sizeof(char) + 1);
// 	int readChar;

// 	readChar = read(0, buffer, nb);

// 	if(readChar == -1)
// 	{
// 		printf("Aucun caractère lu.\n");
// 		return 1;
// 	}

// 	printf("%d caractères lus\n", readChar);
// 	write(1, buffer, readChar);

// 	free(buffer);
// }

int lireFichier(FILE* fd, int nb, char** read_data)
{
	// Traitement
	// +1 pour '\0'
	char* buffer = malloc(nb * sizeof(char) + 1);
	int readChar;

	// FILE* desc = fopen(path, "r");
	readChar = fread(charlu, 1, nb, fd);
    charlu[readChar]='\0';
	if(readChar == -1)
	{
		printf("Aucun caractère lu.\n");
		return 1;
	}

	*read_data = buffer;
	printf(" myread a lu %d \n",readChar);

	return readChar;
}
