# dwm

## Description
This is a personal, experimental build of [dwm](https://dwm.suckless.org).
This build is done using [dwm-flexipatch](https://github.com/bakkeby/dwm-flexipatch).

## Patches
1. [attachaside](https://dwm.suckless.org/patches/attachaside)
2. [vanitygaps](https://dwm.suckless.org/patches/vanitygaps)
3. [swallow](https://dwm.suckless.org/patches/swallow)
4. [centeredmaster layout](https://dwm.suckless.org/patches/centeredmaster)
5. [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags)
6. [restartsig](https://dwm.suckless.org/patches/restartsig)
7. [stacker](https://dwm.suckless.org/patches/stacker)

## Requirements
In order to build dwm you need the Xlib header files.

## Installation

```bash
git clone https://github.com/pleskunov/dwm.git
cd dwm
doas make clean install
```
## Running dwm
Add the following line to your .xinitrc to start dwm using startx:

```bash
exec dwm
```

## Configuration
The configuration of dwm is done by creating a custom config.h and (re)compiling the source code.
