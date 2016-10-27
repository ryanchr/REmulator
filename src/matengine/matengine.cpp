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

#include <systemc.h>
#include "../tools/system_def.h"
#include "../parameter/parameter_arch.h"
#include "matengine.h"
using std::cout;
using std::endl;

void MatEngine::inputEngine()
{
#if DEBUG_ENABLE_MAT_ENGINE
	Engine *ep;
	mxArray *input = NULL;
	//Open the Matlab Engine
	if(!(ep=engOpen("MATLAB"))){
		cout<<"Can't Start MatLab Engine"<<endl;
		return;
	}
	
	//input = mxCreateNumericMatrix(600,400,mxUINT8_CLASS,mxREAL);

	cout<<engEvalString(ep,"input=imread('Peppers1.jpg');");
	//cout<<engEvalString(ep,"subplot(1,2,1);");
	//cout<<engEvalString(ep,"imshow(uint8(input));");

	input = engGetVariable(ep,"input");

	unsigned char *start_pr;
	/* allocate memory for member structure */
	size_t bytes_to_copy;
	start_pr = ( unsigned char *)mxGetData(input);
	bytes_to_copy = mxGetElementSize(input);
	//cout<<"sizeof(char)"<<sizeof(char)<<endl;
	//cout<<"bytes: "<<bytes_to_copy<<endl;

	/* Copy data of image to vector data */
	memcpy(input_data_,start_pr,bytes_to_copy*400*600);

	mxDestroyArray(input);
	engEvalString(ep,"close;");
	engClose(ep);
#endif

	return;
}

Uint8 * MatEngine::returnDataPr() const
{
	return input_data_;
}

void MatEngine::outputEngine(Uint32 *output)
{
#if DEBUG_ENABLE_MAT_ENGINE
	Engine *ep;
	mxArray *outputdata = NULL;
	Uint32 temp[256];

	if(!(ep=engOpen("MATLAB"))){
		cout<<"Can't Start MatLab Engine"<<endl;
		return;
	}	

	Uint32 *temp_pr = output;
	outputdata=mxCreateNumericMatrix(256,1,mxUINT32_CLASS,mxREAL);

	for(Uint32 i=0; i<256; i++)
		temp[i] = temp_pr[i];

	Uint32 * start_pr = (Uint32 *)mxGetData(outputdata);
	size_t bytes_to_copy;
	bytes_to_copy = mxGetElementSize(outputdata);
	memcpy(start_pr,temp,bytes_to_copy*256);

	engPutVariable(ep,"h",outputdata);
	engEvalString(ep,"f=imread('Peppers1.jpg');");
	//engEvalString(ep,"subplot(1,2,1);");
	//engEvalString(ep,"imshow(f);");
	//engEvalString(ep,"h=zeros(256,1);");
	engEvalString(ep,"hs=zeros(256,1);");
	engEvalString(ep,"hp=zeros(256,1);");
	engEvalString(ep,"g=zeros(600,400);");  //m=600, n=400

	engEvalString(ep,"Nf=400*600;");

	engEvalString(ep,"format long;");
	engEvalString(ep,"h = double(h);");

	engEvalString(ep,"k=0;");
	for(int i=0; i<256; i++){
		engEvalString(ep,"k=k+1;");
		engEvalString(ep,"hs(k)=h(k)/Nf;");
	}

	engEvalString(ep,"m=0;");
	for(int i=0; i<256; i++){
		engEvalString(ep,"m=m+1;");
		engEvalString(ep,"hp(m)=sum(hs(1:m));");
	}

	engEvalString(ep,"for i=1:600	;  \
									  for j=1:400 ;  \
									if f(i,j)==0 ; \
										g(i,j)=0;    \
										end;    \
									if f(i,j)~=0;          \
									  g(i,j)=uint8(256*hp(f(i,j)));  \
									end;    \
									end;    \
									end;"   
	);

	//engEvalString(ep,"subplot(1,2,2);");
	//engEvalString(ep,"imshow(uint8(g));");
	engEvalString(ep,"imwrite(uint8(g),'equal_output.jpg','jpg');");

	mxDestroyArray(outputdata);
	engEvalString(ep,"close;");
	engClose(ep);
#endif

	return;
}