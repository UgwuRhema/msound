#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"

int
main(int argc, char *argv[])
{
	char *filename = (char *)malloc(sizeof(char) * 128);
	/* if the user didn't pass a name */
	if (argc < 2)
	{
		strcpy(filename, "music");
	} else if (strcmp(argv[1], "-o") == 0 && argv[2] == NULL){
		fprintf(stderr, "Enter a valid music filename\n");
		return -1;
	}
	free(filename);
	return 0;
}
