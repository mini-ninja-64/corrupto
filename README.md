# corrupto
Command line file corruptor written in C++

#### Why?:

I made this because I like corrupting files and seeing what happens, this is especially fun in old videogame roms and videos. I decided to make my own after a gif I was making got messed up by imagemagick and I wanted to see if could recreate the effect programmatically.

#### Examples:

###### Images:

bear.jpg

![bear](https://raw.githubusercontent.com/mini-ninja-64/corrupto/experimental/examples/images/bear/bear.jpg)

after applying ```corrupto -i bear.jpg -o bearCorr.jpg -s wobble0 -n 1600 -a 5``` I got:

![bear corrupted](https://raw.githubusercontent.com/mini-ninja-64/corrupto/experimental/examples/images/bear/bearCorr.jpg)



#### How to setup:

Linux: ```g++ corrupto.cpp -o corrupto``` (if it does not compile try using C++11 as standard libray).

OS X: Install brew, install g++, same as linux (may make a brew package for corrupto in the future)

Windows: I guess you use cygwin, but I have not tested it.

#### How to use:
```
corrupto options
```
(if you don't add it to the system path then you will need to call ./corrupto options)

The minimum required options for corruption are:

Input file, Output file, Corruption method, Every nth along, Amount of corruption

To denote an option preface it with the following:

* -i: Input file
* -o: Output file
* -s: Corruption method
* -n: Every nth along
* -a: Amount of corruption

To see the full list of options and corruption settings visit the wiki
