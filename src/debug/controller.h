/**********************************************************************************
-----------------------------------------------------------------------------------
    @File:    controller.h
    @Author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @Version: 1.0, 
    @Time:    2010-01-21, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file mainly implements class definition of system controller module.
-----------------------------------------------------------------------------------
**********************************************************************************/

#ifndef _CONTROLLER_H
	#define _CONTROLLER_H

#include<systemc.h>

/*
class controller:
	public sc_module
{
public:
	sc_clk_in clk_in_;
	void mainAction();
	void readconfig();
	void writeconfig();

	SC_HAS_PROCESS(mainAction);
	controller(sc_module_name name_)
		:sc_module(name_)
	{
		SC_THREAD(mainAction);
		sensitive<<clk_in_;
	}

private:


};


void controller::readconfig()
{


}

void controller::writeconfig()
{


}
*/
#endif