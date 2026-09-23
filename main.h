#include <stdint.h>

struct __attribute__((packed)) WavHeader
{
	uint8_t RIFF[4]; /* magic number identifying RIFF format, must be "RIFF" */
	uint32_t ChunkSize; /* size of the entire file minus 8 bytes */
	uint8_t WAVE[4]; /* format identifier, msut be "WAVE" */

	uint8_t fmt[4]; /* sub chunk identifier, must be "fmt" */
	uint32_t Subchunk1Size; /* size of the format sub-chunk */
	uint16_t AudioFormat; /* available: 1, 6, 7, 257, 258, 259 */
	uint16_t NumOfChan; /* number of audio channels, 1 = Mono, 2 = Stereo */
	uint32_t SamplesPerSec; /* Freq in Hz */
	uint32_t bytesPerSec;
	uint16_t blockAlign; /* i give up...i ain't writing thse commecnts no more */
	uint16_t bitsPerSample;

	uint8_t Subchunk2ID[4];
	uint32_t Subchunk2Size;
};

/* the complete header every .wav file must have */

/* ignore this struct */
struct Fool
{
	char data[10];
	int alias;
};

struct WavHeader createWav(uint32_t, uint16_t, uint16_t, uint32_t);
void writeToWav(struct WavHeader *, FILE *, unsigned long, uint16_t *, int);
