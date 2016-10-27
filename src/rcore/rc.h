/**********************************************************************************
-----------------------------------------------------------------------------------
    @File:    rc.h
    @Author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @Version: 1.0, 
    @Time:    2010-01-21, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file mainly implements the reconfigurable cell class definition.
-----------------------------------------------------------------------------------
**********************************************************************************/

#ifndef RC_H_
#define RC_H_

#include <systemc.h>
#include "../config/config_rc.h"
#include "../tools/system_def.h"
#include "../parameter/parameter_arch.h"
#include "alu.h"
#include "../regfile/regs_if.h"
#include <systemc.h>
using namespace RcoreParameter;

// ----------------------------------------------------------------------------
//  SC_MODULE : Rc<num_inport>
// ----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//						Address Definition in Data Segment
//width:    1           2    (NUM_DREGS + NUM_SGREGS+GLOBAL)     THE REST
//			   Head--------Mode-----------Route---------------------Data Address
//-----------------------------------------------------------------------------
/*  */
#define get_width(i) ((i<=4)?2:((i<=8&i>4)?3:((i<=16&i>8)?4:5)))

#define HEAD_BIT  (WIDTH_RCA_ADDR-1)
#define HEAD_MODE_BIT HEAD_BIT - 1
#define HEAD_RF_FLAGS_BIT HEAD_MODE_BIT - 2

#define	GLOBAL_BITS_WIDTH 2
#define	SGRF_BITS_WIDTH 2
#define	DRF_BITS_WIDTH  5  //get_width(NUM_DREGS+NUM_SGREGS)

#define	HEAD_GLOBAL_ADDR_BIT (HEAD_RF_FLAGS_BIT - GLOBAL_BITS_WIDTH)	
#define	HEAD_SGRF_ADDR_BIT (HEAD_RF_FLAGS_BIT - SGRF_BITS_WIDTH)	
#define	HEAD_DRF_ADDR_BIT (HEAD_RF_FLAGS_BIT - DRF_BITS_WIDTH)	


template <Uint32 num_rc_route
				, Uint32 num_port_drf
				, Uint32 num_port_sgrf>
