/**********************************************************************************
-----------------------------------------------------------------------------------
    @file:regs_sg.h
    @author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @version 1.0, 2010-01-21, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file contains class definition of scalable global register file.
-----------------------------------------------------------------------------------
**********************************************************************************/


#ifndef SGREGS_H
	#define SGREGS_H

#include <systemc.h>
#include "regs_if.h"
#include "../tools/system_def.h"

template <class T> 
class SGRegs
: public sgregs_if<T>
, public sc_module
{
public:
	/* sc_channel for limiting simultaneously read/write ports */
	sc_semaphore protect_write_;
	sc_semaphore protect_read_;

	SC_HAS_PROCESS(SGRegs);
	SGRegs(sc_module_name name
		, Uint32 size
		, Uint32 num_readport
		, Uint32 num_writeport)
		:sc_module(name)
		,name_(String(name))
	    ,size_sgregs_(size)									//size of SGRF
		,protect_read_(num_readport)				//num of readports
		,protect_write_(num_writeport)				//num of writeports						
	{
		/* data initialization of regfile_ */
		sc_assert(size>0);
		regfile_ = new T [size];
		if(regfile_){
			for(Uint32 i=0;i<256;i++) { 
				regfile_[i]=5; 
			}
			for(Uint32 i=256;i<size;i++) { 
				regfile_[i]=0; 
			}
		}
	}

	~SGRegs(){
		if(regfile_) { 
			delete[] regfile_; 
			regfile_ = NULL; 
		}
	}	
	
private:
	T *regfile_;//T *regfile_;
	Uint32 size_sgregs_;
	String name_;

public:	
	bool reset(void);
	bool multiRead(T* const data, Uint32 addr, Uint32 num);
	bool write(Uint32 addr, T data);
	void print(std::ostream &out);
};

template<class T> 
bool SGRegs<T>::reset(void) 
{ 
	if(regfile_){
		for(Uint32 i=0;i<size_sgregs_;i++) { 
			regfile_[i]=0; 	
		}
		return true; 
	}
	return false;
}

template<class T> 
bool SGRegs<T>::multiRead( T* const data, Uint32 addr, Uint32 num)
{ 
	sc_assert(addr>=0); 
	sc_assert(regfile_!=0);
	
	protect_read_.wait(); 
	
	T *readdata = data;
	for(Uint32 i=0; i<num; i++){
		
		*(readdata++) = regfile_[addr+i];
		
		#if DEBUG_READ_SGRF
			cout<<"<<<<< Time: "<<sc_time_stamp()<<", ";
			cout<<"Read "<<name_<<": "
				   <<"Addr = "<<addr+i<<", Value = "<<regfile_[addr+i]<<endl;
		#endif
		
	}
	
	wait();
	
	protect_read_.post(); 

	return 1; 
} 

template<class T> 
bool SGRegs<T>::write(Uint32 addr, T data) 
{ 
	 sc_assert(addr>=0); 
	 sc_assert(regfile_!=0);

	 protect_write_.wait();	 
	 regfile_[addr] = data; 
	 
	 #if DEBUG_WRITE_SGRF
	 cout<<"<<<<< Time: "<<sc_time_stamp()<<", ";
	 cout<<"Write "<<name_<<": "
			    <<"Addr = "<<addr<<", Value = "<<data<<endl;
	 #endif
	 
	 wait();
	 protect_write_.post(); 

	 return 1; 
} 

template<class T> 
void SGRegs<T>::print(std::ostream &out)
{
	Uint32 row = size_sgregs_/4 + ((size_sgregs_%4)?1:0);
	Uint32 col = 4, num = 0;

	out<<"----print data in VGRF----"<<endl;
	for (Uint32 i=0; i<row; i++) {
		for(Uint32 j=0; j<col; j++) {
			if(num < size_vgregs_){
	   		out<<"address: "<<num<<" value: "<<regfile_[num]<<"\t\t";
			}
		 num++;		
		}
		out<<endl;
	}
}
#endif
