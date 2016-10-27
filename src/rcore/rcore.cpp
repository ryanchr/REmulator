/*****************************************************************************
-----------------------------------------------------------------------------------
    @File:    rcore.cpp
    @Author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @Version: 1.0, 
    @Time:    2010-06-28, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file mainly implements the rcore class definition.
-----------------------------------------------------------------------------------
 *****************************************************************************/

#include <systemc.h>
#include "rcore.h"
#include "../parameter/parameter_arch.h"
#include "../tools/system_def.h"

using namespace RcoreParameter;

// sc_interface method
void Rcore::writeReadVgrfCfg(Vector<Vector<Uint32> > read_vgrf_cfg)
{
	m_read_vgrf_context_.clear();
	Uint32 size = read_vgrf_cfg.size();
	m_read_vgrf_context_.reserve(size);
	for(Uint32 i=0; i<(Uint32)read_vgrf_cfg.size(); i++)
		m_read_vgrf_context_.push_back(read_vgrf_cfg[i]);
	//wait();

	#if DEBUG_RCORE_WRITECFG
		cout<<"<<<<< Time: "<<sc_time_stamp()<<","
		    <<" Rcore: Read VGRF Config"<<endl;
	#endif
	even_read_vgrf_cfg.notify();
	/* there are two another wait(event) for this event and next event in the same thread */
	wait();
}

void Rcore::writeWriteVgrfCfg(Vector<Vector<Uint32> > write_vgrf_cfg)
{
	#if DEBUG_RCORE_WRITECFG
		cout<<"<<<<< Time "<<sc_time_stamp()<<": "<<endl;
		cout<<"<<<<<  Rcore: Write VGRF Config"<<endl;
	#endif
	m_write_vgrf_context_ = write_vgrf_cfg;
	//wait();
	even_write_vgrf_cfg.notify();
}

void Rcore::writeRouteCfg(RouteSegmentCfg route_context)
{	
  #if DEBUG_RCORE_ROUTE_CONFIG
		cout<<"<<<<< Time: "<<sc_time_stamp()<<", "
		    <<"Rcore: Write Route Config"<<endl;
	#endif	
	m_route_context_ = route_context;
	//wait();
	
	/* Route Config of RCA */
	rca_->RouteConfig(m_route_context_);
	
	/* Route Config of Jump Module for Read VGRF Context Jump */
	Vector<Uint32> module_src,module_op,module_des;
	module_src = route_context.data_source_[NUM_RC_ROW+1];
	module_op = route_context.op_rc_[NUM_RC_ROW+1];
	module_des = route_context.data_des_[NUM_RC_ROW+1];
	jump_modular_r_vgrf->ModuleRouteCfg(module_src, module_op,module_des);
  #if DEBUG_RCORE_ROUTE_CONFIG
		cout<<"<<<<< Time: "<<sc_time_stamp()<<", "
		    <<"Rcore: "<<jump_modular_r_vgrf->returnName()<<" Write Route Config"<<endl;
	#endif	
	
  module_src = route_context.data_source_[NUM_RC_ROW+2];
	module_op = route_context.op_rc_[NUM_RC_ROW+2];
  module_des = route_context.data_des_[NUM_RC_ROW+2];
	jump_modular_w_vgrf->ModuleRouteCfg(module_src, module_op,module_des);
	#if DEBUG_RCORE_ROUTE_CONFIG
	cout<<"<<<<< Time: "<<sc_time_stamp()<<", "
		    <<"Rcore: "<<jump_modular_w_vgrf->returnName()<<" Write Route Config"<<endl;
	#endif	
	/**/
	event_write_route_context.notify();
}
/* Function called under nonepipeline state by TopSys MainAction */
void Rcore::writeDataCfg(DataSegmentCfg data_context)
{
  m_data_context_ = data_context;
  wait();
	#if DEBUG_RCORE_WRITECFG
	  cout<<"<<<<< Time: "<<sc_time_stamp()<<","
	      <<" Rcore: Transfer Data Config to RCA"<<endl;
	#endif
  rca_->DataConfig(m_data_context_);
}

