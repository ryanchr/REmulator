/*****************************************************************************
  tools.cpp

  Original Author: Zhang Jixin, CNASIC, 2010-12-9
 *****************************************************************************/

#include <systemc.h>
#include "system_def.h"
#include <stdio.h>
using std::string;

String nameGen1(const char * initial, Uint32 subscript, Uint32 width)
{
  char buffer[10];
  String name;

  name = initial;
  name += "_";
  sprintf(buffer, "%0*d", width, subscript);  // convert integer to cstring with zero padding
  name += buffer;
  return name;
}

String nameGen2(const char * initial, Uint32 subscript_1, Uint32 subscript_2, Uint32 width)
{
  char buffer[10];
  String name;

  name = initial;
  name += "_";
  sprintf(buffer, "%0*d", width, subscript_1);
  name += buffer;
  name += "_";
  sprintf(buffer, "%0*d", width, subscript_2);
  name += buffer;
  return name;
}

String nameGen3(const char * initial, Uint32 subscript, Uint32 width)
{
  char buffer[10];
  String name;

  name = initial;
  sprintf(buffer, "%0*d", width, subscript);  // convert integer to cstring with zero padding
  name += buffer;
  return name;
}