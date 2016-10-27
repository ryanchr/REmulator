/**********************************************************************************
-----------------------------------------------------------------------------------
    @File:    jumpmodule.h
    @Author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @Version: 2.0, 
    @Time:    2011-07-11, 16:43
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file mainly implements the jump module definition.
-----------------------------------------------------------------------------------
**********************************************************************************/
#ifndef JUMPMODULE_H_
#define JUMPMODULE_H_

#include <systemc.h>
#include "../tools/system_def.h"
#include "../parameter/parameter_arch.h"
#include "rc.h"
#include "../regfile/regs_d.h"
#include "../regfile/regs_sg.h"

using namespace RcoreParameter;

class JumpModule
	: public sc_module
{
	public:
		sc_in_clk  clk_in_;
		sc_in<RcaData> data_in_global[NUM_RCA_INPORT];
		sc_buffer<RcaData> data_out_to_global[NUM_ALU_OUTPUT*2];
		
		sc_buffer<RcaData> data_in_from_rc_[NUM_ALU_OUTPUT];
		sc_signal<RcaData> data_output_to_rc_[NUM_ALU_OUTPUT];
		Rc<1, 3, 1> *rc_unit[2];

		Vector<Uint32> ModuleDataCfg(Vector<Uint32> data_in,Vector<Uint32> data_out,Vector<Uint32> module_mode);

		void ModuleRouteCfg(Vector<Uint32> src,Vector<Uint32> op,Vector<Uint32> des);

		void MainAction();

		String returnName(void) const;
			
		JumpModule(sc_module_name name
							 ,Dregs<DATA_WIDTH_DRF> *dregs_[NUM_DREGS]
							 ,SGRegs<DATA_WIDTH_SGRF> *sgregs_[NUM_SGREGS])
			:sc_module(name)
			,name_(name)
		{
			/* port binding */
	    for (Uint32 i=0; i<2; i++) {
        String rc_name = nameGen1("RC", i, 2);
				String unit_name = name_ + "_" + rc_name;
			  rc_unit[i] = new Rc<1, 3, 1>(unit_name.c_str(),5,i);
				rc_unit[i]->clk_in_(clk_in_);

				for(Uint32 k=0; k<3; k++) {					
					rc_unit[i]->port_link_drf_[k](*dregs_[k]);
				}
				for(Uint32 k=0; k<NUM_PORT_TO_SGRF; k++) {					
					rc_unit[i]->port_link_sgrf_[k](*sgregs_[k]);
				}
				for(Uint32 k=0; k<NUM_RCA_INPORT; k++) {	
      		rc_unit[i]->data_in_global_[k](data_in_global[k]);
				}
				for(Uint32 k=0; k<NUM_ALU_OUTPUT; k++) {	
    			rc_unit[i]->data_output_to_global_[k](data_out_to_global[NUM_ALU_OUTPUT*i+k]);
				}
	    }

			for(Uint32 k=0; k<NUM_ALU_OUTPUT*1; k++) {	
      	rc_unit[0]->data_in_from_rc_[k](data_in_from_rc_[k]);
				rc_unit[0]->data_output_to_rc_[k](data_output_to_rc_[k]);				
			}
			for(Uint32 k=0; k<NUM_ALU_OUTPUT*1; k++) {	
				rc_unit[1]->data_output_to_rc_[k](data_in_from_rc_[k]);
				rc_unit[1]->data_in_from_rc_[k](data_output_to_rc_[k]);
			}
	}
	~JumpModule()
	{
		for(Uint32 i=0; i<2; i++){
			if(rc_unit[i]){
				delete rc_unit[i];
				rc_unit[i] = NULL;
			}
		}
	}
	private:
		sc_signal<RcaData> jump_mode;
		sc_signal<RcaData> jump_addr;
		sc_signal<RcaData> flag_on;
		
		sc_signal<RcaData> addr_global_w[2];
		String name_;
};


#endif

