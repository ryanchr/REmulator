/**********************************************************************************
-----------------------------------------------------------------------------------
    @File:    config_rcore.h
    @Author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @Version: 1.0, 
    @Time:    2011-02-17, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file mainly implements struct definition of rcore configuration data.
-----------------------------------------------------------------------------------
**********************************************************************************/
#ifndef RCORE_CONFIG_H_
#define RCORE_CONFIG_H_

#include "../tools/system_def.h"
#include "../parameter/parameter_arch.h"
#include "config_rca.h"

// ----------------------------------------------------------------------------
//  Debug Information of RCA's Global Data    //used for print information
// ----------------------------------------------------------------------------
struct GlobalDebugInfoPacket
{
	bool flag_pipeline;
  Uint32 num_global_data_in_;
  Vector<String> name_global_data_in_;
  Vector<Uint32>  indices_global_port_in;
  Uint32 num_global_data_out_;
  Vector<String> name_global_data_out_;

  GlobalDebugInfoPacket()
		: num_global_data_in_ (0)
		, num_global_data_out_ (0) 
		, flag_pipeline(0) {}

  GlobalDebugInfoPacket(Uint32 n_read_data, Uint32 n_write_data, bool flag)
		:num_global_data_in_(n_read_data)
		,num_global_data_out_(n_write_data)
		,flag_pipeline(flag){}

};

// ----------------------------------------------------------------------------
//  Config of Computing Context
// ----------------------------------------------------------------------------

struct RouteSegmentCfg
{
  //RcaConfigPacket rca_config_packet;
  Vector<Vector<Uint32> > data_source_, data_des_;
  Vector<Vector<Uint32> > op_rc_;
	
  RouteSegmentCfg() {}
};

// ----------------------------------------------------------------------------
//  Config of Data Context
// ----------------------------------------------------------------------------

struct DataSegmentCfg
{
  Vector<Vector<Uint32> > addr_data_in,addr_data_out;
  
  DataSegmentCfg() {}
};
// ----------------------------------------------------------------------------
//  Config of Context
// ----------------------------------------------------------------------------

struct DataSegmentGroup
{
	Vector<DataSegmentCfg*> data_context;

	DataSegmentGroup(){}
	DataSegmentGroup(const DataSegmentGroup & data_seg_group);
	DataSegmentGroup & operator =(const DataSegmentGroup & data_seg_group);
	
	void creatDataContext(Uint32 num){
		data_context.clear();
    for(Uint32 i = 0; i<num; i++){
      DataSegmentCfg *temp = new DataSegmentCfg();
      data_context.push_back(temp);
    }
  }

	~DataSegmentGroup()
	{ 
		for(Uint32 i = 0; i<data_context.size(); i++){
      DataSegmentCfg *temp = data_context[i];
      if(temp) {
				delete temp;
				temp = NULL;
      }
    }
	}
};

struct ReadVgrfCfg
{
	Uint32 addr_row_head_r,addr_col_head_r, mode_r,row_r,col_r;

	ReadVgrfCfg() :addr_row_head_r(0),addr_col_head_r(0), mode_r(0),row_r(0),col_r(0) {}
};

struct WriteVgrfCfg
{
	Uint32 addr_row_head_w,addr_col_head_w, mode_w,row_w,col_w;

	WriteVgrfCfg() :addr_row_head_w(0),addr_col_head_w(0), mode_w(0),row_w(0),col_w(0) {}
};

struct JumpModularDataCfg
{
  Vector<Uint32> data_in,data_out,mode;
};

struct RcoreContext
{
  Uint32 num_data_context;
	GlobalDebugInfoPacket debugInfo_;
  RouteSegmentCfg route_context;
  DataSegmentGroup data_context_group;
	/* Contexts include all vgrf contexts in each data context */
	Vector<Vector<Uint32> >  read_vgrf_context;    
	Vector<Vector<Uint32> >  write_vgrf_context; 
	/* Contexts include all jump contexts in each data context */
	Vector<JumpModularDataCfg> jump_of_data_cfg;
	Vector<JumpModularDataCfg> jump_read_vgrf_cfg;
	Vector<JumpModularDataCfg> jump_write_vgrf_cfg;
	
  RcoreContext()
		:num_data_context(0) {	}
};



#endif