class Rc
  : public sc_module
{
public:
  /* system clock */
	sc_in_clk clk_in_;

	/* interconnections between RC and Global Memory(stores data from vgrf) */
	sc_in<RcaData> data_in_global_[NUM_RCA_INPORT];
	//sc_out<RcaData> data_out_global[NUM_RCA_OUTPORT];

	/* interconnections between RCs */
	sc_in<RcaData> data_in_from_rc_[num_rc_route*NUM_ALU_OUTPUT];

	/* output data wires */  
	sc_out<RcaData> data_output_to_rc_[NUM_ALU_OUTPUT];
  sc_out<RcaData> data_output_to_global_[NUM_ALU_OUTPUT];   //interconnected with global Memory
  RegsData data_output_to_rf_[NUM_ALU_OUTPUT];      //interconnected with drf
  
	/* input/output ports between RC and DRF */
	sc_port<dregs_if<DATA_WIDTH_DRF> > port_link_drf_[num_port_drf];     
	
	/* input/output ports between RC and SGRF */
	sc_port<sgregs_if<DATA_WIDTH_SGRF> > port_link_sgrf_[num_port_sgrf];

  // interface method

	void SourceConfig(Uint32 cfg_source[NUM_ALU_INPUT]);
	
	void LinkRcConfig(Uint32 cfg_source[NUM_ALU_INPUT]);

	void OpConfig(Uint32 cfg_op);
	
	void DesConfig(Uint32 cfg_des[NUM_ALU_OUTPUT]);
	
	void rcRouteConfig(Uint32 cfg_data_source[NUM_ALU_INPUT]
									  ,Uint32 cfg_data_des[NUM_ALU_OUTPUT],Uint32 cfg_op);
															
  void globalInConfig(Uint32 addr_in[NUM_ALU_INPUT], Uint32 addr_out[NUM_ALU_OUTPUT]);
	
	void routeRfConfig(Uint32 addr_in[NUM_ALU_INPUT],Uint32 addr_out[NUM_ALU_OUTPUT]);
	
	void dataAddrConfig(Uint32 addr_in[NUM_ALU_INPUT],Uint32 addr_out[NUM_ALU_OUTPUT]);	
	
	void rcDataConfig(Uint32 addr_in[NUM_ALU_INPUT]
									 	,Uint32 addr_out[NUM_ALU_OUTPUT]);

  //sc_event start_read_event_,start_write_event_;
	bool flag_write_rf_done_, flag_read_rf_done_, flag_need_read_rf_
			,flag_need_write_rf_,flag_route_cfg_itr,flag_rc_execution_done
			,flag_need_new_global_in,flag_need_new_data_from_rc;
	//bool flag_rc_execution_done;

private:
  // module instance

  /* route one rc or one drf as input or output */
  sc_signal<Uint32> route_one_rc[NUM_ALU_INPUT],route_one_rf_out[NUM_ALU_OUTPUT];
	Uint32 route_one_rf_in[NUM_ALU_INPUT];
	
	/* route rc, gloabl mem or rf as input */
	sc_signal<Uint32> cfg_source_route[NUM_ALU_INPUT],cfg_des_route[NUM_ALU_OUTPUT]; 
	
	/* input/output data addresses signals */
	Uint32 addr_global_in_[NUM_ALU_INPUT], addr_global_out_[NUM_ALU_OUTPUT]
				,addr_rf_in_[NUM_ALU_INPUT],addr_rf_out_[NUM_ALU_OUTPUT];
	
	/* input/output data mode signals */
	sc_signal<Uint32> addressing_mode_in[NUM_ALU_INPUT], addressing_mode_out[NUM_ALU_OUTPUT];

	/* input/output data address source or des */
	sc_signal<Uint32> addressing_src_in[NUM_ALU_INPUT], addressing_src_out[NUM_ALU_OUTPUT];

	/* config including description of readRF & writeRF actions */
	sc_event event_read_rf_done_,event_write_rf_done_;
	
	sc_event event_route_in_from_rc_done, event_read_rf_request
					,event_write_rf_quest ,event_route_config_done_
					,event_route_in_from_g_done,event_data_config_done_
					,event_route_in_from_g_request,event_route_in_from_rc_request
					,event_rc_execute_done
					,event_data_from_global_changed,event_data_from_rc_changed
					,event_data_from_rc_catched;

	void readRF(void);
  void writeRF(void);
	void execute(void);	

public:
  // process
	bool isWriteRfDone(void) const;
	bool needWriteRf(void) const;
	
	bool isReadRfDone(void) const;
	bool needReadRf(void) const;

	Vector<Uint32> isRcExecuteDone(void) const;

	String returnName(void) const;

  // constructor
  SC_HAS_PROCESS(Rc);
  Rc(sc_module_name name, Uint32 index_row, Uint32 index_col)
    : sc_module(name)
    ,name_(String(name))
    ,flag_write_rf_done_(false)
    ,flag_read_rf_done_(false)
    ,flag_need_read_rf_(false)
    ,flag_need_write_rf_(false)
    ,flag_route_cfg_itr(false)
    ,flag_rc_execution_done(false)
    ,flag_need_new_global_in(true)
    ,flag_need_new_data_from_rc(true)
    ,row_rc_(index_row)
    ,col_rc_(index_col)
  {
  	/* process "execute" : a sequential circuit */
    SC_THREAD(execute);
    sensitive<<clk_in_.pos();
    
		/* process "routeIn" is implemented as a combinational circuit */
	  SC_THREAD(routeRcIn);
	  for (Uint32 i=0; i<num_rc_route; i++)
			for (Uint32 j=0; j<NUM_ALU_OUTPUT; j++)
				sensitive << data_in_from_rc_[i*NUM_ALU_OUTPUT+j];
		//TODO /* This trigger signal may be removed later */
		
		SC_THREAD(routeGlobalIn);
		//for (Uint32 i=0; i<NUM_RCA_INPORT; i++)
		//	sensitive << data_in_global_[i];
		sensitive<<clk_in_.pos();
		 
		/* process "readRF/writeRF" is implemented as a sequential circuit */
		SC_THREAD(readRF);
		sensitive<<clk_in_.pos();	
		
		SC_THREAD(writeRF);
		sensitive<<clk_in_.pos();
    // initializition
    for (Uint32 i=0; i<NUM_ALU_INPUT; i++){
	    route_one_rc[i] = INROUTE_DEFAULT;
  		route_one_rf_in[i] = INROUTE_DEFAULT;	
  		addr_global_in_[i] = INROUTE_DEFAULT;
  		addr_rf_in_[i] = INROUTE_DEFAULT;
			cfg_source_route[i] = RcInDefault;

			alu_data_in_[i] = DATA_DEFAULT;
			temp_in_from_rc_[i] = DATA_DEFAULT;
			temp_in_from_global_[i] = DATA_DEFAULT;
			temp_in_from_rf_[i] = DATA_DEFAULT;				
  	}
		
  	for (Uint32 i=0; i<NUM_ALU_OUTPUT; i++){
  		route_one_rf_out[i] = INROUTE_DEFAULT;
  		addr_rf_out_[i] = INROUTE_DEFAULT;
			cfg_des_route[i] = RcOutDefault;
  		addr_global_out_[i] = INROUTE_DEFAULT;

			data_output_to_rf_[i] = DATA_DEFAULT;
			alu_data_out_[i] = DATA_DEFAULT;
  	}
		index_alu_input = 0;
		index_alu_output = 0;
  }
  // destructor

private:
  String name_;
  Alu alu_;
  RcaData alu_data_in_[NUM_ALU_INPUT]; 
  RcaData alu_data_out_[NUM_ALU_OUTPUT];
	RcaData	temp_in_from_rc_[NUM_ALU_INPUT], temp_in_from_global_[NUM_ALU_INPUT] 
					,temp_in_from_rf_[NUM_ALU_INPUT];
					//data_in_from_drf_[NUM_ALU_INPUT], data_in_from_sgrf[NUM_ALU_INPUT];
	Uint32 index_alu_input,index_alu_output,row_rc_,col_rc_;
private:
  void routeRcIn();
	void routeGlobalIn();
};

