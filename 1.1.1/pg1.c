#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 100

int main(int argc, char** argv)
{
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

	return 0;
}