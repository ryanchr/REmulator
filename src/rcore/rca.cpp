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
#include "rca.h"
#include "../config/config_mux.h"
#include "../parameter/parameter_arch.h"
#include "../tools/system_def.h"

using namespace RcoreParameter;

// interface method
void Rca::RouteConfig(RouteSegmentCfg route_context)
{
	Uint32 data_source[NUM_ALU_INPUT],data_des[NUM_ALU_OUTPUT],op;

	#if DEBUG_RCA_ROUTE_CFG
		cout<<"<<<<< Time: "<<sc_time_stamp()<<", "<<"RCA Route Config"<<endl;
	#endif
	
	/* Route Config of All RCs*/
  for (Uint32 i=0; i<NUM_RC_ROW; i++){
		assert(route_context.data_source_[i].size() == NUM_RC_ROW*NUM_ALU_INPUT);
		assert(route_context.data_des_[i].size() == NUM_RC_ROW*NUM_ALU_OUTPUT);
		assert(route_context.op_rc_[i].size() == NUM_RC_ROW);

    for (Uint32 j=0; j<NUM_RC_COL; j++){
			for (Uint32 k=0; k<NUM_ALU_INPUT; k++) 
				data_source[k] = route_context.data_source_[i][NUM_ALU_INPUT*j+k];
			for (Uint32 n=0; n<NUM_ALU_OUTPUT; n++) 
				data_des[n] = route_context.data_des_[i][NUM_ALU_OUTPUT*j+n];
			op = route_context.op_rc_[i][j];
			/* This Function need one clock time */
     	rc_[i][j]->rcRouteConfig(data_source,data_des,op);
			#if DEBUG_RCA_ROUTE_CFG
				cout<<"<<<<< Time: "<<sc_time_stamp()<<", ";
				cout<<rc_[i][j]->returnName()<<": Route Config Event"<<endl;
			#endif
  	}
  }
	/* Route Config of Jump Module 2 */
	//Note: NUM_RC_ROW may be changed with Config File definition
	Vector<Uint32> module_src = route_context.data_source_[NUM_RC_ROW];
	Vector<Uint32> module_op = route_context.op_rc_[NUM_RC_ROW];
	Vector<Uint32> module_des = route_context.data_des_[NUM_RC_ROW];
	jump_modular_data_cfg->ModuleRouteCfg(module_src, module_op,module_des);

	#if DEBUG_RCA_ROUTE_CFG
		cout<<"<<<<< Time "<<sc_time_stamp()<<": ";
		cout<<" "<<jump_modular_data_cfg->returnName()<<": Route Config Event"<<endl;
	#endif

}

void Rca::DataConfig(DataSegmentCfg data_context)
{
	Uint32 addr_in[NUM_ALU_INPUT],addr_out[NUM_ALU_OUTPUT];
	Uint32 index_mux = 0;

	/* initial all outputMux config */
	for(Uint32 i=0; i<NUM_RCA_OUTPORT; i++){
			output_mux[i]->configure(MUX_DEFAULT);
	}

  for (Uint32 i=0; i<NUM_RC_ROW; i++){
		assert(data_context.addr_data_in[i].size() == NUM_RC_ROW*NUM_ALU_INPUT);
		assert(data_context.addr_data_out[i].size() == NUM_RC_ROW*NUM_ALU_OUTPUT);
		
    for (Uint32 j=0; j<NUM_RC_COL; j++){
			for (Uint32 k=0; k<NUM_ALU_INPUT; k++) 
				addr_in[k] = data_context.addr_data_in[i][NUM_ALU_INPUT*j+k];
			for (Uint32 n=0; n<NUM_ALU_OUTPUT; n++) {
				addr_out[n] = data_context.addr_data_out[i][NUM_ALU_OUTPUT*j+n];
				/* This code is not what I want, while used temporarily */
				//TODO: This code is wrong
				/* if output mode: direct addressing, output port:global */
		    if( (((addr_out[n]>>(WIDTH_RCA_ADDR-3))&0x3) == 0x0)
				  && (((addr_out[n]>>(WIDTH_RCA_ADDR-5))&0x3) == 0x3)){
				assert(((addr_out[n])&0x7FF) < NUM_RCA_OUTPORT);
				output_mux[addr_out[n]&0x7FF]->configure(i*NUM_RC_ROW + j*NUM_ALU_OUTPUT+n);
		    }
			}	
    	rc_[i][j]->rcDataConfig(addr_in,addr_out);
  	}
  }
  #if DEBUG_RCA_DATA_CFG
	cout<<"<<<<< Time: "<<sc_time_stamp()<<","
	    <<" "<<name_<<": Data Config Event"<<endl;
	#endif
}

