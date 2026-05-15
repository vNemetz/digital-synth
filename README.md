# Digital Synth

Simple JUCE-based console synth that plays a short looping melody through your system audio device.

## Prerequisites

Linux tools:

- C++ compiler (GCC or Clang)
- CMake 3.15+
- pkg-config

Development libraries required by the current CMake configuration:

- gtk+-3.0
- webkit2gtk-4.1
- libsoup-3.0
- javascriptcoregtk-4.1
- libcurl

Audio backends used by JUCE on Linux:

- ALSA development files
- PulseAudio development files

Example install command for Debian/Ubuntu:

```bash
sudo apt update
sudo apt install -y \
 build-essential cmake pkg-config \
 libgtk-3-dev libwebkit2gtk-4.1-dev libsoup-3.0-dev \
 libjavascriptcoregtk-4.1-dev libcurl4-openssl-dev \
 libasound2-dev libpulse-dev
```

## Clone

This repository uses JUCE as a git submodule.

```bash
git clone --recurse-submodules git@github.com:vNemetz/digital-synth.git
cd digital-synth
```

If you already cloned without submodules:

```bash
git submodule update --init --recursive
```

Or if you're a man that uses grown men's distro (NixOS):

```bash
git clone git@github.com:vNemetz/digital-synth.git
nix-shell
```

## Build

From the project root:

```bash
cmake -S . -B build
cmake --build build -j
```

## Run

Run the generated executable:

```bash
./build/DigitalSynth_artefacts/DigitalSynth
```

Behavior:

- The app opens the default system output device.
- It starts playing a looping sine-wave melody.
- Press Enter in the terminal to stop.

## Troubleshooting

If CMake fails finding packages, verify pkg-config can resolve them:

```bash
pkg-config --modversion gtk+-3.0 webkit2gtk-4.1 libsoup-3.0 javascriptcoregtk-4.1 libcurl
```

If you changed branches or pulled updates, refresh submodules:

```bash
git submodule sync --recursive
git submodule update --init --recursive
```
