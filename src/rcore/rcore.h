/**********************************************************************************
-----------------------------------------------------------------------------------
    @File:    rcore.h
    @Author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @Version: 1.0, 
    @Time:    2010-01-21, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file mainly implements the rcore class definition.
-----------------------------------------------------------------------------------
**********************************************************************************/
#ifndef RCORE_H_
#define RCORE_H_

#include <systemc.h>
#include "../config/config_rcore.h"
#include "../tools/system_def.h"
#include "jumpmodule.h"
#include "../parameter/parameter_arch.h"
#include "../config/reconfigure_if.h"
#include "rca.h"
#include "../regfile/regs_d.h"
#include "../regfile/regs_vg.h"
#include "../regfile/regs_sg.h"

using namespace RcoreParameter;
using TopSysParameter::NUM_VGRF;
using TopSysParameter::DATA_WIDTH_VGRF;

#define NUM_MAX_READ_TIME 128
// ----------------------------------------------------------------------------
//  SC_MODULE : Rcore
// ----------------------------------------------------------------------------

class Rcore
  : public sc_module
  //, public ReconfigureIf
{
public:
  // port
  sc_in_clk clk_;
  sc_port<vgregs_if<DATA_WIDTH_VGRF> > port_to_vgregs_[NUM_VGRF];
	
  // sc_interface method
  void runOneContext(RcoreContext rcore_context);
  
  void writeRouteCfg(RouteSegmentCfg route_context);
	
  void writeDataCfg(DataSegmentCfg data_context); 

	void writeDataCfgGroup(Vector<DataSegmentCfg*> data_context);
	
	void writeReadVgrfCfg (Vector<Vector<Uint32> > read_vgrf_cfg);
	
	void writeWriteVgrfCfg (Vector<Vector<Uint32> > write_vgrf_cfg);

	void printSGRF(Uint32 *data);

	sc_event event_write_route_context,event_write_data_context
					,even_read_vgrf_cfg,even_write_vgrf_cfg,route_rca_in
					,event_read_vgrf_done,event_set_state,event_one_data_context_done
					,event_need_read_vgrf,event_revert_data_cfg
					,event_need_write_vgrf
					,event_data_cfg_read_global,event_data_cfg_can_read;
private:
  // module instance
  Rca *rca_;
	JumpModule *jump_modular_r_vgrf, *jump_modular_w_vgrf;
  // signals
  sc_signal<RcaData> rca_data_in_[NUM_RCA_INPORT];
  sc_buffer<RcaData> rca_data_out_[NUM_RCA_OUTPORT];
	
  // for functional model
  bool flag_execution_done_,flag_need_revert_data_cfg;
	
	/* This two parameter is used for check state, may be modified later */
	Uint32 idx_data_cfg_running, idx_next_data_cfg, idx_next_read_vgrf_cfg, idx_next_write_vgrf_cfg; 
	bool flag_pipeline_, flag_module_data_cfg_on, flag_data_cfg_jump, flag_read_vgrf_jump 
		  ,flag_module_r_vgrf_on, flag_write_vgrf_jump ,flag_module_w_vgrf_on; 

public:
  // process
  void routeRCAIn();
	
	void isRCAExecuteDone();
	
  // constructor
  SC_HAS_PROCESS(Rcore);
  Rcore(sc_module_name name)
    : sc_module(name)
    , name_(String(name))
    ,flag_execution_done_(false)
    ,idx_data_cfg_running(0)
    ,idx_next_data_cfg(0)
    ,idx_next_read_vgrf_cfg(0)
    ,flag_pipeline_(false)    
    ,flag_data_cfg_jump(false)    
    ,flag_module_data_cfg_on(false)
    ,flag_module_r_vgrf_on(false)
    ,flag_read_vgrf_jump(false)
    ,flag_write_vgrf_jump(false) 
    ,flag_module_w_vgrf_on(false)
  {
  	// port binding
    rca_ = new Rca("RCA");
  	rca_->clk_in_(clk_);
		/* Initial of Jump Modular for VGRF Context Jump */
		jump_modular_r_vgrf = new JumpModule("JumpModuleReadVGRF",rca_->dregs_,rca_->sgregs_);
		jump_modular_r_vgrf->clk_in_(clk_);
		for(Uint32 i=0; i<NUM_RCA_INPORT; i++)
			jump_modular_r_vgrf->data_in_global[i](rca_data_in_[i]);

		jump_modular_w_vgrf = new JumpModule("JumpModuleWriteVGRF",rca_->dregs_,rca_->sgregs_);
		jump_modular_w_vgrf->clk_in_(clk_);
		for(Uint32 i=0; i<NUM_RCA_INPORT; i++)
			jump_modular_w_vgrf->data_in_global[i](rca_data_in_[i]);

    for (Uint32 i=0; i<NUM_RCA_INPORT; i++)
      rca_->data_in_[i](rca_data_in_[i]);
    for (Uint32 i=0; i<NUM_RCA_OUTPORT; i++)
      rca_->data_out_[i](rca_data_out_[i]);
    // process registration
    SC_THREAD(routeRCAIn);
  	sensitive << clk_.pos();
		
    SC_THREAD(isRCAExecuteDone);
  	sensitive << clk_.pos();

		SC_THREAD(readVGregs);
		sensitive << clk_.pos();
		
		SC_THREAD(writeVGregs);
		sensitive << clk_.pos();

		for(Uint32 i=0; i<NUM_RCA_INPORT; i++){
			rca_data_in_buf_[i] = 0;
		}
		/* Initialize for read/write vgrf context */
		//m_read_vgrf_context_.resize(1);
		//m_write_vgrf_context_.resize(1);
  }

  // destructor
  ~Rcore()
  {
		if(rca_){
    	delete rca_; 
			rca_ = NULL;
		}
		if(jump_modular_r_vgrf){
    	delete jump_modular_r_vgrf; 
			jump_modular_r_vgrf = NULL;
		}
		if(jump_modular_w_vgrf){
    	delete jump_modular_w_vgrf; 
			jump_modular_w_vgrf = NULL;
		}
  }

private:
  String name_;
	Vector<Vector<Uint32> > m_read_vgrf_context_;
	Vector<Vector<Uint32> > m_write_vgrf_context_;

	RcoreContext m_rcore_context_;
	RouteSegmentCfg m_route_context_;
  DataSegmentCfg m_data_context_;
	Vector<DataSegmentCfg> m_data_group_;
  
  RcaData rca_data_in_buf_[NUM_RCA_INPORT];    // for functional model
private:
	void readVGregs();
	void writeVGregs();
};


#endif
