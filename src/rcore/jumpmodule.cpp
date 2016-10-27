/**********************************************************************************
-----------------------------------------------------------------------------------
    @File:    rca.cpp
    @Author:  Chen Ren, CNASIC, <diyer.renchen@gmail.com>
    @Version: 1.0, 
    @Time:    2010-01-21, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file mainly implements the rca class definition.
-----------------------------------------------------------------------------------
**********************************************************************************/
#include <systemc.h>
#include "jumpmodule.h"
#include "../parameter/parameter_arch.h"
#include "../tools/system_def.h"

using namespace RcoreParameter;

Vector<Uint32> JumpModule::ModuleDataCfg(Vector<Uint32> data_in
															,Vector<Uint32> data_out
															,Vector<Uint32> module_mode)
{
	Uint32 data_in1[2],data_out1[1];
	Uint32 data_in2[2],data_out2[1];

	for(Uint32 i=0; i<2; i++)
		data_in1[i] = data_in[i];
	data_out1[0] = data_out[0];


	rc_unit[0]->rcDataConfig(data_in1, data_out1);
	#if DEBUG_RCORE_JUMP_MODULAR
		cout<<"<<<<< Time: "<<sc_time_stamp()<<","
		    <<" "<<name_
				<<": Rc0 Write Data Cfg"<<endl;
	#endif
	/* Before test flag, wait flag value changed */
	wait(clk_in_->posedge_event());
	while(!(rc_unit[0]->flag_rc_execution_done)) wait();
	
	data_in2[0] = 0;
	data_in2[1] = data_in[2];
	data_out2[0] = data_out[1];

	assert(module_mode.size()==3);
	jump_mode = module_mode[0];	
	jump_addr = module_mode[1];
	flag_on = module_mode[2];
	wait();

	bool flag_need_jump;
	if(flag_on){
		rc_unit[1]->rcDataConfig(data_in2, data_out2);
		data_output_to_rc_[0]= rc_unit[0]->data_output_to_rf_[0];
		while(!(rc_unit[1]->flag_rc_execution_done)) wait();
		/* wait for data_out_to_global value change */
		wait(clk_in_->posedge_event());
		flag_need_jump = data_out_to_global[NUM_ALU_OUTPUT*2-1].read();
	}else{
		flag_need_jump = 0;
	}	

	Vector<Uint32> jump_info;
	jump_info.push_back(flag_need_jump);
	jump_info.push_back(module_mode[0]);
	jump_info.push_back(module_mode[1]);
	
	return jump_info;
}

void JumpModule::ModuleRouteCfg(Vector<Uint32> src
																,Vector<Uint32> op
																,Vector<Uint32> des)

{
	Uint32 src1[2],op1,des1[1];
	Uint32 src2[2],op2,des2[1];

	for(Uint32 i=0; i<2; i++)
		src1[i] = src[i];
	op1 = op[0];
	des1[0] = des[0];
	rc_unit[0]->rcRouteConfig(src1, des1, op1);

	RcSourceCfg cfg = FromRc;
	src2[0] = (Uint32)(cfg);
	src2[1] = src[2];
	op2 = op[1];
	des2[0] = des[1];	
	rc_unit[1]->rcRouteConfig(src2, des2, op2);
}

String JumpModule::returnName(void) const
{
	return name_;
}