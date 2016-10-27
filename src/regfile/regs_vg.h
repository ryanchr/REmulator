/**********************************************************************************
-----------------------------------------------------------------------------------
    @file:system_def.h
    @author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @version 1.0, 2010-01-21, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file contains class definition of vector global register file.
-----------------------------------------------------------------------------------
**********************************************************************************/


#ifndef VGREGS_H
	#define VGREGS_H

#include <systemc.h>
#include "regs_if.h"
#include "../tools/system_def.h"


#define WIDTH_VGRF_ROW 32

template <class T>
class VGregs: public vgregs_if<T>
							  ,public sc_module
{
public:
	/* sc_channel for limiting simultaneously read/write ports */
	sc_semaphore protect_write_;
	sc_semaphore protect_read_;

	SC_HAS_PROCESS(VGregs);
	VGregs(sc_module_name name
		, Uint32 size
		, Uint32 readport_num
		, Uint32 writeport_num)
		:sc_module(name)
		,name_(String(name))
	  ,size_vgregs_(size)
		,protect_read_(readport_num)
		,protect_write_(writeport_num)
	{
		sc_assert(size>0);
		regfile_ = new T [size];//T[size];
		if(regfile_){
			for(Uint32 i=0;i<size;i++) { 
				regfile_[i]=0; 
			}
		}
	}

	~VGregs(){
		if(regfile_) { 
			delete[] regfile_; 
			regfile_ = NULL; 
		}
	}	
	
private:
	T *regfile_;//T *regfile_;
	Uint32 size_vgregs_;
	String name_;

public:	
	bool reset(void);
	
	bool multiRead(T* const data, Uint32 addr, Uint32 num);
	
	bool multiWrite(Vector<T> data, Uint32 addr, Uint32 num);
	
	bool blockRead(Uint32 addr_row_head,Uint32 addr_col_head
								, Uint32 mode,Uint32 row,Uint32 col, Vector<T> * data);

	bool blockWrite(Uint32 addr_row_head,Uint32 addr_col_head
								, Uint32 mode,Uint32 row,Uint32 col, Vector<T> data);
	
	void initialize(Uint8 * addr_input, Uint32 size_input);
	void initialize(Uint32 * addr_input, Uint32 size_input);
	
	void print(std::ostream &out);
};

template<class T> 
bool VGregs<T>::reset(void) 
{ 
	if(regfile_){
		for(Uint32 i=0;i<size_vgregs_;i++) { 
			regfile_[i]=0; 	
		}
		return true; 
	}
	return false;
}

template<class T> 
bool VGregs<T>::multiRead(T* const data, Uint32 addr, Uint32 num)
{ 
	sc_assert(addr>=0); 
	sc_assert(regfile_!=0);

	protect_read_.wait(); 
	T *readdata = data;
#if 0
	cout<<"---------- ";
  cout<<"Time: "<<sc_time_stamp();
  cout<<" ----------"<<endl;
  cout<<"*Event: read '"<<name_<<"'"<<endl;
#endif		
	for(Uint32 i=0; i<num; i++){
		*(readdata++) = regfile_[addr+i];
		#if 0
	    cout<<"address: "<<addr+i;
	    cout<<"\t"<<"read value: "<<regfile_[addr+i]<<endl;
		#endif	
	}
	wait();
	protect_read_.post(); 

	return true; 
} 

template<class T> 
bool VGregs<T>::multiWrite(Vector<T> data, Uint32 addr, Uint32 num)
{ 
	assert(addr>=0); 
	assert(regfile_!=0);

	protect_write_.wait(); 
	Uint32 size_data = data.size();
	cout<<"---------- ";
  cout<<"Time: "<<sc_time_stamp();
  cout<<" ----------"<<endl;
  cout<<"*Event: write '"<<name_<<"'"<<endl;
		
	for(Uint32 i=0; i<size_data; i++){
		regfile_[addr+i] = data[i];
	  cout<<"address: "<<addr+i;
	  cout<<"\t"<<"write value: "<<regfile_[addr+i]<<endl;
	}
	wait();
	protect_read_.post(); 

	return true; 
} 