#define prefix_def		template <Uint32 num_rc_route			\
	   		 									   , Uint32 num_port_drf				\
			  									   , Uint32 num_port_sgrf>			\
							 inline void Rc<num_rc_route						\
												   , num_port_drf							\
												   , num_port_sgrf>			

/*---------------------------------------*/
/* interface method for rc configuration */


//////////////////////////////////////////////////////////////////////
//////// Functions for Route Config of RC ////////////////////////////

prefix_def::SourceConfig(Uint32 cfg_source[NUM_ALU_INPUT])
{
	RcSourceCfg cfg;
	flag_need_read_rf_ = false;
	const Uint32 num_link_outputs = NUM_LINK_RC*NUM_ALU_OUTPUT;
	
	/* if any of inputs need read rf, change flag */
	for (Uint32 i=0; i<NUM_ALU_INPUT; i++){
		if ( cfg_source[i] < num_link_outputs ){
			cfg = FromRc; 
		}
		else{
			switch(cfg_source[i]){
				//TODO /* this mapping will not be affected by change of Enum "RcSourCfg" */
				case num_link_outputs : 
					cfg = FromRf; 
					flag_need_read_rf_ = true; 
					break;
				case num_link_outputs+1 : 
					cfg = FromGlobal; 
					break;
				case num_link_outputs+2 : 
					cfg = NoInput; 
					break;
				default: 
					cfg = RcInDefault; 
					break;
			}
		}
		cfg_source_route[i] = (Uint32)cfg;
	}
}

prefix_def::LinkRcConfig(Uint32 cfg_source[NUM_ALU_INPUT])
{
	for (Uint32 i=0; i<NUM_ALU_INPUT; i++){
		route_one_rc[i] = ((cfg_source[i]<NUM_LINK_RC*NUM_ALU_OUTPUT) ? cfg_source[i] : 0x00 );
	}
}

prefix_def::OpConfig(Uint32 cfg_op)
{
	AluOpConfig op = (AluOpConfig)cfg_op;
	alu_.configure(op);
}

prefix_def::DesConfig(Uint32 cfg_des[NUM_ALU_OUTPUT])
{
	flag_need_write_rf_ = false;
	RcDesCfg des_cfg_rf = ToRf;
	/* if any of outputs need write rf, change flag */
	for (Uint32 i=0; i<NUM_ALU_OUTPUT; i++){
		cfg_des_route[i] = cfg_des[i];
		if( cfg_des[i] == des_cfg_rf )
			flag_need_write_rf_ = true;
	}
}

prefix_def::rcRouteConfig(Uint32 cfg_data_source[NUM_ALU_INPUT]
															,Uint32 cfg_data_des[NUM_ALU_OUTPUT],Uint32 cfg_op)
{
	SourceConfig(cfg_data_source);
	LinkRcConfig(cfg_data_source);
	OpConfig(cfg_op);
	DesConfig(cfg_data_des);

	flag_route_cfg_itr = true;
	//wait();
	event_route_config_done_.notify(SC_ZERO_TIME);	
	/* A signal's value would be updated next delta cycle */
	//wait(clk_in_->posedge_event());
	wait(1,SC_NS);
}


///////////////////////////////////////////////////////////////////
/* Global output is configured by RCA */
prefix_def::globalInConfig(Uint32 addr_in[NUM_ALU_INPUT], Uint32 addr_out[NUM_ALU_OUTPUT])
{
	  for (Uint32 i=0; i<NUM_ALU_INPUT; i++){
			/* Whether data input from global */
			if(((addr_in[i]>>(HEAD_RF_FLAGS_BIT-GLOBAL_BITS_WIDTH+1))&0x3) == 0x3){
				/* this equation get the data address without headbit and route info */
    		addr_global_in_[i] = addr_in[i]&((0x1<<(HEAD_GLOBAL_ADDR_BIT+1)) - 1);	
				//TODO: this code shoulde change with number of DRF, but definition is unclear.
				addressing_src_in[i] = (Uint32)FromGlobal;
				flag_need_read_rf_ = false;
			}
	  }

		for (Uint32 i=0; i<NUM_ALU_OUTPUT; i++){
			/* Whether data output to global */
			if(((addr_out[i]>>(HEAD_RF_FLAGS_BIT-GLOBAL_BITS_WIDTH+1))&0x3) == 0x3){
				/* this equation get the data address without headbit and route info */
    		addr_global_out_[i] = addr_out[i]&((0x1<<(HEAD_GLOBAL_ADDR_BIT+1)) - 1);	
				//TODO: this code shoulde change with number of DRF, but definition is unclear.
				addressing_src_out[i] = (Uint32)FromGlobal;
			}
	  }
}
 
