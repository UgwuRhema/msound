# msound

msound is a simple CLI tool that generates playable `.wav` audio files from mathematical waveforms. You pick a wave shape, target frequency, and duration, and it writes out a complete audio file.

It works by manually assembling a standard 44-byte RIFF header and writing raw 16-bit PCM audio samples directly to disk using basic wave math. Built in pure C with zero external dependencies.

## Installation

Compile the binary using `make` and move it to a directory in your `$PATH`:

```bash
make
cp msound ~/.local/bin/

```

## License

[MIT]