void Rcore::writeDataCfgGroup(Vector<DataSegmentCfg*> data_context)
{
	m_data_group_.clear();
	#if DEBUG_RCORE_WRITECFG
	  cout<<"<<<<< Time: "<<sc_time_stamp()<<", "
	      <<" Rcore: Write DataGroupCfg when nonepipeline"<<endl;
	#endif
	for(Uint32 i = 0; i<(Uint32)data_context.size(); i++)
  	m_data_group_.push_back(*data_context[i]);
  
  rca_->DataGroupConfig(m_data_group_);
}

// process:for what?
void Rcore::routeRCAIn()
{
	wait();
  while(true)
  {
		/* This thread action is based on pipelining state */
		/* So make sure pipeline state is set before read vgrf event */
		//TODO: This process action based on flag_pipeline, it omits variation of
		//flag_pipeline and it should has nothing to do with flag_pipeline.
		
		/* For pipeline state, route RCA input only once, these input data come from VGRF */
			if(flag_pipeline_) {
				wait(event_read_vgrf_done);
				/* Computation of each RC is driven by signal rca_data_in*/
	    	for (Uint32 i=0; i<NUM_RCA_INPORT; i++)    
	      	rca_data_in_[i] = rca_data_in_buf_[i];
				
				cout<<"<<<<< Time "<<sc_time_stamp()<<": "<<endl;
				cout<<"<<<<<  Rcore: Route RCA In(pipeline) "<<endl;
				
				route_rca_in.notify();
			} else {
					wait(event_read_vgrf_done & event_data_cfg_read_global);
					
		    	for (Uint32 i=0; i<NUM_RCA_INPORT; i++)    
		      	rca_data_in_[i] = rca_data_in_buf_[i]; 

					#if DEBUG_RCORE_ROUTERCAIN
						cout<<"<<<<< Time: "<<sc_time_stamp()<<","
						    <<" Rcore: Route RCA In(unpipeline) "<<endl;
					#endif
					
					route_rca_in.notify(SC_ZERO_TIME);
					event_data_cfg_can_read.notify(SC_ZERO_TIME);					
					wait();
					
			}			
  }
}

void Rcore::isRCAExecuteDone()
{
	wait();
	while(true){
		wait();		
		flag_execution_done_ = rca_->isAllRcComputeDone();
		#if DEBUG_RCORE_ISRCAEXECUTEDONE
			cout<<"<<<<< Time: "<<sc_time_stamp()<<","
	    <<" "<<"Thread IsRCAExecuteDone, Flag is "<<flag_execution_done_<<endl;
		#endif
	}
}

