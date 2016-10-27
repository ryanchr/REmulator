# SystemC based Simulator of 2D Systolic Array system
This project is meant to create a SystemC Simulator of a 2D systolic array consisting of processing elements. 

**Install**
1. set up matlab lib
1)required matlab lib files: libeng．lib、libmx．lib、libmat.lib, make sure to include these files in your makefile
2) any new cpp file should include engine.h file

2. set up flex&bison
1) install GNUWIN32 and flex&bison
2) compile flex and yacc files:
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





 
