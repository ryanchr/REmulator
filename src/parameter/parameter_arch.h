/*****************************************************************************
  parameter_arch.h

  Original Author: Zhang Jixin, CNASIC, 2010-12-16
 *****************************************************************************/
#include "../tools/system_def.h"
#include <systemc.h>

#ifndef ARCH_PARAMETER_H_
#define ARCH_PARAMETER_H_

namespace RcoreParameter
{
	const Uint32 NUM_ALU_INPUT = 2;
	const Uint32 NUM_ALU_OUTPUT = 1;
  /* data parameters of rca */
  const Uint32 WIDTH_RCA_DATA = 32;
  typedef Uint32 RcaData; 
  typedef Uint32 RegsData;

  /* size parameters of RCA */
  const Uint32 NUM_RCA_INPORT = 64;
  const Uint32 NUM_RCA_OUTPORT = 64;
  const Uint32 NUM_RC_ROW = 4;
  const Uint32 NUM_RC_COL = 4;
  const Uint32 NUM_PORT_TO_VGRF = 1;
	const Uint32 WIDTH_RCA_ADDR = 16;    //corresponding with addr in data segment

  /* architecture parameters of DRF */
  const Uint32 NUM_DREGS = 4;
  const Uint32 SIZE_DREGS = 32;
  const Uint32 NUM_READPORT_DREGS = 3;
  const Uint32 NUM_WRITEPORT_DREGS = 1;
  typedef Uint32 DATA_WIDTH_DRF;

  /* architecture parameters of SGRF */
  const Uint32 NUM_SGREGS = 1;
  const Uint32 SIZE_SGREGS = NUM_RC_ROW*NUM_RC_COL*(0x1<<7);       
  const Uint32 NUM_READPORT_SGREGS = NUM_RC_ROW*NUM_RC_COL*2;
  const Uint32 NUM_WRITEPORT_SGREGS = NUM_RC_ROW*NUM_RC_COL*2;
  typedef Uint32 DATA_WIDTH_SGRF;
  
  /* parameters of mux in rca */
  const Uint32 NUM_OUTPUT_MUX_INPORT = NUM_RC_ROW*NUM_RC_COL*NUM_ALU_OUTPUT;

  /* parameters of rc in rca */
  const Uint32 NUM_PORT_TO_DRF = 3;
  const Uint32 NUM_PORT_TO_SGRF = 1; 

  /**/
  const Uint32 NUM_LINK_RC =  NUM_RC_COL;

}

namespace TopSysParameter
{
  const Uint32 NUM_RCORE = 1;
  const Uint32 NUM_VGRF = 1;   

	using RcoreParameter::NUM_RC_ROW;
	using RcoreParameter::NUM_RC_COL;
  /* architecture parameters of VGRF */
  const Uint32 SIZE_VGREGS = 32*10000;//NUM_RC_ROW*NUM_RC_COL*32;       
  const Uint32 NUM_READPORT_VGREGS = NUM_RC_COL*2 + (NUM_RC_ROW - 1)*2;
  const Uint32 NUM_WRITEPORT_VGREGS = NUM_RC_COL*2 + (NUM_RC_ROW - 1)*2;
  typedef Uint32 DATA_WIDTH_VGRF; 
}

	/* Debug Macro for Thread One On One */
	#define DEBUG_RC_EXECUTE 0
	#define DEBUG_RC_ROUTERCIN 0
	#define DEBUG_RC_ROUTEGLOBALIN 0
	#define	DEBUG_RC_DATACFG 0

	/* Debug Macro for RCore */
	#define DEBUG_RCORE_WRITECFG 0
	#define DEBUG_RCORE_ROUTERCAIN 0
	#define DEBUG_RCORE_ISRCAEXECUTEDONE 0

	#define DEBUG_RCORE_RUNONECONTEXT 0

	#define DEBUG_RCORE_JUMP_MODULAR 0	
	#define DEBUG_RCORE_READ_VGRF_JUMP 0
	#define DEBUG_RCORE_WRITE_VGRF_JUMP 0
	#define DEBUG_RCORE_DATA_CFG_JUMP 0

	#define	DEBUG_DATACFG_RUN 0
	#define DEBUG_RCORE_ROUTE_CONFIG 0
    
	#define DEBUG_DATA_FROM_RF_DIRECT 0
	#define DEBUG_RCORE_READVGRF 1
	#define DEBUG_RCORE_WRITEVGRF 1
	#define DEBUG_READ_SGRF 0
	#define DEBUG_WRITE_SGRF 0
    #define DEBUG_READ_GLOBAL 0
    #define DEBUG_WRITE_GLOBAL 0
	#define DEBUG_MUX 0
	/* Debug Macro for RCA */
	#define DEBUG_RCA_ROUTE_CFG 0
	#define DEBUG_RCA_DATA_CFG 0
	/* Debug Macro for Config Initilizer */
	#define DEBUG_CFG_PARSE 0
  /* Debug Macro for Print Value in VGRF */
	#define DEBUG_PRINT_VGRF 0
	
	#define DEBUG_ENABLE_MAT_ENGINE 1
	#define DEBUG_USE_MAT_INPUT 1
	#define DEBUG_USE_MAT_OUTPUT 1
	#define DEBUG_USE_TXT_INPUT 0
  /* Debug Macro for Flex&Bison,Skip Other Actions. */
	#define DEBUG_ONLY_PARSE 1
	#define DEBUG_YACC 1

  #define TIME_CFG_RC 1
	
#endif