// private method
void Rcore::readVGregs()
{
	wait();
	while(true){
		/* These two event near */
		wait(event_set_state & even_read_vgrf_cfg);

		Vector<Uint32> tmp_read_vgrf_cfg;		
		/* Under pipelining state, default size of this context is 1 */
		for(Uint32 i_cfg = 0; i_cfg<m_read_vgrf_context_.size(); i_cfg++){			
			/* check whether data config jump happen */
			if(!flag_pipeline_){ 
				if(flag_module_data_cfg_on && flag_data_cfg_jump){
					wait(event_one_data_context_done);
					/* If it is a outside Data Cfg jump */
					//TODO:May be travesing is not the best way to trigger read vgrf
					if(idx_data_cfg_running != idx_next_data_cfg)
						for(Uint32 j=0; j<m_read_vgrf_context_.size(); j++)
								if(m_read_vgrf_context_[j][0] == idx_next_data_cfg)
									i_cfg = j;
				}					
			}
			/* Extract config info */
			Vector<Uint32> cfg_read_vgrf = m_read_vgrf_context_[i_cfg];
			Vector<RegsData> read_buf;

			assert(cfg_read_vgrf.size()==8);
			Uint32 idx_data_cfg = cfg_read_vgrf[0];
			Uint32 index_vgrf = cfg_read_vgrf[1];
			Uint32 addr_row_head_r = cfg_read_vgrf[2];
			Uint32 addr_col_head_r = cfg_read_vgrf[3];
			Uint32 mode_r = cfg_read_vgrf[4]; 
			Uint32 row_r = cfg_read_vgrf[5]; 
			Uint32 col_r = cfg_read_vgrf[6];
			Uint32 num_read = cfg_read_vgrf[7];
			
			/* synchronization with RCA when under none pipeline state */
			if(!flag_pipeline_)
				while(idx_data_cfg != idx_data_cfg_running ) wait();

			#if DEBUG_RCORE_READVGRF
				cout<<"<<<<< Time: "<<sc_time_stamp()<<","
				    <<" Rcore: Read VGRF "<<index_vgrf<<endl;
			#endif
			
			if(num_read)
				port_to_vgregs_[index_vgrf]->blockRead(addr_row_head_r,addr_col_head_r
																					   , mode_r,row_r,col_r, &read_buf);

			#if DEBUG_DATACFG_RUN
					cout<<"<<<<< Time: "<<sc_time_stamp()<<","
					    <<" Rcore: Running Read VGRF Cfg_"<<i_cfg<<endl;
				#endif

			if(flag_module_r_vgrf_on && flag_read_vgrf_jump)
				m_read_vgrf_context_[i_cfg] = tmp_read_vgrf_cfg;
	
			assert(read_buf.size()<=NUM_RCA_INPORT);
			assert(read_buf.size()==num_read);

			for (Uint32 i=0; i<read_buf.size(); i++)
			  	rca_data_in_buf_[i] = read_buf[i]; 
			/* wait for rca route global input done */
			if(!flag_pipeline_) {
				/* trigger the THREAD of routing rca in */
				event_read_vgrf_done.notify(SC_ZERO_TIME);
				/* trigger the THREAD of routing rca in */
				wait(route_rca_in);				
			}

			wait();
			/* Data Config of Jump Module for read VGRF */
			Vector<Uint32> module_addr_in = m_rcore_context_.jump_read_vgrf_cfg[index_vgrf].data_in;
			Vector<Uint32> module_addr_out = m_rcore_context_.jump_read_vgrf_cfg[index_vgrf].data_out;
			Vector<Uint32> module_mode = m_rcore_context_.jump_read_vgrf_cfg[index_vgrf].mode;
			Vector<Uint32> jump_info;
			flag_module_r_vgrf_on = (bool)module_mode[2];

			if(flag_module_r_vgrf_on){
				jump_info = jump_modular_r_vgrf->ModuleDataCfg(module_addr_in, module_addr_out,module_mode);
  			flag_read_vgrf_jump = (bool)jump_info[0];
			}else
				flag_read_vgrf_jump = false;

			if(flag_module_r_vgrf_on){
				if(flag_read_vgrf_jump==true) {
					idx_next_read_vgrf_cfg = jump_info[2];
					Uint32 jump_addr_row_head_mode = ((jump_info[1])>>14)&0x3;
					Uint32 jump_addr_row_head_var = ((jump_info[1])>>8)&0x3f;
					Uint32 jump_addr_col_head_mode = ((jump_info[1])>>6)&0x3;
					Uint32 jump_addr_col_head_var = (jump_info[1])&0x3f;

					switch(jump_addr_row_head_mode)
					{
					case 0: tmp_read_vgrf_cfg = m_read_vgrf_context_[idx_next_read_vgrf_cfg];
									tmp_read_vgrf_cfg[1] = m_read_vgrf_context_[idx_next_read_vgrf_cfg][2] + jump_addr_row_head_var;
									break;
					case 1: m_read_vgrf_context_[idx_next_read_vgrf_cfg][2] += jump_addr_row_head_var;
									tmp_read_vgrf_cfg = m_read_vgrf_context_[idx_next_read_vgrf_cfg];
									break;
					default: assert(0); break;
					}
					wait(event_need_read_vgrf);	
					flag_need_revert_data_cfg = true;
					event_revert_data_cfg.notify();
					#if DEBUG_RCORE_READ_VGRF_JUMP
						cout<<"<<<<< Time: "<<sc_time_stamp()<<","
						    <<" Rcore: Read VgrfCfg Jump to VGRFCfg_"<<idx_next_read_vgrf_cfg<<endl;
					#endif
				}else {
					wait(event_need_read_vgrf);
					flag_need_revert_data_cfg = false;
					event_revert_data_cfg.notify();
					
					idx_next_read_vgrf_cfg = i_cfg + 1;
				}
			}else {
			  wait(event_need_read_vgrf);
				flag_need_revert_data_cfg = false;
				event_revert_data_cfg.notify();
				idx_next_read_vgrf_cfg = i_cfg + 1;
			}
			i_cfg = idx_next_read_vgrf_cfg - 1;				
		}
		event_read_vgrf_done.notify();
	}

}

