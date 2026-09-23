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

	struct WavHeader wav_header = createWav(44100, 1, 16, 0);
	/* the .wav file creation, pretty easy right? */
	FILE *fd = fopen(filename, "wb+");
	if (!fd) return -1;

	/* this should be how it's done right?*/
	fwrite(&wav_header, sizeof(wav_header), 1, fd);

	fclose(fd);
	free((void *)filename);
	return 0;
}

struct
WavHeader createWav(uint32_t sr, uint16_t nc, uint16_t bps, uint32_t db)
{
	/* boilerplate identifiers */
	struct WavHeader header;
	memcpy(header.RIFF, "RIFF", 4);
	memcpy(header.WAVE, "WAVE", 4);
	memcpy(header.fmt, "fmt", 4);
	memcpy(header.Subchunk2ID, "data", 4);
	/*fixed PCM parameters */
	header.Subchunk1Size = 16; /* standard size for PCM as i discovered */
	header.AudioFormat = 1; /* 1 = Mono, uncompressed */
	/* non-boilerplate..get it? */
	header.NumOfChan = nc;
	header.SamplesPerSec = sr;
	header.bitsPerSample = bps;
	header.blockAlign = nc * (bps / 8);
	header.bytesPerSec = sr * header.blockAlign;
	/* payload sizes */
	header.Subchunk2Size = db;
	header.ChunkSize = 36 + db;

	return header;
}
