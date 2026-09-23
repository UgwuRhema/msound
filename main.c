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
	strcpy(filename, "music.wav");
	/* else */
	if (argc > 1 && strcmp(argv[1], "-o") == 0)
	{
		if (argc < 3 || argv[2] == NULL)
		{
			fprintf(stderr, "Enter a valid music filename that ends with .wav\n");
			return -1;
		}

		strncpy(filename, argv[2], 127);
		filename[127] = '\0';
	}

	struct WavHeader wav_header;
	/* the .wav file creation, pretty easy right? */
	FILE *fd = fopen(filename, "wb+");
	if (!fd) return -1;

	/* this should be how it's done right?*/
	fwrite(&wav_header, sizeof(wav_header), 1, fd);

	fclose(fd);
	free((void *)filename);
	return 0;
}
