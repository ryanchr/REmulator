/**********************************************************************************
-----------------------------------------------------------------------------------
    @File:    engine.h
    @Author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @Version: 2.0, 
    @Time:    2011-07-16, 14:21
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file mainly implements the interface with matlab.
-----------------------------------------------------------------------------------
**********************************************************************************/
#ifndef ENGINE_H_
#define ENGINE_H_

#include <systemc.h>
#include "../tools/system_def.h"
#include "../parameter/parameter_arch.h"

#if DEBUG_ENABLE_MAT_ENGINE
  #include "engine.h"
#endif

using namespace RcoreParameter;


class MatEngine
	: public sc_module
{
public:
	//sc_in_clk  clk_in_;

	void inputEngine();

	void outputEngine(Uint32 *output);

	Uint8 *returnDataPr() const;

	void MainAction();

	String returnName(void) const;
		
	MatEngine(sc_module_name name)
		:sc_module(name)
		,name_(name)
	{
		input_data_ = (Uint8 *)malloc(400*600*sizeof(Uint8));
	}
		
	~MatEngine()
	{	
		free(input_data_);
	}
	
	private:
		String name_;
		Uint8 *input_data_;
};


#endif


