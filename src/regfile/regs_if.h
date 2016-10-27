/**********************************************************************************
-----------------------------------------------------------------------------------
    @file:regs_if.h
    @author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @version 1.0, 2010-01-21, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file contains class definitions of register read/write interfaces.
-----------------------------------------------------------------------------------
**********************************************************************************/

#ifndef _DREGS_IF_H
	#define _DREGS_IF_H

#include <systemc.h>
#include "../tools/system_def.h"

//enum transfer_status { TRANSFER_OK = 0, TRANSFER_ERROR };

class regs_reset_if
{
public:
	virtual bool reset(void) = 0;
};

template <class T>											
class regs_read_port_if				
{																
public:														
	virtual bool read(Uint32 addr, T& data) = 0;	
};	

template <class T>											
class regs_write_port_if			
{																
public:														
	virtual bool write(Uint32 addr, T data) = 0;	
};	

template <class T>											
class regs_multiread_port_if				
{																
public:															
	virtual bool multiRead(T* const data, Uint32 addr, Uint32 num) = 0;
};	

template <class T>											
class regs_multiwrite_port_if			
{																
public:														
	virtual bool multiWrite(Vector<T> data, Uint32 addr, Uint32 num) = 0;	
};	

template <class T>											
class regs_blockread_port_if			
{																
public:														
	virtual bool blockRead(Uint32 addr_row_head,Uint32 addr_col_head
								, Uint32 mode,Uint32 row,Uint32 col, Vector<T> *data)  = 0;	
};	

template <class T>											
class regs_blockwrite_port_if			
{																
public:														
	virtual bool blockWrite(Uint32 addr_row_head,Uint32 addr_col_head
								, Uint32 mode,Uint32 row,Uint32 col, Vector<T> data)  = 0;	
};	


/* sc_interface for reading/writing distributed Register File */
template <class T>											
class dregs_if: public sc_interface					
			   ,public regs_read_port_if<T>
			   ,public regs_write_port_if<T>
			   ,public regs_reset_if
{																		
};

/* sc_interface for reading/writing global Register File */
template <class T>											
class sgregs_if: public sc_interface
			   ,public regs_multiread_port_if<T>
			   ,public regs_write_port_if<T>
			   ,public regs_reset_if
{																		
};

template <class T>											
class vgregs_if: public sc_interface
			   ,public regs_multiread_port_if<T>
			   ,public regs_multiwrite_port_if<T>
			   ,public regs_blockread_port_if<T>
			   ,public regs_blockwrite_port_if<T>
			   ,public regs_reset_if
{																		
};

#endif