void Rcore::writeVGregs()
{
	wait();
	while(true){
		/* wait for these two events */
		wait(event_set_state & even_write_vgrf_cfg);
		
		/**/
		Vector<Uint32> tmp_write_vgrf_cfg;
		
		for(Uint32 idx_cfg = 0; idx_cfg<m_write_vgrf_context_.size();idx_cfg++){
			/* wait for last time execution accomplished */
			assert(flag_pipeline_ >= 0);
			if(flag_pipeline_) 
				wait(flag_execution_done_);
			else{
				/*check whether data config jump happen */\
				if(flag_module_data_cfg_on && flag_data_cfg_jump){
					wait(event_one_data_context_done);
				/* If it is a outside Data Cfg jump, change pointer to write vgrf context */
				//TODO:May be travesing is not the best way to trigger read vgrf
				if(idx_data_cfg_running != idx_next_data_cfg)
					for(Uint32 j=0; j<m_read_vgrf_context_.size(); j++)
						if(m_read_vgrf_context_[j][0] == idx_next_data_cfg)
							idx_cfg = j;
				}	
			}
			/* Read Context */
			Vector<Uint32> cfg_write_vgrf = m_write_vgrf_context_[idx_cfg];
			Vector<RegsData> write_buf;

			assert(cfg_write_vgrf.size() == 8);
			Uint32 idx_data_cfg = cfg_write_vgrf[0];
			Uint32 index_vgrf = cfg_write_vgrf[1];
			Uint32 addr_row_head_w = cfg_write_vgrf[2];
			Uint32 addr_col_head_w = cfg_write_vgrf[3];
			Uint32 mode_w = cfg_write_vgrf[4]; 
			Uint32 row_w = cfg_write_vgrf[5]; 
			Uint32 col_w = cfg_write_vgrf[6];
			Uint32 num_write = cfg_write_vgrf[7];

			/* synchronization with RCA when under none pipeline state */
			if(!flag_pipeline_) {
				while(idx_data_cfg != idx_data_cfg_running) wait();
				/* wait for value change in buffer */
				//for (Uint32 i=0; i<num_write; i++)
				//TODO: When num_write is big, thread stops here.
				//wait((rca_data_out_[num_write-1].value_changed_event()));
				//wait(flag_execution_done_);
			}

			/* Read Data Context of Jump Module 2 */
			Vector<Uint32> module_addr_in = m_rcore_context_.jump_write_vgrf_cfg[idx_cfg].data_in;
			Vector<Uint32> module_addr_out = m_rcore_context_.jump_write_vgrf_cfg[idx_cfg].data_out;
			Vector<Uint32> module_mode = m_rcore_context_.jump_write_vgrf_cfg[idx_cfg].mode;
			Vector<Uint32> jump_info;
			flag_module_w_vgrf_on = (bool)module_mode[2];
			
			if(flag_module_w_vgrf_on){
				jump_info= jump_modular_w_vgrf->ModuleDataCfg(module_addr_in, module_addr_out,module_mode);
			  flag_write_vgrf_jump = (bool)jump_info[0];
			}else
				flag_write_vgrf_jump = false;

			if(flag_module_w_vgrf_on == true){
				if(flag_write_vgrf_jump == true) {
					idx_next_write_vgrf_cfg = jump_info[2];
					Uint32 jump_addr_row_head_mode = ((jump_info[1])>>14)&0x3;
					Uint32 jump_addr_row_head_var = ((jump_info[1])>>8)&0x3f;
					Uint32 jump_addr_col_head_mode = ((jump_info[1])>>6)&0x3;
					Uint32 jump_addr_col_head_var = (jump_info[1])&0x3f;

					switch(jump_addr_row_head_mode)
					{
					case 0: tmp_write_vgrf_cfg = m_write_vgrf_context_[idx_next_write_vgrf_cfg];
									tmp_write_vgrf_cfg[1] = m_write_vgrf_context_[idx_next_write_vgrf_cfg][2] + jump_addr_row_head_var;
									break;
					case 1: m_write_vgrf_context_[idx_next_write_vgrf_cfg][2] += jump_addr_row_head_var;
									tmp_write_vgrf_cfg = m_write_vgrf_context_[idx_next_write_vgrf_cfg];
									break;
					default: assert(0); break;
					}
          
					wait(event_need_write_vgrf);
					flag_need_revert_data_cfg = true;
					event_revert_data_cfg.notify();
					
					#if DEBUG_RCORE_WRITE_VGRF_JUMP
						cout<<"<<<<< Time: "<<sc_time_stamp()<<","
						    <<" Rcore: Write VgrfCfg Jump to VGRFCfg_"<<idx_next_write_vgrf_cfg<<endl;
					#endif
				}else {
					wait(event_need_write_vgrf);
					flag_need_revert_data_cfg = false;
					event_revert_data_cfg.notify();
					
					idx_next_write_vgrf_cfg = idx_cfg + 1;
				}
			}else {
				wait(event_need_write_vgrf);
				flag_need_revert_data_cfg = false;
				event_revert_data_cfg.notify();
				idx_next_write_vgrf_cfg = idx_cfg + 1;
			}
			
			for (Uint32 i=0; i<num_write; i++)
				write_buf.push_back(RcaData(rca_data_out_[i].read()));

			#if DEBUG_RCORE_WRITEVGRF
				cout<<"<<<<< Time: "<<sc_time_stamp()<<",";
				cout<<" Rcore: Write VGRF_"<<index_vgrf<<", Write Data Are: "<<endl;
				Uint32 col_print = 32;
				Uint32 row_print = num_write/32 + ((num_write%32)?1:0);
				for( Uint32 i=0; i<row_print; i++){
					for (Uint32 j=0; j<col_print; j++)
						if((i*col_print+j)<num_write)
							cout<<write_buf[(i*col_print+j)]<<" ";
					cout<<endl;
				}
			#endif 

			cout<<endl;
			port_to_vgregs_[index_vgrf]->blockWrite(addr_row_head_w, addr_col_head_w
																	, mode_w, row_w, col_w, write_buf);
			
			idx_cfg = idx_next_write_vgrf_cfg - 1;	
		}
	}
}