prefix_def::routeRfConfig(Uint32 addr_in[NUM_ALU_INPUT],Uint32 addr_out[NUM_ALU_OUTPUT])
{
  for (Uint32 i=0; i<NUM_ALU_INPUT; i++){
		//Data from DRF0-3
		if(((addr_in[i]>>(HEAD_RF_FLAGS_BIT-GLOBAL_BITS_WIDTH+1))&0x3) == 0x0){
			/* this equation get the route rf info */
	    route_one_rf_in[i] = ((addr_in[i])>>(HEAD_DRF_ADDR_BIT+1))&0x7;
			/* Record addr source in when in indirect addressing mode */		
			addressing_src_in[i] = (Uint32)FromRf;
			/*If value changed, wait for update, else wait two delta time */
			//wait(2*SC_ZERO_TIME, route_one_rf_in[i].value_changed_event());
		}
		else if(((addr_in[i]>>(HEAD_RF_FLAGS_BIT-GLOBAL_BITS_WIDTH+1))&0x3) == 0x2){
			/* this equation enable the sgrf route */
	    route_one_rf_in[i] = num_port_drf; 
			addressing_src_in[i].write((Uint32)FromRf);
			/*If value changed, wait for update, else wait two delta time */
			//wait(2*SC_ZERO_TIME, route_one_rf_in[i].value_changed_event());
		} 
  }
	//Data from SGRF
	for (Uint32 i=0; i<NUM_ALU_OUTPUT; i++){
		if(((addr_out[i]>>(HEAD_RF_FLAGS_BIT-GLOBAL_BITS_WIDTH+1))&0x3) == 0x0){
			/* this equation get the route rf info */
	    route_one_rf_out[i] = ((addr_in[i])>>(HEAD_DRF_ADDR_BIT+1))&0x7;
			addressing_src_out[i] = (Uint32)FromRf;
			/*If value changed, wait for update, else wait two delta time */
			//wait(2*SC_ZERO_TIME, route_one_rf_in[i].value_changed_event());
		}
		else if(((addr_out[i]>>(HEAD_RF_FLAGS_BIT-GLOBAL_BITS_WIDTH+1))&0x3) == 0x2){
			/* this equation enable the sgrf route */
	    route_one_rf_out[i] = num_port_drf; 
			addressing_src_out[i] = (Uint32)FromRf;
			/*If value changed, wait for update, else wait two delta time */
			//wait(2*SC_ZERO_TIME, route_one_rf_in[i].value_changed_event());
		}
	}
}

/* interface method for read/write RF */
prefix_def::dataAddrConfig(Uint32 addr_in[NUM_ALU_INPUT],Uint32 addr_out[NUM_ALU_OUTPUT])
{
	for (Uint32 i=0; i<NUM_ALU_INPUT; i++){
		/* get data input mode */
		addressing_mode_in[i].write((addr_in[i]>>(HEAD_RF_FLAGS_BIT+1))&0x3);
		wait(clk_in_.posedge_event());

		RcDataAddressingMode mode = ImmAddressing;
		/* get data/address input address or immediate data */
		if(addressing_mode_in[i] != (Uint32)mode){
			if(((addr_in[i]>>(HEAD_RF_FLAGS_BIT-GLOBAL_BITS_WIDTH+1))&0x3) == 0x0)
				/* this equation get low 7-bit addr of drf */
		    addr_rf_in_[i] = addr_in[i]&((0x01<<(HEAD_DRF_ADDR_BIT+1))-1);
			else if(((addr_in[i]>>(HEAD_RF_FLAGS_BIT-GLOBAL_BITS_WIDTH+1))&0x3) == 0x2)
				/* this equation get low 11-bit addr of sgrf */
				addr_rf_in_[i] = addr_in[i]&((0x01<<(HEAD_SGRF_ADDR_BIT+1))-1);
		}else{
		   /* this equation get low 13-bit immediate data */
			 assert(cfg_source_route[i] == NoInput);
			 addr_rf_in_[i] = addr_in[i]&((0x01<<(HEAD_RF_FLAGS_BIT+1))-1);
		}
  }

	for (Uint32 i=0; i<NUM_ALU_OUTPUT; i++){
		/* get data output mode */
		addressing_mode_out[i].write((addr_out[i]>>(HEAD_RF_FLAGS_BIT+1))&0x3);
    wait(clk_in_.posedge_event());
		
		RcDataAddressingMode mode = ImmAddressing;
		/* get data output address */
		if(addressing_mode_out[i] != (Uint32)mode){
		if(((addr_out[i]>>(HEAD_RF_FLAGS_BIT-GLOBAL_BITS_WIDTH+1))&0x3) == 0x0)
			/* this equation get low 7-bit addr of drf */
	    addr_rf_out_[i] = addr_out[i]&((0x01<<(HEAD_DRF_ADDR_BIT+1))-1);
		else if(((addr_out[i]>>(HEAD_RF_FLAGS_BIT-GLOBAL_BITS_WIDTH+1))&0x3) == 0x2)
			/* this equation get low 11-bit addr of sgrf */
			addr_rf_out_[i] = addr_out[i]&((0x01<<(HEAD_SGRF_ADDR_BIT+1))-1);
		}else{
		   /* this equation get low 13-bit immediate data */
			 for(Uint32 j=0; j<NUM_ALU_OUTPUT; )
			 	assert(cfg_source_route[j] == NoInput);
			 addr_rf_out_[i] = addr_in[i]&((0x01<<(HEAD_RF_FLAGS_BIT+1))-1);
		}
	}
}

