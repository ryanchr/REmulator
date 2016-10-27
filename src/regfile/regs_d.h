/**********************************************************************************
-----------------------------------------------------------------------------------
    @file:regs_d.h
    @author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @version 1.0, 2010-01-21, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file contains class definition of distributed register file.
-----------------------------------------------------------------------------------
**********************************************************************************/

#ifndef DREGS_H
	#define DREGS_H

#include <systemc.h>
#include "regs_if.h"
#include "../tools/system_def.h"

template <class T>
class Dregs: public dregs_if<T>,
			 public sc_module
{
public:
	/* sc_channel for limiting simultaneously read/write ports */
	sc_semaphore protect_write_;			
	sc_semaphore protect_read_;

	SC_HAS_PROCESS(Dregs);
	Dregs(sc_module_name name, Uint32 size, Uint32 num_readport, Uint32 num_writeport)
		:sc_module(name)
		,name_(String(name))
	  ,size_dregs_(size)				 //size of DRF
		,protect_read_(num_readport)      //num of readports
		,protect_write_(num_writeport)	 //num of writeports	
	{
		/* data initialization of regfile */
		sc_assert(size>0);
		regfile_ = new T [size];
		if(regfile_){
			for(Uint32 i=0;i<size;i++) { 
				regfile_[i]=0;   
			}
		}
	}

	~Dregs(){
		if(regfile_) { 
			delete[] regfile_; 
			regfile_ = NULL; }
	}	
	
private:
	T *regfile_;
	Uint32 size_dregs_;
	String name_;

public:	
	bool reset(void);

	bool read(Uint32 addr, T& data);
	bool write(Uint32 addr, T data);
};

template<class T> 
bool Dregs<T>::reset(void) 
{ 
	if(regfile_){
	for(Uint32 i=0;i<size_dregs_;i++) { 
		regfile_[i] = 0; 	
	}
	return true; 
	}
	return false;
}

template<class T> 
bool Dregs<T>::read(Uint32 addr, T& data) 
{ 
	sc_assert(addr>=0); 
	sc_assert(regfile_!=0);

	protect_read_.wait(); 
	data = regfile_[addr];
  cout<<"<<<<< Time: "<<sc_time_stamp()<<", ";
	cout<<"Read "<<name_<<": "
		   <<"Addr = "<<addr<<", Value = "<<data<<endl;
	wait();	
	protect_read_.post(); 

	return 1; 
} 

template<class T> 
bool Dregs<T>::write(Uint32 addr, T data) 
{ 
  sc_assert(addr>=0); 
	sc_assert(regfile_!=0);

	protect_write_.wait();
	regfile_[addr] = data; 

	cout<<"<<<<< Time: "<<sc_time_stamp()<<", ";
	cout<<"Write "<<name_<<": "
		   <<"Addr = "<<addr<<", Value = "<<data<<endl;
	
	wait();								
	protect_write_.post(); 

	return 1; 
} 

#endif