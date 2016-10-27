/**********************************************************************************
-----------------------------------------------------------------------------------
    @file:system_def.h
    @author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @version 1.0, 2010-01-21, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file contains several type definitions.
-----------------------------------------------------------------------------------
**********************************************************************************/


#ifndef SYSTEMC_DEF_H_
#define SYSTEMC_DEF_H_


#include <systemc.h>
#include <vector>

#define String std::string
#define Vector std::vector
#define VectorInt Vector<Uint32>::size_type

typedef unsigned long long 	Uint64;
typedef long long 			Sint64;
typedef unsigned int 	Uint32;
typedef int 				Sint32;
typedef unsigned short		Uint16;
typedef short				Sint16;
typedef unsigned char 		Uint8;
typedef char 				Sint8;

String nameGen1(const char * initial, Uint32 subscript, Uint32 width);
String nameGen2(const char * initial, Uint32 subscript_1, Uint32 subscript_2, Uint32 width);
String nameGen3(const char * initial, Uint32 subscript, Uint32 width);

#endif