prefix_def::rcDataConfig(Uint32 addr_in[NUM_ALU_INPUT],Uint32 addr_out[NUM_ALU_OUTPUT])
{
#if DEBUG_RC_DATACFG
	cout<<"<<<<< Time: "<<sc_time_stamp()<<","
		  <<" "<<name_
		  <<": RC Data Config Event"<<endl;
#endif
	globalInConfig(addr_in, addr_out);
	routeRfConfig(addr_in, addr_out);
	dataAddrConfig(addr_in, addr_out);

	event_data_config_done_.notify(SC_ZERO_TIME);
	//wait(clk_in_->posedge_event());
	wait();
	/* This part will be revised later, this sentence will be in use. */
	//wait(event_rc_execute_done);
}


/////////////////////////////////////////////////////////////////////
/* alu execution function */
prefix_def::execute()
{
	wait();
	wait(event_route_config_done_);
  while(true){		
		/* after route config, reset this flag */
		flag_route_cfg_itr = false;
		/* every time route config change initialize execution flag */
		flag_rc_execution_done = false;

		#if DEBUG_RC_EXECUTE
			cout<<"<<<<< Time: "<<sc_time_stamp()<<", "
			    <<name_<<": Start waiting for data or route cfg iterrupt"<<endl;
		#endif
		
		/* this code is for pipeline state */
		while(!flag_route_cfg_itr)
		{			
			/* this circulation will be interrupted by route config and driven by
		   data config */
		 	wait(event_data_config_done_|event_route_config_done_);
			/* every time data config change reset execution flag */
			flag_rc_execution_done = false;
			
			wait(1,SC_NS);			
			
			/* if route config change, computing part will be bypass. */
			if(!flag_route_cfg_itr){

			#if DEBUG_RC_EXECUTE	
			cout<<"<<<<< Time: "<<sc_time_stamp()<<","
	        <<" "<<name_
		      <<": Data Config Finished, Start Read Input Data"<<endl;
			#endif

			/* if any input data is from other rc, wait for data coming */
			bool flag_input_from_rc = false;
			for(Uint32 i=0; i<NUM_ALU_INPUT; i++)
				if(cfg_source_route[i] == FromRc)
					flag_input_from_rc = true;
			if(flag_input_from_rc)
				wait(event_data_from_rc_catched);

				for(Uint32 i =0; i<NUM_ALU_INPUT; i++){
					index_alu_input = i; 
					RcDataAddressingMode mode = (RcDataAddressingMode)addressing_mode_in[i].read();
					
			    switch(cfg_source_route[i])
			    {
			    case NoInput: 
							 switch(mode)
							 {
							 case ImmAddressing: alu_data_in_[i] = addr_rf_in_[i];
							 
							 										 #if DEBUG_RC_EXECUTE
																		 cout<<"<<<<< Time: "<<sc_time_stamp()<<","
																		     <<" "<<name_
																				 <<": Read Immediate Data, Value = "<<alu_data_in_[i]<<endl;
																	 #endif
							            default: break;
							 }
							 break;
			    case FromRc:  
							 event_route_in_from_rc_request.notify();
							 wait(event_route_in_from_rc_done);
							 alu_data_in_[i] = temp_in_from_rc_[i]; 
							 #if DEBUG_RC_EXECUTE
							 cout<<"<<<<< Time: "<<sc_time_stamp()<<","
								   <<" "<<name_<<": Read Data from Other RC, Value = "<<alu_data_in_[i]<<endl;
							 #endif
							 
							 break;
			    case FromRf:
							 RcaData addr_rf;
							 switch(mode)
								{
								case DirectAddressing:
											event_read_rf_request.notify(); 												
											wait(event_read_rf_done_);
											alu_data_in_[i] = temp_in_from_rf_[i];
											
											#if DEBUG_DATA_FROM_RF_DIRECT
										  cout<<"<<<<< Time: "<<sc_time_stamp()<<","
													 <<" "<<name_
													 <<": Read RF Directly, Value = "<<alu_data_in_[i]<<endl;
										  #endif
											
											break;																				
								case ImmAddressing:assert(0);
								break;
								case IndirectAddressing:
										 switch(addressing_src_in[i])
										{
										case FromRf: 	event_read_rf_request.notify(); 												
																	wait(event_read_rf_done_);
																	addr_rf = temp_in_from_rf_[i];
																	
																	#if DEBUG_RC_EXECUTE
																	cout<<"<<<<< Time: "<<sc_time_stamp()<<","
																		  <<" "<<name_
																			<<": Read RF Address, Addr = "<<addr_rf<<endl;
										  						#endif			
																	
																	addr_rf_in_[i] = addr_rf;
																	route_one_rf_in[i] = num_port_drf;
																	event_read_rf_request.notify(SC_ZERO_TIME); 												
																	wait(event_read_rf_done_);
																	alu_data_in_[i] = temp_in_from_rf_[i];
																	
																	#if DEBUG_RC_EXECUTE
																	cout<<"<<<<< Time: "<<sc_time_stamp()<<","
																		  <<" "<<name_
																			<<": Read SGRF, Value = "<<alu_data_in_[i]<<endl;
										  						#endif
																	
																	break;
									case FromGlobal:event_route_in_from_g_request.notify();
															    wait(event_route_in_from_g_done);
																	addr_rf = temp_in_from_global_[i];

																	#if DEBUG_RC_EXECUTE
																  cout<<"<<<<< Time: "<<sc_time_stamp()<<","
																		  <<" "<<name_
																		  <<": Read Global Address, Addr = "<<addr_rf<<endl;
																	#endif

																	addr_rf_in_[i] = addr_rf;
																	route_one_rf_in[i] = num_port_drf;
																	event_read_rf_request.notify(SC_ZERO_TIME); 												
																	wait(event_read_rf_done_);
																	alu_data_in_[i] = temp_in_from_rf_[i];

																	#if DEBUG_RC_EXECUTE
																  cout<<"<<<<< Time: "<<sc_time_stamp()<<","
																		  <<" "<<name_
																		  <<": Read SGRF, Value = "<<alu_data_in_[i]<<endl;
																	#endif 																			
												 default: break;
										}
										break;
								default:
									  break;																			
								}
								break;
		  case FromGlobal:  
								RcaData addr_global;
								switch(mode)
								{
							 case DirectAddressing: event_route_in_from_g_request.notify();
																	    wait(event_route_in_from_g_done);
																			alu_data_in_[i] = temp_in_from_global_[i];

																			#if DEBUG_RC_EXECUTE
																			cout<<"<<<<< Time: "<<sc_time_stamp()<<","
																		      <<" "<<name_
																				  <<": Read Global, Value = "<<alu_data_in_[i]<<endl;
																			#endif
																			break;
									  case ImmAddressing: assert(0);
									 										break;
								case IndirectAddressing: switch(addressing_src_in[i])
																			{
																			case FromRf:
																					 event_read_rf_request.notify(); 												
																					 wait(event_read_rf_done_);
																					 addr_global = temp_in_from_rf_[i];

																					 #if DEBUG_RC_EXECUTE
																					 cout<<"<<<<< Time: "<<sc_time_stamp()<<","
																		           <<" "<<name_
																						   <<": Read RF Addr, Addr = "<<addr_global<<endl;
																					 #endif
																			
																					 alu_data_in_[i] = data_in_global_[addr_global].read();
																					 
																					 #if DEBUG_RC_EXECUTE
																					 cout<<"<<<<< Time: "<<sc_time_stamp()<<","
																		           <<" "<<name_
																						   <<": Read Global, Value = "<<alu_data_in_[i]<<endl;
																					 #endif
																					 
																					 break;
																			case FromGlobal: 
																					 addr_global = data_in_global_[addr_global_in_[i]].read();
																					 #if DEBUG_RC_EXECUTE
																					 cout<<"<<<<< Time: "<<sc_time_stamp()<<","
																		           <<" "<<name_
																						   <<": Read Global Addr, Addr = "<<addr_global<<endl;
																					 #endif
																					 
																					 alu_data_in_[i] = data_in_global_[addr_global].read();
																					 #if DEBUG_RC_EXECUTE
																					 cout<<"<<<<< Time: "<<sc_time_stamp()<<","
																		           <<" "<<name_
																						   <<": Read Global, Value = "<<alu_data_in_[i]<<endl;
																					 #endif
																					 
																					 break;
																	default: break;
																			}
								                      break;
															default:break;																			
								}
								break;								
	 	 case RcInDefault:  break;
				      default:  break;
			    }
				}
		    wait();
				
		    #if DEBUG_RC_EXECUTE
				cout<<"<<<<< Time: "<<sc_time_stamp()<<","
					  <<" "<<name_
						<<": Start Compute "<<endl;
				 #endif
				
		  	alu_.compute(alu_data_in_, alu_data_out_);
		  	/* Output data based on Routing out config */
				for(Uint32 i =0; i<NUM_ALU_OUTPUT; i++){
					RcDataAddressingMode mode = (RcDataAddressingMode)addressing_mode_out[i].read();
					index_alu_output = i; 
			    switch(cfg_des_route[i])
			    {  
					case ToRc: data_output_to_rc_[i] = alu_data_out_[i];
					
										 #if DEBUG_RC_EXECUTE
									   cout<<"<<<<< Time: "<<sc_time_stamp()<<","
											   <<" "<<name_
											   <<": Output To RC, Value = "<<alu_data_out_[i]<<endl;
										 #endif
										 break;			   
			    case ToRf: RcaData addr_rf;
										 switch(mode)
										 {
								case DirectAddressing:
												   data_output_to_rf_[i] = alu_data_out_[i];
													 event_write_rf_quest.notify(SC_ZERO_TIME); 
											     wait(event_write_rf_done_);																						 

													 #if DEBUG_RC_EXECUTE
													 cout<<"<<<<< Time: "<<sc_time_stamp()<<","
															 <<" "<<name_
														   <<": Write RF, Value = "<<data_output_to_rf_[i]<<endl;
													 #endif
													 break;
							 case ImmAddressing: 
													 assert(0);
												 	 break;
				       case IndirectAddressing:
										       switch(addressing_src_out[i])
													{
										 case FromRf:
										 				addr_rf_in_[i] = addr_rf_out_[i];
														/* Data Addr Source: from DRF0-3 or SGRF */
														route_one_rf_in[i] = route_one_rf_out[i];														
										 				event_read_rf_request.notify(SC_ZERO_TIME); 												
														wait(event_read_rf_done_);
														addr_rf = temp_in_from_rf_[i];
														
														#if DEBUG_RC_EXECUTE
														cout<<"<<<<< Time: "<<sc_time_stamp()<<","
																<<" "<<name_
																<<": Read RF Write Address, Addr = "<<addr_rf<<endl;
							  						#endif			
														
														addr_rf_out_[i] = addr_rf;
														/* Data Des: to SGRF */
														route_one_rf_out[i] = num_port_drf;
														data_output_to_rf_[i] = alu_data_out_[i];
														event_write_rf_quest.notify(SC_ZERO_TIME); 												
														wait(event_write_rf_done_);
														
														#if DEBUG_RC_EXECUTE
														 cout<<"<<<<< Time: "<<sc_time_stamp()<<","
																 <<" "<<name_
																 <<": Write SGRF, Value = "<<data_output_to_rf_[i]<<endl;
							  						#endif
														
														break;
									 case FromGlobal:
									 					addr_global_in_[i] = addr_global_out_[i];
									 				  event_route_in_from_g_request.notify(SC_ZERO_TIME);
												    wait(event_route_in_from_g_done);
														addr_rf = temp_in_from_global_[i];

														#if DEBUG_RC_EXECUTE
														 cout<<"<<<<< Time: "<<sc_time_stamp()<<","
																 <<" "<<name_
															   <<": Read Global Address, Addr = "<<addr_rf<<endl;
														#endif

														addr_rf_out_[i] = addr_rf;
														/* Data Des: to SGRF */
														route_one_rf_out[i] = num_port_drf;
														data_output_to_rf_[i] = alu_data_out_[i];
														event_write_rf_quest.notify(SC_ZERO_TIME); 												
														wait(event_write_rf_done_);

														#if DEBUG_RC_EXECUTE
														 cout<<"<<<<< Time: "<<sc_time_stamp()<<","
																 <<" "<<name_
															   <<": Write SGRF, Value = "<<data_output_to_rf_[i]<<endl;
														#endif 																			
									    default: 
									    			break;
													}
												break;
										default:
												break;																			
										}
										break;

			case ToGlobal:  data_output_to_global_[i] = alu_data_out_[i];
											#if DEBUG_WRITE_GLOBAL
											cout<<"<<<<< Time: "<<sc_time_stamp()<<","
													<<" "<<name_
												  <<": Write Global Data, Value = "<<alu_data_out_[i]<<endl;
											#endif 	
											break;
			case NoOutput:  break;
	case RcOutDefault:  break;
			    }
				}

				#if DEBUG_RC_EXECUTE
			 	cout<<"<<<<< Time: "<<sc_time_stamp()<<","
	          <<" "<<name_
			      <<": Execution Finished "<<endl;
			  #endif

				flag_rc_execution_done = true;
				event_rc_execute_done.notify();
		    wait();
			}
		}
  }
}