void Rca::DataGroupConfig(Vector<DataSegmentCfg> data_context)
{
	Uint32 loop_count = (Uint32)data_context.size();
	Uint32 (*rc_addr_in) [NUM_RC_ROW][NUM_RC_COL][NUM_ALU_INPUT];
	Uint32 (*rc_addr_out) [NUM_RC_ROW][NUM_RC_COL][NUM_ALU_OUTPUT];
	rc_addr_in = new Uint32 [loop_count][NUM_RC_ROW][NUM_RC_COL][NUM_ALU_INPUT];
	rc_addr_out = new Uint32 [loop_count][NUM_RC_ROW][NUM_RC_COL][NUM_ALU_OUTPUT];

	/* extract address information */
	for(Uint32 m = 0; m<loop_count; m++ ){
	  for (Uint32 i=0; i<NUM_RC_ROW; i++){
			assert(data_context[m].addr_data_in[i].size() == NUM_RC_ROW*NUM_ALU_INPUT);
			assert(data_context[m].addr_data_out[i].size() == NUM_RC_ROW*NUM_ALU_OUTPUT);
			
	    for (Uint32 j=0; j<NUM_RC_COL; j++){
				for (Uint32 k=0; k<NUM_ALU_INPUT; k++) 
					rc_addr_in[m][i][j][k] = data_context[m].addr_data_in[i][NUM_ALU_INPUT*j+k];
				
				for (Uint32 n=0; n<NUM_ALU_OUTPUT; n++) {
					rc_addr_out[m][i][j][n] = data_context[m].addr_data_out[i][NUM_ALU_OUTPUT*j+n];
					/* This code is not what I want, while used temporarily */
			    if( rc_addr_out[m][i][j][n]>>(WIDTH_RCA_ADDR-1) == 1 ){
						assert(rc_addr_out[m][i][j][n]&&0x7F < NUM_RCA_OUTPORT);
						output_mux[rc_addr_out[m][i][j][n]&&0x7F]->configure(i*NUM_RC_ROW
																											 					+j*NUM_ALU_OUTPUT+n);
			    }
				}	
	  	}
	  }
	}

	/* pipeline scheduling */
	for (Uint32 i=0; i<NUM_RC_ROW; i++)
		for (Uint32 j=0; j<NUM_RC_COL; j++)
			rc_[i][j]->rcDataConfig(rc_addr_in[0][i][j],rc_addr_out[0][i][j]);
	/* record loop count which rc computing corresponding to */
	Uint32 idx_data_cfg_run[NUM_RC_ROW][NUM_RC_COL];
	for (Uint32 i=0; i<NUM_RC_ROW; i++)
		for (Uint32 j=0; j<NUM_RC_COL; j++)
			idx_data_cfg_run[i][j] = 0;

	/* A circulation of configuration for all RCs, including communication with RCs  */
	Uint32 i_row = 0,i_col = 0; 
	bool flag_cfg_done = false;
	while(!flag_cfg_done){
		/* hold on checking RCs that have accomplished execution */
		while(!rc_[i_row][i_col]->isRcExecuteDone()[0]){
			if(i_row<NUM_RC_ROW)  
				if (i_col<NUM_RC_COL) 
					(i_col++) ;
				else {
					i_col = 0; 
					i_row++;
				}
			else {
				i_row = 0; 
			}
		}
		/* Once execution done, send new configuration and update index of running loop */
		Uint32 i_loop = ++idx_data_cfg_run[i_row][i_col];
		rc_[i_row][i_col]->rcDataConfig(rc_addr_in[i_loop][i_row][i_col]
																	,rc_addr_out[i_loop][i_row][i_col]);

		/* check whether all configuration have been sent out. */
		flag_cfg_done = true;
		for (Uint32 i=0; i<NUM_RC_ROW; i++)
			for (Uint32 j=0; j<NUM_RC_COL; j++){
				bool flag_no_cfg = (idx_data_cfg_run[i][j] == loop_count); 
				flag_cfg_done &= flag_no_cfg;
			}
	}

	delete [] rc_addr_in;
	delete [] rc_addr_out;
}

/*
void Rca::startRcReadRF(void)
{
	 for (Uint32 i=0; i<NUM_RC_ROW; i++)
    for (Uint32 j=0; j<NUM_RC_COL; j++)
			rc[i][j]->start_read_event_.notify(SC_ZERO_TIME);
}

void Rca::startRcWriteRF(void)
{
	 for (Uint32 i=0; i<NUM_RC_ROW; i++)
    for (Uint32 j=0; j<NUM_RC_COL; j++)
			rc[i][j]->start_write_event_.notify(SC_ZERO_TIME);
}
*/

bool Rca::isAllRcWriteRfDone(void)
{
	bool write_done = 1;
	for (Uint32 i=0; i<NUM_RC_ROW; i++)
    	for (Uint32 j=0; j<NUM_RC_COL; j++)
			if( rc_[i][j]->needWriteRf() )
				write_done &= rc_[i][j]->isWriteRfDone();

	return write_done;
}

bool Rca::isAllRcReadRfDone(void)
{
	bool read_done = 1;
	for (Uint32 i=0; i<NUM_RC_ROW; i++)
    	for (Uint32 j=0; j<NUM_RC_COL; j++)
				if( rc_[i][j]->needReadRf() )
				read_done &= rc_[i][j]->isReadRfDone();
				
	return read_done;
}

bool Rca::isAllRcComputeDone(void){
	bool flag_done_ = true;
	for(Uint32 i=0; i<NUM_RC_ROW; i++)
		for(Uint32 j=0; j<NUM_RC_ROW; j++){
			bool flag_rc_state = (rc_[i][j]->isRcExecuteDone()[0]	);
			flag_done_ &= flag_rc_state; 
		}
	return flag_done_;
}

void Rca::clearFlag(void)
{
	for (Uint32 i=0; i<NUM_RC_ROW; i++)
    	for (Uint32 j=0; j<NUM_RC_COL; j++) { 
				 rc_[i][j]->flag_read_rf_done_ = false;
				rc_[i][j]->flag_write_rf_done_ = false;
    }	

}
