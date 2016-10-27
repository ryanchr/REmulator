/*****************************************************************************
  alu.h

  Original Author: Zhang Jixin, CNASIC, 2010-12-9
 *****************************************************************************/

#ifndef ALU_H_
#define ALU_H_


#include "../config/config_alu.h"
#include "../tools/system_def.h"
#include "../parameter/parameter_arch.h"

using namespace RcoreParameter;


// ----------------------------------------------------------------------------
//  class : Alu
//  (This is not a sc_module, because 'configure' and 'compute'
//   comunicate using global variable 'op_func_ptr_' but not signals)
// ----------------------------------------------------------------------------


class Alu
{
public:
  Alu()
  {
    m_op_config_ = OP_DEFAULT;
    op_func_ptr_ = &Alu::op_null;
  }
  void configure(AluOpConfig op_config);
  void compute(RcaData data_in[], RcaData * data_out);

private:
  AluOpConfig m_op_config_;
  RcaData m_data_in_[NUM_ALU_INPUT], m_data_out_[NUM_ALU_OUTPUT];

private:
  // operations
  void (Alu::* op_func_ptr_)();      // function pointer to operations

  void op_null();
  void op_pass0();

  void op_add();
  void op_sub();
  void op_mul();

  void op_not0();
  void op_and();
  void op_nand();
  void op_or();
  void op_nor();
  void op_xor();
  void op_xnor();

  void op_lsl();
  void op_lsr();
  void op_asr();
  void op_rol();
  void op_ror();

  void op_asub();
  void op_lt();
};


#endif