/* input data from other RCs */
prefix_def::routeRcIn()
{
//TODO: data inputs from RC may reach in different cycle, in this case, the later
//one may be fetched a wrong data.	
//This process has got revised.
	while(true){
		/* This process is triggerred by any value changed event of input_from_rc */		
		bool flag_data_catched[NUM_ALU_INPUT], flag_all_data_catched = false;
		bool flag_no_input_from_rc = false;
		
		while(!flag_all_data_catched)
		{
			/* When no input data from rc, this process may keep stay here, that's ok. */
			wait();
			/* if no input data from rc,this process may be triggerred by other rc, then break */
			bool flag_input_from_rc = false;
			for(Uint32 i=0; i<NUM_ALU_INPUT; i++)
				if(cfg_source_route[i] == FromRc)
					flag_input_from_rc = true;
			if(!flag_input_from_rc)
				break;
			
			/* If process trigger, catch right data from other rc. */
			for(Uint32 i=0; i<NUM_ALU_INPUT; i++){
				/* test whether input data of this inport is from RC */
				if(cfg_source_route[i] == FromRc){
					if(data_in_from_rc_[route_one_rc[i]].event()){
						/* if value update, catch this data */
						temp_in_from_rc_[i] = data_in_from_rc_[route_one_rc[i]].read();
						flag_data_catched[i] = true;
					}else
						flag_data_catched[i] = false;
				}else{
					/* Input data was not from other rc */
					flag_data_catched[i] = true;
				}
			}
			/* Update RouteRCIn flag */
			flag_all_data_catched = true;
			for(Uint32 i=0; i<NUM_ALU_INPUT; i++){	
				if(cfg_source_route[i] == FromRc){
					flag_all_data_catched &= flag_data_catched[i];
				}
			}
		}
		/* make sure before this event notify, rc already wait for data catch */
		/* make sure when no input data from rc, rc would not wait for this event */
		event_data_from_rc_catched.notify();

		bool flag_all_data_fetched = true;
		bool flag_data_fetched[NUM_ALU_INPUT];
		/* inital for flags */
		for(Uint32 i=0; i<NUM_ALU_INPUT; i++){
			if(cfg_source_route[i] == FromRc)
				flag_data_fetched[i] = false;
			else
				/* if no input from rc, then skimp next fetch data process */
				flag_data_fetched[i] = true;
			flag_all_data_fetched &= flag_data_fetched[i];
		}			
	  while(!flag_all_data_fetched)
	  {  
	    wait(event_route_in_from_rc_request);
			#if DEBUG_RC_ROUTERCIN
			  cout<<"<<<<< Time :"<<sc_time_stamp()<<","
			      <<" "<<name_
			      <<": Here is a Route Rc In Request"<<endl;
		  #endif
			flag_data_fetched[index_alu_input] = true;			 
		  event_route_in_from_rc_done.notify();
			/* Update flags */
			flag_all_data_fetched = true;
			for(Uint32 i=0; i<NUM_ALU_INPUT; i++)
					flag_all_data_fetched &= flag_data_fetched[i];
			}			
	  }
	
	return;
}
/* input data from global Memory */
prefix_def::routeGlobalIn()
{
 	while(true){		
		wait(event_route_in_from_g_request);
		
		#if DEBUG_RC_ROUTEGLOBALIN
		cout<<"<<<<< Time: "<<sc_time_stamp()<<","
		    <<" "<<name_
		    <<": Here is a ALU Read Global Data Request"<<endl;
		#endif
		
		Uint32 index = index_alu_input;
		assert(addr_global_in_[index]<NUM_RCA_INPORT);
		temp_in_from_global_[index] = data_in_global_[addr_global_in_[index]].read();	

    #if DEBUG_READ_GLOBAL
       	cout<<"<<<<< Time: "<<sc_time_stamp()<<","
		    <<" "<<name_
		    <<": Read Global Data, Addr:"<<addr_global_in_[index]<<", Data:"<<temp_in_from_global_[index]<<endl;
    #endif
    
		event_route_in_from_g_done.notify(SC_ZERO_TIME);
 	}
	return;
}

