/*****************************************************************************
  config_alu.h

  Original Author: Zhang Jixin, CNASIC, 2010-12-9
 *****************************************************************************/

#ifndef ALU_CONFIG_H_
#define ALU_CONFIG_H_


#include "../tools/system_def.h"
#include "../parameter/parameter_arch.h"
#include <map>
#include <string>
#include <iostream>

#define Map std::map

// ----------------------------------------------------------------------------
//  CONFIG of module 'Alu'
// ----------------------------------------------------------------------------

enum AluOpConfig
{
  OPNULL,
  BYPASS0,
  ADD,
  SUB,
  MUL,
  NOT0,
  AND,
  NAND,
  OR,
  NOR,
  XOR,
  XNOR,
  LSL,
  LSR,
  ASR,
  ROL,
  ROR,

  ASUB,
  LT,

  OP_DEFAULT=OPNULL
};

#endif
