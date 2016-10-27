/*****************************************************************************
  rca_config.h

  Original Author: Zhang Jixin, CNASIC, 2010-12-9
 *****************************************************************************/

#ifndef RCA_CONFIG_H_
#define RCA_CONFIG_H_


#include "../tools/system_def.h"
#include "../parameter/parameter_arch.h"
#include "config_rc.h"
#include "config_mux.h"


// ----------------------------------------------------------------------------
//  CONFIG of module 'Rca'
// ----------------------------------------------------------------------------

// config value of rc->inroute_config
#define NUM_LOCAL 4
#define LOCAL(i)    i
#define GLOBAL(i)    LOCAL(0) + i
// config value of output_mux->m_config_
#define RC_OUTPUT(i,j,m)    i*NUM_RC_COL*NUM_ALU_OUTPUT+j*NUM_ALU_OUTPUT+m

using namespace RcoreParameter;

struct RcaConfigPacket
{
  MuxConfig output_mux_config[NUM_RCA_OUTPORT];
  RcConfigPacket rc_config_packet[NUM_RC_ROW][NUM_RC_COL];

  RcaConfigPacket()
  {
    for (Uint32 i=0; i<NUM_RCA_OUTPORT; i++)
      output_mux_config[i] = MUX_DEFAULT;
  }
};



#endif