prefix_def::readRF()
{
	wait();
	/* read RF if notified	*/
	while(true){
		wait(event_read_rf_request);
		Uint32 index = index_alu_input;
		assert(route_one_rf_in[index]>=0 && route_one_rf_in[index]
																				< ((0x1<<DRF_BITS_WIDTH)-1) );
		Uint32 addr = addr_rf_in_[index];
		DATA_WIDTH_SGRF buffer[32];
				
		if(route_one_rf_in[index] < num_port_drf) {    
			// example : 0x00-0x02 for drf 0x03 for sgrf
			port_link_drf_[route_one_rf_in[index] ]->read(addr, alu_data_in_[index]);
		} 
		else {
			port_link_sgrf_[route_one_rf_in[index] - num_port_drf ]
				->multiRead(buffer, addr, 1);
			temp_in_from_rf_[index] = buffer[0];	
		}					

		event_read_rf_done_.notify(SC_ZERO_TIME);
	}
}

prefix_def::writeRF()
{
	wait();
	while(true)
	{
		/* write RF if quest	*/
		wait(event_write_rf_quest);
		flag_write_rf_done_ = false;
		Uint32 index = index_alu_output;
		assert((route_one_rf_out[index]>=0) && (route_one_rf_out[index]
																				< num_port_drf + num_port_sgrf) );
		Uint32 addr = addr_rf_out_[index];
		RegsData data = data_output_to_rf_[index];
		if(route_one_rf_out[index] < num_port_drf) { 		
			/* example : 0x00-0x02 for drf 0x03 for sgrf */
			port_link_drf_[route_one_rf_out[index]]->write(addr, data);
		}	else {
			port_link_sgrf_[route_one_rf_out[index] - num_port_drf ]->write(addr, data);
		}

		event_write_rf_done_.notify();
		flag_write_rf_done_ = true;
	}

}

