eblearn-matlab
==============

eblearn matlab wrapper using libmatio (now included in eblearn trunk as matlab.h)

Dependencies
------------
The wrapper uses libmatio-dev 

URL: http://sourceforge.net/projects/matio/ 

Dont install libmatio from ubuntu repos (apt-get). They are out of date and you will get compile errors.
Download libmatio 1.5 from the matio website.

If not, you can get the package and build it from the website.

Usage
-----
Recompile eblearn with matio enabled
---
Let eblearn know that you installed libmatio by opening 

<code>eblearn/tools/scripts/FindCustom.cmake</code>

and add the line

<code>
SET(MATIO_FOUND TRUE)                                                                                                                                                                                                                        
</code>

If libmatio is at a non-standard path (for example /home/sc3104/libmatio/), add the corresponding lines too

<code>
SET(MATIO_INCLUDE_DIR "/home/sc3104/libmatio/include/")                                                                                                                                                                                         
SET(MATIO_LIBRARIES_DIR "/home/sc3104/libmatio/lib/") 
</code>

Then recompile and install eblearn.

Using the wrapper in your code
---
In your program, add the line

<code> #define \_\_MATLAB\_\_ </code>

before including eblearn headers

Link your program with libmatio (compiler flag -lmatio)

Check main.cpp for sample usage and CMakelists.txt for sample linking
