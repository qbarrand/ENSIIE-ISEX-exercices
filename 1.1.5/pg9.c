#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void
flush_stdin()
{
	char c;
	while((c = getchar()) != '\n' && c != EOF)
	/* discard */ ;
}

int
main(int argc, char** argv)
{
	char selection;

	printf("1/ ls -l\n"
		"2/ ps\n"
		"3/ traduction de la date en français\n"
		"4/ quitter\n"
		"\n");

	do
	{
		printf("quentin@isex:$ ");
		scanf("%c", &selection);

		switch(selection)
		{
			case '1':
				system("/bin/ls -l");
				break;

			case '2':
				system("/bin/ps");
				break;

			case '3':
				system("/bin/date");
				break;

			case '4':
				printf("Bye\n");
				exit(0);
		}
		
		flush_stdin();
	} while(selection != '4');
}
