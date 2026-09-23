#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"

int
main(int argc, char *argv[])
{
	char *filename = (char *)malloc(128 * sizeof(char));
	if (!filename) return -1;

	/* if the user didn't pass a name */
	strcpy(filename, "music");
	/* else */
	if (argc > 1 && strcmp(argv[1], "-o") == 0)
	{
		if (argc < 3 || argv[2] == NULL)
		{
			fprintf(stderr, "Enter a valid music filename\n");
			return -1;
		}

		strncpy(filename, argv[2], 127);
		filename[127] = '\0';
	}

	FILE *wav = fopen(filename, "w");
	if (!wav)
	{
		fprintf(stderr, "Failed to open file. \n");
		return -1;
	}
	fprintf(wav, "Hello World\n");
	fclose(wav);

	free(filename);
	return 0;
}
