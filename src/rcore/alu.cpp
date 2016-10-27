/*****************************************************************************
  alu.cpp

  Original Author: Zhang Jixin, CNASIC, 2010-12-9
 *****************************************************************************/

#include "alu.h"
#include "../parameter/parameter_arch.h"

using namespace RcoreParameter;

// interface method
void Alu::configure(AluOpConfig op_config)
{
  m_op_config_ = op_config;

  switch(op_config)
  {
  case OPNULL  :  op_func_ptr_ = &Alu::op_null; break;
  case BYPASS0  :  op_func_ptr_ = &Alu::op_pass0; break;
  case ADD      :  op_func_ptr_ = &Alu::op_add;  break;
  case SUB      :  op_func_ptr_ = &Alu::op_sub;  break;
  case MUL      :  op_func_ptr_ = &Alu::op_mul;  break;
  case NOT0     :  op_func_ptr_ = &Alu::op_not0; break;
  case AND      :  op_func_ptr_ = &Alu::op_and;  break;
  case NAND     :  op_func_ptr_ = &Alu::op_nand; break;
  case OR       :  op_func_ptr_ = &Alu::op_or;   break;
  case NOR      :  op_func_ptr_ = &Alu::op_nor;  break;
  case XOR      :  op_func_ptr_ = &Alu::op_xor;  break;
  case XNOR     :  op_func_ptr_ = &Alu::op_xnor; break;
  case LSL      :  op_func_ptr_ = &Alu::op_lsl; break;
  case LSR      :  op_func_ptr_ = &Alu::op_lsr; break;
  case ASR      :  op_func_ptr_ = &Alu::op_asr; break;
  case ROL      :  op_func_ptr_ = &Alu::op_rol; break;
  case ROR      :  op_func_ptr_ = &Alu::op_ror; break;
  case ASUB     :  op_func_ptr_ = &Alu::op_asub; break;
  case LT       :  op_func_ptr_ = &Alu::op_lt; break;
  }
}

void Alu::compute(RcaData data_in[], RcaData *data_out)
{
	for(Uint32 i = 0; i<NUM_ALU_INPUT; i++){
	  m_data_in_[i] = data_in[i];
	}
  (this->*op_func_ptr_)();
	for(Uint32 i = 0; i<NUM_ALU_OUTPUT; i++){
  	data_out[i] = m_data_out_[i];
	}
}

// private method
// operations
void Alu::op_null()
{
}

void Alu::op_pass0()
{
  m_data_out_[0] = m_data_in_[0];
}

void Alu::op_add()
{
  m_data_out_[0] = m_data_in_[0] + m_data_in_[1];
}

void Alu::op_sub()
{
  m_data_out_[0] = m_data_in_[0] - m_data_in_[1];
}

void Alu::op_mul()
{
  m_data_out_[0] = m_data_in_[0] * m_data_in_[1];
}

void Alu::op_not0()
{
  m_data_out_[0] = ~m_data_in_[0];
}

void Alu::op_and()
{
  m_data_out_[0] = m_data_in_[0] & m_data_in_[1];
}

void Alu::op_nand()
{
  m_data_out_[0] = ~( m_data_in_[0] & m_data_in_[1] );
}

void Alu::op_or()
{
  m_data_out_[0] = m_data_in_[0] | m_data_in_[1];
}

void Alu::op_nor()
{
  m_data_out_[0] = ~( m_data_in_[0] | m_data_in_[1] );
}

void Alu::op_xor()
{
  m_data_out_[0] = m_data_in_[0] ^ m_data_in_[1];
}

void Alu::op_xnor()
{
  m_data_out_[0] = ~( m_data_in_[0] ^ m_data_in_[1] );
}

void Alu::op_lsl()
{
  m_data_out_[0] = m_data_in_[0] << m_data_in_[1];
}

void Alu::op_lsr()
{
  sc_int<WIDTH_RCA_DATA> temp = m_data_in_[0];
  m_data_out_[0] = temp >> m_data_in_[1];
}

void Alu::op_asr()
{
  m_data_out_[0] = m_data_in_[0] >> m_data_in_[1];
}

void Alu::op_rol()
{
}

void Alu::op_ror()
{
}

void Alu::op_asub()
{
  if (m_data_in_[0]>m_data_in_[1])
    m_data_out_[0] = m_data_in_[0] - m_data_in_[1];
  else
    m_data_out_[0] = m_data_in_[1] - m_data_in_[0];
}

void Alu::op_lt()
{
  m_data_out_[0] = (m_data_in_[0] < m_data_in_[1]);
}
