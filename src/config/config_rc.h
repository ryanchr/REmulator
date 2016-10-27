/**********************************************************************************
-----------------------------------------------------------------------------------
    @File:    config_rc.h
    @Author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @Version: 1.0, 
    @Time:    2011-02-17, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file mainly implements struct definition of rc configuration data.
-----------------------------------------------------------------------------------
**********************************************************************************/
#ifndef RC_CONFIG_H_
#define RC_CONFIG_H_

#include "../tools/system_def.h"
#include "../parameter/parameter_arch.h"
#include "config_alu.h"

using namespace RcoreParameter;


// ----------------------------------------------------------------------------
//  CONFIG of module 'Rc'
// ----------------------------------------------------------------------------

#define INROUTE_DEFAULT    0
#define DATA_DEFAULT  0

/* Enum of class definition for configuration */

/* as input cfg will change with different topology, 
here use a template class for input cfg definition */
template<Uint32 num_link_rc> 
class RcInputCfg
{
public:
	Map<String,Uint32> input_cfg_;
	RcInputCfg(){
		Uint32 init_num = 0;
		for (Uint32 i = 0 ; i<num_link_rc*NUM_ALU_OUTPUT; i++){
			String name = nameGen3("FromRc",i,1);
			input_cfg_[name] = init_num++;
		}
		input_cfg_["FromRf"] = init_num++;	
		input_cfg_["FromGlobal"] = init_num++;	
		input_cfg_["NoInput"] = init_num++;
		input_cfg_["Default"] = init_num;
	}
private:
};

enum RcSourceCfg
{
	FromRc,
  FromRf,
  FromGlobal,
	NoInput,
  RcInDefault
};
	
/**/
enum RcDesCfg
{
	ToRc,
  ToRf,
  ToGlobal,
  NoOutput,
  RcOutDefault
};

enum RcDataAddressingMode
{
	DirectAddressing,
	IndirectAddressing,
	ImmAddressing
};


typedef Uint32 SourceCfg;
typedef Uint32 LinkRcCfg;
typedef Uint32 DesCfg;
typedef Uint32 GlobalInAddr;
typedef Uint32 GlobalOutAddr;
typedef Uint32 LinkRfCfg;
typedef Uint32 RfDataInAddr;
typedef Uint32 RfDataOutAddr;

struct OpCfg
{
  AluOpConfig alu_op_config;

  OpCfg()
  {
     alu_op_config = OP_DEFAULT;
  }
};

struct RcDataPacket
{
	/* input data config */
	GlobalInAddr addr_global_in[NUM_ALU_INPUT];
	LinkRfCfg link_one_rf[NUM_ALU_INPUT];
	RfDataInAddr addr_rf_in[NUM_ALU_INPUT];
	
	/* Output data config */	
	GlobalOutAddr addr_global_out[NUM_ALU_OUTPUT];
	RfDataOutAddr addr_rf_out[NUM_ALU_OUTPUT];

	RcDataPacket()
  {
		for (Uint32 i=0; i<NUM_ALU_INPUT; i++){
      addr_global_in[i] = INROUTE_DEFAULT; 
			link_one_rf[i] = INROUTE_DEFAULT;
			addr_rf_in[i] = INROUTE_DEFAULT;
		}
		for (Uint32 i=0; i<NUM_ALU_OUTPUT; i++){
			addr_global_out[i] = INROUTE_DEFAULT;
			addr_rf_out[i] = INROUTE_DEFAULT;
		}
  }
};

struct RcRoutePacket
{
	SourceCfg source_[NUM_ALU_INPUT];				// input from rc , global or rf?
	LinkRcCfg link_one_rc[NUM_ALU_INPUT];	  // input from which rc
	OpCfg op_;
	RcDesCfg des_[NUM_ALU_OUTPUT];

	RcRoutePacket()
  {
		for (Uint32 i=0; i<NUM_ALU_INPUT; i++){
      source_[i] = INROUTE_DEFAULT; 
			link_one_rc[i] = INROUTE_DEFAULT;
		}
		for (Uint32 i=0; i<NUM_ALU_INPUT; i++)
			des_[i] = RcOutDefault;
  }
};

struct RcConfigPacket
{
	RcRoutePacket cfg_route_;
	RcDataPacket cfg_data_;
};


#endif
