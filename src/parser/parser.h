/*
*  parser.h
*
*  ContextParser definition
*
*  Copyright (C) 2011  Chen Ren
*
*  2011-07-01 15:35:11 Created.
*
*  Description: The ContextParser parser_ the module through the cfgfile. 
*/

#ifndef ME_INITIALIZER_H
#define ME_INITIALIZER_H

#include <iostream>
#include <string>
#include "../config/config_rcore.h"
#include "../tools/system_def.h"
#include "../matengine/matengine.h"

using namespace RcoreParameter;

class ContextParser
{
public:	

	ContextParser();

	Uint8 *initialOfMatInput();

	void initialOfMatOutput(Uint32 output[]);
	
	void setNumOfContext(Uint32 num);

	void setFlagPipeline(Uint32 num, Uint32 index);
	
	void setNumOfGlobalIn(Uint32 num, Uint32 index);
	
	void setNumOfGlobalOut(Uint32 num, Uint32 index);
	
	void setIndexOfGlobalPort( Uint32 size, Vector<Uint32> vec_int, Uint32 index);
	
	void setNameOfGlobalIn( Uint32 size, Vector<String> vec_string, Uint32 index);
	
	void setNameOfGlobalOut( Uint32 size, Vector<String> vec_string, Uint32 index);
	
	void setDataSource( Uint32 size, Vector<String> vec_string, Uint32 index );
	
	void setOpcode( Uint32 size, Vector<String> vec_string, Uint32 index );
	
	void setDataDes( Uint32 size, Vector<String> vec_sring, Uint32 index );

  void setDataCfgNum(Uint32 num, Uint32 index);

  void setDataAddrIn(Uint32 size, Uint32 loopindex, Uint32 cfgindex, Vector<Uint32> vec_int);

  void setDataAddrOut(Uint32 size, Uint32 loopindex, Uint32 cfgindex, Vector<Uint32> vec_int);
  	
	void setReadVgrfCfg(Uint32 idx_data_cfg, Uint32 size, Uint32 cfgindex, Vector<Uint32> vec_int);
	
	void setWriteVgrfCfg(Uint32 idx_data_cfg, Uint32 size, Uint32 cfgindex, Vector<Uint32> vec_int);

	void setJumpDataIn(Uint32 size, Uint32 idx_data_cfg, Uint32 idx_cfg, Vector<Uint32> vec_int, Uint32 idx_jump_modular);

	void setJumpDataOut(Uint32 size, Uint32 idx_data_cfg, Uint32 idx_cfg, Vector<Uint32> vec_int, Uint32 idx_jump_modular);

	void setJumpMode(Uint32 size, Uint32 idx_data_cfg, Uint32 idx_cfg, Vector<Uint32> vec_int, Uint32 idx_jump_modular);
	
  Vector<RcoreContext> getRcoreContext(void);

	void readDataInputTxt(Vector<Uint32> vec_int);
	Vector<Uint32> returnDataInputTxt(void) const;

	~ContextParser() 
	{
		if(mat_engine)
			delete mat_engine;
	}

private:
	Vector<RcoreContext> init_rcore_context_;
	Uint32 num_context_;
 
  Map<String,AluOpConfig> op_map_;
  Map<String, Uint32> rc_input_map_;
  Map<String, RcDesCfg> rc_output_map_;
	RcInputCfg<NUM_LINK_RC> rc_input_cfg;

	MatEngine *mat_engine;
	Vector<Uint32> data_txt_in;
};

#endif
