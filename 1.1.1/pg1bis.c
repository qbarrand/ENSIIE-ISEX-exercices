#include <stdio.h>

#define BUFFER_SIZE 100

int main(int argc, char** argv)
{
	// +1 pour '\0'
	char buffer[BUFFER_SIZE + 1];
	int readChar;

	readChar = fread(buffer, 1, BUFFER_SIZE, stdin);

	if(readChar == -1)
	{
		printf("Aucun caractère lu.\n");
		return 1;
	}

	printf("%d caractères lus\n", readChar);
	fwrite(buffer, 1, readChar, stdout);

	return 0;
}