#define prefix_def2	 	template <Uint32 num_rc_route					\
										   		   , Uint32 num_port_drf						\
												   , Uint32 num_port_sgrf>					\
							inline bool Rc<num_rc_route									\
												   , num_port_drf									\
												   , num_port_sgrf>	
					  
prefix_def2::isWriteRfDone(void) const
{
	return flag_write_rf_done_;
}

prefix_def2::needWriteRf(void) const
{
	return flag_need_write_rf_;
}

prefix_def2::isReadRfDone(void) const
{
	return flag_read_rf_done_;
}

prefix_def2::needReadRf(void) const
{
	return flag_need_read_rf_;
}


template <Uint32 num_rc_route,Uint32 num_port_drf,Uint32 num_port_sgrf>					
inline Vector<Uint32> Rc<num_rc_route,num_port_drf,num_port_sgrf>	
						::isRcExecuteDone(void) const
{
	Vector<Uint32> flag_row_col;
	flag_row_col.push_back((Uint32)flag_rc_execution_done);
	flag_row_col.push_back(row_rc_);	
	flag_row_col.push_back(col_rc_);
	return flag_row_col;
}

template <Uint32 num_rc_route,Uint32 num_port_drf,Uint32 num_port_sgrf>					
inline String Rc<num_rc_route,num_port_drf,num_port_sgrf>	
						::returnName(void) const
{
	return name_;
}

#undef prefix_def
#undef prefix_def2

#endif
