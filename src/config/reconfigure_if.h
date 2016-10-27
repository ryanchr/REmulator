/**********************************************************************************
-----------------------------------------------------------------------------------
    @File:    reconfigure_if.h
    @Author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @Version: 1.0, 
    @Time:    2010-01-21, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file mainly implements the reconfigure interface.
-----------------------------------------------------------------------------------
**********************************************************************************/

#ifndef RECONFIGURE_IF_H_
#define RECONFIGURE_IF_H_

#include <systemc.h>
#include "../tools/system_def.h"
#include "../parameter/parameter_arch.h"
#include "config_rcore.h"


#if 0
class ReconfigureIf
  : virtual public sc_interface
{
public:
  virtual void writeRouteCfg(RouteSegmentCfg route_context) = 0;
  virtual void writeDataCfg(DataSegmentCfg data_context) = 0;
  //virtual void write_rca_config(RcaConfigPacket & config_packet) = 0;
  //virtual void write_data_config(DataConfigPacket & config_packet) = 0;
};
#endif

#endif
