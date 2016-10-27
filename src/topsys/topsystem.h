/**********************************************************************************
-----------------------------------------------------------------------------------
    @file:topsystem.h
    @author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @version 1.0,2011-01-21
    
    @section LICENSE
    @
    @section DESCRIPTION:
    The TopSystem class represents a top system module.
-----------------------------------------------------------------------------------
**********************************************************************************/
#ifndef _TOPSYSTEM_H
	#define _TOPSYSTEM_H

#include <systemc.h>
#include "../tools/system_def.h"
#include "../rcore/rcore.h"
#include "../config/config_rcore.h"
#include "../regfile/regs_vg.h"
#include "../parser/parser.h"

using TopSysParameter::NUM_RCORE;
using TopSysParameter::NUM_VGRF;
using TopSysParameter::SIZE_VGREGS;
using TopSysParameter::NUM_READPORT_VGREGS;
using TopSysParameter::NUM_WRITEPORT_VGREGS;

class TopSystem:
	public sc_module
{
public:
	sc_in_clk clk_in_;
	ContextParser *init_;
	Rcore *rcore_[NUM_RCORE];
	VGregs<DATA_WIDTH_VGRF> *vgregs_[NUM_VGRF];
	
	SC_HAS_PROCESS(TopSystem);
	TopSystem(sc_module_name name = sc_module_name("TopSys")
								, ContextParser *_init = NULL)
		:sc_module(name)
		,init_(_init)
		,name_(String(name))
	{
    /* initialization for VGRF */
    for(Uint32 i = 0; i < NUM_VGRF; i++) {
      String vgrf_name = nameGen1("VGRF_", i, 1);
		  vgregs_[i] = new VGregs<DATA_WIDTH_VGRF> (vgrf_name.c_str()
									                          	,SIZE_VGREGS
									                          	,NUM_READPORT_VGREGS
									                          	,NUM_WRITEPORT_VGREGS);
      
    }

    /* initialization for RCORE */
		for(Uint32 i = 0; i < NUM_RCORE; i++) { 
      String rcore_name = nameGen1("RCORE_", i, 1);

		  rcore_[i] = new Rcore(rcore_name.c_str());

      rcore_[i]->clk_(clk_in_);
      /* port binding to vgregs */
			
      for(Uint32 j = 0; j< NUM_VGRF; j++)
        rcore_[i]->port_to_vgregs_[j](*vgregs_[j]);
    }

		SC_THREAD(mainAction);
		sensitive<<clk_in_.pos();
		//dont_initialize();
	}

	~TopSystem()
	{
	 for(Uint32 i = 0; i < NUM_RCORE; i++) { 
		if(rcore_[i]) {
			delete rcore_[i];
			rcore_[i] = NULL;
		}
   }
   for(Uint32 i = 0; i < NUM_VGRF; i++) {
		if(vgregs_[i]) {
			delete vgregs_[i];
			vgregs_[i] = NULL;
		}
	 }
  }
	
private:	
	Vector<RcoreContext> rcore_context_;
	String name_;

public:
	void mainAction();
	void readInputContext(void);
	
};

#endif