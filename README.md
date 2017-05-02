# Ungroup

A group file extractor written in C for build engine games.

## Usage

`ungroup filename.grp`

## Information

The group file format is commonly used on build engine games, such as Duke Nukem 3D, Shadow Warrior, etc. This program extracts the individual files from the group file, much like unzip does for zip files.

## Compiling

This program compiles out of the box with [Borland C++ Compiler 5.5](https://edn.embarcadero.com/article/20633), any should work with most other C compilers without too much hassle. To compile, install Borland C++ Compiler, ensure it is in your path, and run `make`.

## File Specifications

From [http://advsys.net/ken/build.htm](http://advsys.net/ken/build.htm):

*What's the .GRP file format?*

The ".grp" file format is just a collection of a lot of files stored into 1 big one. I tried to make the format as simple as possible: The first 12 bytes contains my name, "KenSilverman". The next 4 bytes is the number of files that were compacted into the group file. Then for each file, there is a 16 byte structure, where the first 12 bytes are the filename, and the last 4 bytes are the file's size. The rest of the group file is just the raw data packed one after the other in the same order as the list of files.
