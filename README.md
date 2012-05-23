eblearn-matlab
==============

eblearn matlab wrapper using libmatio (now included in eblearn trunk as matlab.h)

Dependencies
------------
libmatio-dev 
URL: http://sourceforge.net/projects/matio/ 
Ubuntu: sudo apt-get install libmatio-dev

Usage
-----
> add the line 
#define __MATLAB__ 
before including eblearn headers

> Link your program with libmatio (compiler flag -lmatio)

Check main.cpp for sample usage and CMakelists.txt for sample linking