/* This function will be called by TopSys Thread */
void Rcore::runOneContext(RcoreContext rcore_context)
{
	m_rcore_context_ = rcore_context;
	
	flag_pipeline_ = rcore_context.debugInfo_.flag_pipeline;
	event_set_state.notify(SC_ZERO_TIME);

	/* This should be the first step */
	writeRouteCfg(rcore_context.route_context);

	/* only transit all read vgrf context to rcore */
	writeReadVgrfCfg(rcore_context.read_vgrf_context);
	
	/* only transit all write vgrf context to rcore */
	writeWriteVgrfCfg(rcore_context.write_vgrf_context);
		
	if(flag_pipeline_) {
		/* wait for global data until ready */
		wait(route_rca_in);
		/* write all data config until all of these accomplished */
		writeDataCfgGroup(rcore_context.data_context_group.data_context);	
	}
	else {
		if(!(rcore_context.num_data_context)) {
			assert(0);
			//TODO:These codes will be removed later */
		}	else {
			DataSegmentCfg temp_data_config;
			DataSegmentGroup init_data_config = rcore_context.data_context_group;
						
			for (Uint32 i_data_cfg=0;  i_data_cfg<rcore_context.num_data_context;  i_data_cfg++) {
				/* if not jump inside, then wait route rca in */
				idx_data_cfg_running = i_data_cfg;

				bool inside_jump = (flag_data_cfg_jump)&&(idx_data_cfg_running == idx_next_data_cfg);
				if(!inside_jump){
					event_data_cfg_read_global.notify(SC_ZERO_TIME);
					wait(event_data_cfg_can_read);
				}				

				#if DEBUG_DATACFG_RUN
					cout<<endl<<"<<<<< Time: "<<sc_time_stamp()<<","
					    <<" Rcore: Start Run Data Config_"<<i_data_cfg<<endl;
				#endif
			 	writeDataCfg(*init_data_config.data_context[i_data_cfg]);

				#if DEBUG_DATACFG_RUN
					cout<<"<<<<< Time: "<<sc_time_stamp()<<","
					    <<" Rcore: End Run Data Config_"<<i_data_cfg<<endl;
				#endif
								
				/* Function of this word based on jump mode:IA / IB */
				if((flag_data_cfg_jump&flag_module_data_cfg_on) == true)
					*init_data_config.data_context[i_data_cfg] = temp_data_config;
				
				/* Route Config of Jump Module for read VGRF */
				Vector<Uint32> module_data_in = m_rcore_context_.jump_of_data_cfg[i_data_cfg].data_in;
				Vector<Uint32> module_data_out = m_rcore_context_.jump_of_data_cfg[i_data_cfg].data_out;
				Vector<Uint32> module_mode = m_rcore_context_.jump_of_data_cfg[i_data_cfg].mode;
				/* Config of Module2 */
				Vector<Uint32> jump_info;
				flag_module_data_cfg_on = (bool)module_mode[2];

				if(flag_module_data_cfg_on){
					jump_info = rca_->jump_modular_data_cfg->ModuleDataCfg(module_data_in, module_data_out,module_mode);
					flag_data_cfg_jump = (bool)jump_info[0];
				}else
					flag_data_cfg_jump = false;

				assert(module_mode[2] <= 1);
				assert(jump_info[0] <= 1);
		
				if(flag_module_data_cfg_on == true) {
					if(flag_data_cfg_jump == true) {
							/* if there is a jump back */
							idx_next_data_cfg = jump_info[2];
							Uint32 jump_mode = ((jump_info[1])>>6)&0x3;
							Uint32 jump_addr_var = (jump_info[1])&0x3f;

							DataSegmentCfg * next_data_cfg;
							next_data_cfg = init_data_config.data_context[idx_next_data_cfg];
							switch(jump_mode)
							{
							case 0: temp_data_config = *next_data_cfg;
											/* Update Data Addr or Indirect Addr, Leave Imm Alone */
											for(Uint32 i=0; i<temp_data_config.addr_data_in.size(); i++)
												for(Uint32 j=0; j<temp_data_config.addr_data_in[i].size(); j++)	{
													Uint32 addr = temp_data_config.addr_data_in[i][j];
													if(((addr>>(HEAD_MODE_BIT-1))&0x3) != 0x2)
														temp_data_config.addr_data_in[i][j] += jump_addr_var;
												}
											for(Uint32 i=0; i<temp_data_config.addr_data_out.size(); i++)
												for(Uint32 j=0; j<temp_data_config.addr_data_out[i].size(); j++)	
													temp_data_config.addr_data_out[i][j] += jump_addr_var;											
											break;
							case 1: for(Uint32 i=0; i<next_data_cfg->addr_data_in.size(); i++)
												for(Uint32 j=0; j<next_data_cfg->addr_data_in[i].size(); j++){	
													Uint32 addr = next_data_cfg->addr_data_in[i][j];
													if(((addr>>(HEAD_MODE_BIT-1))&0x3) != 0x2)
														next_data_cfg->addr_data_in[i][j] += jump_addr_var;		
												}
											for(Uint32 i=0; i<next_data_cfg->addr_data_out.size(); i++)
												for(Uint32 j=0; j<next_data_cfg->addr_data_out[i].size(); j++)
													next_data_cfg->addr_data_out[i][j] += jump_addr_var;
											temp_data_config = *next_data_cfg;
											break;
								}
								#if DEBUG_RCORE_DATA_CFG_JUMP
									cout<<"<<<<< Time: "<<sc_time_stamp()<<","
									    <<" Rcore: Data Config Jump to DataCfg_"<<idx_next_data_cfg<<endl;
								#endif
						}else{
								/* when no inside jump, check outside jump. */
								event_need_read_vgrf.notify(SC_ZERO_TIME);
								event_need_write_vgrf.notify(SC_ZERO_TIME);
								wait(event_revert_data_cfg);

								if(flag_need_revert_data_cfg == true) {
									*init_data_config.data_context[idx_next_data_cfg] 
										= *rcore_context.data_context_group.data_context[idx_next_data_cfg];
            
									//TODO: it need a clear opertion on sgrf, but used in an unproper way.
									Uint32 jump_module_in_addr = ((rcore_context.jump_of_data_cfg[i_data_cfg].data_in[0])
										                             & ((0x1<<(HEAD_GLOBAL_ADDR_BIT+1))-1) );
									rca_->sgregs_[0]->write(jump_module_in_addr,0);
									//init_data_config.data_context[idx_next_data_cfg]->jump_module2_data_cfg[0][2] += var;
									#if DEBUG_DATACFG_RUN
										cout<<"<<<<< Time: "<<sc_time_stamp()<<","
												<<" Rcore: Inside Loop End, Start A New Outside Loop"<<i_data_cfg<<endl;
									#endif
								}
								else
									idx_next_data_cfg = i_data_cfg + 1;

								//if(flag_need_revert_data_cfg && flag_)
									//idx_next_data_cfg = i_data_cfg + 1;
						}
					}else{
					  event_need_read_vgrf.notify(SC_ZERO_TIME);
						event_need_write_vgrf.notify(SC_ZERO_TIME);
						wait(event_revert_data_cfg);
						idx_next_data_cfg = i_data_cfg + 1;
					}
				
				while( !flag_execution_done_ ) wait();
								
				event_one_data_context_done.notify();
				/* note:if idx_next_data_cfg=0,then now i_data_cfg=-1,++i_data_cfg=0 */
				i_data_cfg = idx_next_data_cfg - 1;
				//while(!rca_->isAllRcWriteRfDone()) wait();			
				//rca_->clearFlag();
			}
		}
	}
		
	
	return;
}


void Rcore::printSGRF(Uint32 *data)
{
	//Uint32 temp[256];
	Uint32 *p = data;
	rca_->sgregs_[0]->multiRead(p,0,256);
	cout<<"Value In SGRF:"<<endl;
	for(Uint32 i=0; i<32; i++){
		for(Uint32 j=0; j<8; j++)
			cout<<*(p++)<<" ";
		cout<<endl;
	}
}