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
			free((void *)filename);
			return -1;
		}

		strncpy(filename, argv[2], 127);
		filename[127] = '\0';
	}
	/* defaults */
	int wave_type = 1;
	float freq = 440.0f;
	float duration = 2.0f;

	printf("=====MSOUND======\n");
	printf("Select waveform shape:\n");
	printf("1. Sine Wave\n2. Square Wave\n3. Sawtooth Wave\n4. Triangle Wave\n");
	printf("Choice: ");
	if (scanf("%d", &wave_type) != 1 || wave_type < 1 || wave_type > 4) 
	{
		printf("\tDefault picked = 1\n");
		wave_type = 1;
	}
	printf("Enter Frequency in Hz (eg. 440 for A4 and 261.63 for C4): ");
	if (scanf("%f", &freq) != 1 || freq <= 0) freq = 440.0f;
	printf("Enter Duration in Seconds(float): ");
	if (scanf("%f", &duration) != 1 || duration <= 0) duration = 2.0f;

	uint32_t sample_rate = 44100;
	size_t num_samples = (size_t)sample_rate * duration;
	uint32_t data_bytes = (uint32_t)(num_samples * sizeof(int16_t));

	int16_t *samples = (int16_t *)malloc(data_bytes);
	if (!samples) { free((void *)filename); return -1;}

	/* when writing sounds remember these, db(data_bytes) is number_of_samples multiplied by the sizeof whatever type the samples are */
	/* have a definite duration, for example 2 seconds */
	/* number_of_samples is sample_rate(normally 44100 by def) multiplied by the duration in seconds */
	struct WavHeader wav_header = createWav(sample_rate, 1, 16, data_bytes);
	/* the .wav file creation, pretty easy right? */
	FILE *fd = fopen(filename, "wb+");
	if (!fd) {free((void *)filename);return -1;}

	/* this should be how it's done right?*/
	fwrite(&wav_header, sizeof(wav_header), 1, fd);
	/* let's write the samples, 1 second of absolute silence */
	writeToWav(&wav_header, fd, samples, num_samples);
	fclose(fd);
	free((void *)samples);
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
	memcpy(header.fmt, "fmt ", 4);
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

void
writeToWav(const struct WavHeader *wh, FILE *fd, const int16_t *samples_data, size_t num_samples)
{
	/* this is a default writer that writes 2 seconds of silence into the .wav file*/
	size_t bytes_per_sample = wh->bitsPerSample / 8;
	fwrite(samples_data, bytes_per_sample, num_samples, fd);
}

void generateSamples(int16_t *samples, size_t num_samples, uint32_t sample_rate, float freq, int wave_type)
{
	for (size_t i = 0; i < num_samples; i++)
	{
		double t = (double)i / sample_rate;
		double phase = fmod(freq * t, 1.0); /* Phase progression between 0.0 and 1.0 */

		switch (wave_type)
		{
			case 1: /* Sine Wave */
				samples[i] = (int16_t)(AMPLITUDE * sin(2.0 * M_PI * freq * t));
				break;
			case 2: /* Square Wave */
				samples[i] = (int16_t)(sin(2.0 * M_PI * freq * t) >= 0 ? AMPLITUDE : -AMPLITUDE);
				break;
			case 3: /* Sawtooth Wave */
				samples[i] = (int16_t)(AMPLITUDE * (2.0 * phase - 1.0));
				break;
			case 4: /* Triangle Wave */
				samples[i] = (int16_t)(AMPLITUDE * (2.0 * fabs(2.0 * phase - 1.0) - 1.0));
				break;
			default:
				samples[i] = 0;
				break;
		}
	}
}