template<class T> 
bool VGregs<T>::blockRead(Uint32 addr_row_head,Uint32 addr_col_head
								, Uint32 mode,Uint32 row,Uint32 col, Vector<T> *data)
{
		protect_read_.wait();
		Uint32 addr_start = ((addr_row_head*WIDTH_VGRF_ROW) + addr_col_head);
		Uint32 addr_read = addr_start;
		switch(mode)
		{
			case 0: for(Uint32 i=0; i<row; i++){
								for(Uint32 j=0; j<col; j++)
									(*data).push_back(regfile_[addr_read++]);
								addr_start += WIDTH_VGRF_ROW;
								addr_read = addr_start;
								assert(addr_read < size_vgregs_);
							} 
							break;
			case 1: for(Uint32 i=0; i<row; i++){
								for(Uint32 j=0; j<col; j++)
									(*data).push_back(regfile_[addr_read++]);
								addr_start += 2*WIDTH_VGRF_ROW;
								addr_read = addr_start;
								assert(addr_read < size_vgregs_);
							} 
							break;
			case 2: for(Uint32 i=0; i<row; i++){
								for(Uint32 j=0; j<col; j++)
									(*data).push_back(regfile_[addr_read++]);
								addr_start += 3*WIDTH_VGRF_ROW;
								addr_read = addr_start;\
								assert(addr_read < size_vgregs_);
							} 
							break;
			case 3: for(Uint32 i=0; i<row; i++){
								for(Uint32 j=0; j<col; j++)
									(*data).push_back(regfile_[addr_read++]);
								addr_start += 4*WIDTH_VGRF_ROW;
								addr_read = addr_start;
								assert(addr_read < size_vgregs_);
							} 
							break;
		}
		wait();
		protect_read_.post(); 	
	 return true; 

}


template<class T> 
bool VGregs<T>::blockWrite(Uint32 addr_row_head,Uint32 addr_col_head
								, Uint32 mode,Uint32 row,Uint32 col, Vector<T> data) 
{
		protect_read_.wait();
		Uint32 addr_start = ((addr_row_head*WIDTH_VGRF_ROW) + addr_col_head);
		Uint32 addr_write = addr_start;
		switch(mode)
		{
			case 0: for(Uint32 i=0; i<row; i++){
								for(Uint32 j=0; j<col; j++)
									regfile_[addr_write++] = data[i*col+j];
								addr_start += WIDTH_VGRF_ROW;
								addr_write = addr_start;
								assert(addr_write < size_vgregs_);
							} 
							break;
			case 1: for(Uint32 i=0; i<row; i++){
								for(Uint32 j=0; j<col; j++)
									regfile_[addr_write++] = data[i*col+j];
								addr_start += 2*WIDTH_VGRF_ROW;
								addr_write = addr_start;
								assert(addr_write < size_vgregs_);
							} 
							break;
			case 2: for(Uint32 i=0; i<row; i++){
								for(Uint32 j=0; j<col; j++)
									regfile_[addr_write++] = data[i*col+j];
								addr_start += 3*WIDTH_VGRF_ROW;
								addr_write = addr_start;
								assert(addr_write < size_vgregs_);
							} 
							break;
			case 3: for(Uint32 i=0; i<row; i++){
								for(Uint32 j=0; j<col; j++)
									regfile_[addr_write++] = data[i*col+j];
								addr_start += 4*WIDTH_VGRF_ROW;
								addr_write = addr_start;
								assert(addr_write < size_vgregs_);
							} 
							break;
		}
		wait();
		protect_read_.post(); 	
	 return true; 

} 


// interface methods
template<class T> 
void VGregs<T>::initialize(Uint8 * addr_input, Uint32 size_input)
{
	//Uint8 *data_input;
	//data_input = (Uint8 *)malloc(400*600*sizeof(Uint8));

	T *start_reg_pr = regfile_;
	Uint8 *start_input_pr = addr_input;
	/* 4*9 var data */
	for(int i=0; i<size_input; i++)
		*start_reg_pr++ = (T)(*start_input_pr++);

	//free(data_input)
}

// interface methods
template<class T> 
void VGregs<T>::initialize(Uint32 * addr_input, Uint32 size_input)
{
	T *start_reg_pr = regfile_;
	Uint32 *start_input_pr = addr_input;
	/* 4*9 var data */
	for(int i=0; i<size_input; i++)
		*start_reg_pr++ = (T)(*start_input_pr++);
	//free(data_input)
}

template<class T> 
void VGregs<T>::print(std::ostream &out)
{
	Uint32 row = size_vgregs_/4 + ((size_vgregs_%4)?1:0);
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
