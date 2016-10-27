/*****************************************************************************
  mux.h

  Original Author: Zhang Jixin, CNASIC, 2010-12-9
 *****************************************************************************/

#ifndef MUX_H_
#define MUX_H_

#include "../tools/system_def.h"
#include "../parameter/parameter_arch.h"
#include "../config/config_mux.h"
#include <systemc.h>

using RcoreParameter::RcaData;

// ----------------------------------------------------------------------------
//  SC_MODULE : Mux<num_inport>
// ----------------------------------------------------------------------------

template <Uint32 num_inport>
class Mux
  : public sc_module
{
public:
	sc_in<RcaData> data_in_[num_inport];
	sc_out<RcaData> data_out_;

private:
	sc_signal<MuxConfig> m_config_;
	sc_event event_write_config_;

public:
	void route();
	void configure(MuxConfig config);
  
	SC_HAS_PROCESS(Mux);
	Mux(sc_module_name name)
	  : sc_module(name)
	  , name_(std::string(name))
	{
		SC_METHOD(route);
		for (Uint32 i=0; i<num_inport; i++)
		  sensitive << data_in_[i];
		//sensitive << event_write_config_;

		m_config_ = MUX_DEFAULT;
	}

private:
	String name_;
};

#define prefix_def3  template <Uint32 num_inport>  \
								inline void Mux<num_inport>

prefix_def3::configure(MuxConfig config)
{
	m_config_ = config;
	//event_write_config_.notify(SC_ZERO_TIME);
}

prefix_def3::route()
{
	if(m_config_ != MUX_DEFAULT){
		int data_out = data_in_[m_config_].read();
		data_out_.write(data_out); 
	#if DEBUG_MUX
		cout<<"<<<<< Time: "<<sc_time_stamp()<<","
			  <<" "<<name_
			  <<": Write Global Data, RCIndex = "<<m_config_.read()<<", Value = "<<data_out<<endl;
	#endif
	}
}

#undef prefix_def3

#endif
