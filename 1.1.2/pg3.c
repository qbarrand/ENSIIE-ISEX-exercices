#include <stdio.h>

int main(int argc, char** argv)
{
	redirect();
	lire();
	restore();

	printf("Ceci devrait s'afficher sur l'écran.\n");
}