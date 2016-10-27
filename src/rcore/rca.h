/**********************************************************************************
-----------------------------------------------------------------------------------
    @File:    rca.h
    @Author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @Version: 1.0, 
    @Time:    2010-01-21, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file mainly implements the reconfigurable cell class definition.
-----------------------------------------------------------------------------------
**********************************************************************************/
#ifndef RCA_H_
#define RCA_H_

#include <systemc.h>
#include "../config/config_rcore.h"
#include "../config/config_rca.h"
#include "../tools/system_def.h"
#include "../parameter/parameter_arch.h"
#include "rc.h"
#include "mux.h"
#include "../regfile/regs_d.h"
#include "../regfile/regs_sg.h"
#include "jumpmodule.h"

using namespace RcoreParameter;


// ----------------------------------------------------------------------------
//  SC_MODULE : Rca
// ----------------------------------------------------------------------------

// TODO: 以下不是参数
////////// just some #define, move away from here?
#define ROW_UP(row)    ((Uint32)row-1)%NUM_RC_ROW
#define ROW_DOWN(row)    ((Uint32)row+1)%NUM_RC_ROW
#define COL_LEFT(col)    ((Uint32)col-1)%NUM_RC_COL
#define COL_RIGHT(col)    ((Uint32)col+1)%NUM_RC_COL
//////////


