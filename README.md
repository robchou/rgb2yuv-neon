# rgb2yuv NEON benchmark

## Overview
This is a demo to show the NEON's effect

## Compile
```sh
# compile normal code
arm-linux-gnueabihf-gcc rgb2yuv_neon.c -o rgb2yuv -O3
## compile NEON code
arm-linux-gnueabihf-gcc rgb2yuv_neon.c -o rgb2yuv_neon -mfpu=neon -O3
```

## Usage
```sh
# normal
./rgb2yuv ./res/720p  outfile.yuv 1280 720 #outfile is yuv420p
# neon
./rgb2yuv_neon ./res/720p  outfile.yuv 1280 720 #outfile is yuv420p
```
