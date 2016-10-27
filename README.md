# SystemC based Simulator of 2D Systolic Array system

This project is meant to create a SystemC Simulator of a 2D systolic array consisting of processing elements. 

**Install**

Set up matlab lib

* required matlab lib files: libeng．lib、libmx．lib、libmat.lib, make sure to include these files in your makefile

* any new cpp file should include engine.h file

Set up flex&bison

* install GNUWIN32 and flex&bison

* compile flex and yacc files:

    flex -o../src/config/config.lex.cpp ../src/config/config.lex

    bison -o../src/config/config.tab.cpp -d ../src/config/config.y

compile commands:

    Flex -oxxx.lex.cpp xxx.l  

    Bison -oxxx.tab.cpp -d  xxx.y  

if not able to add the library files, then add the follow line into the .l file:

    %option noyywrap   %option noyylineno 

**How to run**

1. compile the files

2. run the generated executable file





 