class Rca
  : public sc_module
{
public:
	/* system clock */
	sc_in_clk clk_in_;

  // port
  sc_in<RcaData> data_in_[NUM_RCA_INPORT];
  sc_out<RcaData> data_out_[NUM_RCA_OUTPORT];
  //sc_port<vgregs_if<DATA_WIDTH_SGRF> > port_link_sgrf_[NUM_READPORT_SGREGS];
  
	/* Register File in RCA */
	Dregs<DATA_WIDTH_DRF> *dregs_[NUM_DREGS];
	SGRegs<DATA_WIDTH_SGRF> *sgregs_[NUM_SGREGS];

	JumpModule *jump_modular_data_cfg;

  // interface method
  void RouteConfig(RouteSegmentCfg route_context);
	
	void DataConfig(DataSegmentCfg data_context);
	
	void DataGroupConfig(Vector<DataSegmentCfg> data_context);
	
	/* control interface for read/write RF */
  //void startRCAReadVGRF(void);
  //void startRCAWriteVGRF(void);
  
	//void startRcReadRF(void);
	//void startRcWriteRF(void);

	bool isAllRcWriteRfDone(void);
	
	bool isAllRcReadRfDone(void);

	bool isAllRcComputeDone(void);
	
	void clearFlag(void);

private:
  // module instance
  Mux<NUM_OUTPUT_MUX_INPORT>* output_mux[NUM_RCA_OUTPORT];
	Rc<NUM_LINK_RC, NUM_PORT_TO_DRF, NUM_PORT_TO_SGRF>* rc_[NUM_RC_ROW][NUM_RC_COL];
	
  // signal
  sc_signal<RcaData> rc_data_out_to_rc[NUM_RC_ROW][NUM_RC_COL][NUM_ALU_OUTPUT];
	/* buffer will trigger thread even if data value is not changed. */
	sc_buffer<RcaData> rc_data_out_to_global[NUM_RC_ROW][NUM_RC_COL][NUM_ALU_OUTPUT];
	
public:
  // constructor
  Rca(sc_module_name name)
    : sc_module(name)
    , name_(String(name))
  {
		/* initialization for DRF */
		for(Uint32 i=0; i<NUM_DREGS; i++)
		{
			String drf_name = nameGen1("DRF", i, 1);
			dregs_[i] = new Dregs<DATA_WIDTH_DRF>(drf_name.c_str()
																			    , SIZE_DREGS
																				  , NUM_READPORT_DREGS																				 
																				  , NUM_WRITEPORT_DREGS); 
		}
		/* initialization for SGRF */
		for(Uint32 i=0; i<NUM_SGREGS; i++) {
			String sgrf_name = nameGen1("SGRF", i, 1);
			sgregs_[i] = new SGRegs<DATA_WIDTH_SGRF>(sgrf_name.c_str()
															    					 , SIZE_SGREGS
																   					 , NUM_READPORT_SGREGS
																  					 , NUM_WRITEPORT_SGREGS); 
		}
	  /* port binding */
    for (Uint32 i=0; i<NUM_RC_ROW; i++)
      for (Uint32 j=0; j<NUM_RC_COL; j++) {
        String rc_name = nameGen2("RC", i, j, 2);
			  rc_[i][j] = new Rc<NUM_LINK_RC, NUM_PORT_TO_DRF, NUM_PORT_TO_SGRF>(rc_name.c_str(),i,j);
				rc_[i][j]->clk_in_(clk_in_);

				for(Uint32 k=0; k<NUM_PORT_TO_DRF; k++) {					
					rc_[i][j]->port_link_drf_[k](*dregs_[k]);
				}
				for(Uint32 k=0; k<NUM_PORT_TO_SGRF; k++) {					
					rc_[i][j]->port_link_sgrf_[k](*sgregs_[k]);
				}
				
				for(Uint32 k=0; k<NUM_ALU_OUTPUT; k++) {	
        	rc_[i][j]->data_output_to_rc_[k](rc_data_out_to_rc[i][j][k]);
				}
				for(Uint32 k=0; k<NUM_ALU_OUTPUT; k++) {	
        	rc_[i][j]->data_output_to_global_[k](rc_data_out_to_global[i][j][k]);
				}
				
      }
		
    for (Uint32 i=0; i<NUM_RCA_OUTPORT; i++)
    {
      String mux_name = nameGen1("Output_Mux", i, 1);
      output_mux[i] = new Mux<NUM_OUTPUT_MUX_INPORT>(mux_name.c_str());
      output_mux[i]->data_out_(data_out_[i]);
    }

    /* interconnection between RC, it can be changed with variation of topology */
    for (Uint32 i=0; i<NUM_RC_ROW; i++)
      for (Uint32 j=0; j<NUM_RC_COL; j++)
      {
        for (Uint32 k=0; k<NUM_LOCAL; k++)
					for (Uint32 m=0; m<NUM_ALU_OUTPUT; m++)
          	rc_[i][j]->data_in_from_rc_[LOCAL(k)*NUM_ALU_OUTPUT+m]( rc_data_out_to_rc[ ROW_UP(i) ][ k ][m] );
				
        for (Uint32 k=0; k<NUM_RCA_INPORT; k++)
          rc_[i][j]->data_in_global_[ GLOBAL(k)]( data_in_ [k] );
      }

    for (Uint32 k=0; k<NUM_RCA_OUTPORT; k++)
      for (Uint32 i=0; i<NUM_RC_ROW; i++)
        for (Uint32 j=0; j<NUM_RC_COL; j++)
					for (Uint32 m=0; m<NUM_ALU_OUTPUT; m++)
          	output_mux[k]->data_in_[RC_OUTPUT(i,j,m)]( rc_data_out_to_global[i][j][m] );

		jump_modular_data_cfg = new JumpModule("JumpModuleForDataCfg",dregs_,sgregs_);
		jump_modular_data_cfg->clk_in_(clk_in_);
		for(Uint32 i=0; i<NUM_RCA_INPORT; i++)
			jump_modular_data_cfg->data_in_global[i](data_in_[i]);
  }

  // destructor
  ~Rca()
  {
    for (Uint32 i=0; i<NUM_RC_ROW; i++)
      for (Uint32 j=0; j<NUM_RC_COL; j++){
        delete rc_[i][j];
				rc_[i][j] = NULL;
    }
    for (Uint32 i=0; i<NUM_RCA_OUTPORT; i++){
      delete output_mux[i];
			output_mux[i] = NULL;
    }
		for(Uint32 i=0; i<NUM_DREGS; i++){
			delete dregs_[i]; dregs_[i] = NULL;
		}
		/* initialization for SGRF */
		for(Uint32 i=0; i<NUM_SGREGS; i++){
			delete sgregs_[i]; sgregs_[i] = NULL;
		}
		if(jump_modular_data_cfg){
    	delete jump_modular_data_cfg; 
			jump_modular_data_cfg = NULL;
		}
  }

private:
  String name_;
	Vector<RcConfigPacket> m_rca_cfg_;   // Unused, may be removed later
};


#endif
