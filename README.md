# Capstone Project Udacity CPP Nanodegree Program

This is a SDL2 + OpenGL Based Game Project, written in C++, MIT licensed.


# Project structure

```
.vscode/        // Visual studio code files
build/          // Build files, not versioned
src/            // Sources files
.gitignore      // Files we don't want to version
CMakeLists.txt  // Root CMake file, manage dependencies
MakeFile        // Root Make File, build process
LICENCE         // Your rights
Readme.md       // This file ;)
```

# Librairies

## Linux: Get SDL2

This tutorial is for Debian-distributions - I use LUbuntu and Linux-Mint. You can easily adapt it to other distros. You are a Linux user, after all.

```
sudo apt install libsdl2-dev libsdl2-2.0-0 -y;

sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y;

sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y;
```

It is a posibility that your distribution does not embed the last SDL2 version. If you want the last versions, get the last tar.gz sources file from:
- SDL2: https://www.libsdl.org/download-2.0.php
- SDL2 mixer: https://www.libsdl.org/projects/SDL_mixer/
- SDL2 ttf: https://www.libsdl.org/projects/SDL_ttf/

Then decompress them, open a terminal, and go in each folder, where you will execute:

```
./configure
make 
sudo make install
```

You will need two additional librairies to run this template. GLEW, which eases the use of OpenGL, and GLM, which prevents you from writing math calculus.

Install GLEW and GLM:

```
sudo apt update
sudo apt install libglew-dev libglm-dev -y;

```
# Compile tools

You need a way to compile C++. For Windows, if you want to use the handmade classic method, use `g++` with MingW, or use any compiler if you want to use CMake.

## Linux : install any compiler

`g++` or `clang` will do.


# Build and Launch

Build you game with Ctrl + Shift + B for the classic compile mode, or with F7 for the CMake mode.

Launch with F5.
