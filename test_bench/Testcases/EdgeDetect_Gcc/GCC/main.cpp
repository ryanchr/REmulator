#include <stdio.h>
#include "edge_detect.h"

struct PIX
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
PIX  *pix;

int height,width;
short h = 8;
short w = 8;

unsigned char GetPix(int row,int col,int rgb);
unsigned short abs(short a);

int main()
{
#ifdef DEBUG
    printf("ENTER INTO MAIN\n");
#endif
    int i,j;
    unsigned short th = 50;
    FILE * pFile;
    
    short IMAGE_SIZE = h*w;
    
    pix = new PIX[IMAGE_SIZE];
    int offset =0;
    pFile = fopen("gcc.log","w");
    
    for(i=0;i<IMAGE_SIZE;i++)
    {
        pix[i].r= ppm_in[3*i+offset];
    	pix[i].g= ppm_in[3*i+1+offset];
    	pix[i].b= ppm_in[3*i+2+offset];
    }

///////////////////////////// oparation //////////////////////////////
    
    unsigned char p00r,p01r,p02r,p10r,p11r,p12r,p20r,p21r,p22r;
    unsigned char p00g,p01g,p02g,p10g,p11g,p12g,p20g,p21g,p22g;
    unsigned char p00b,p01b,p02b,p10b,p11b,p12b,p20b,p21b,p22b;
    unsigned char p00y,p01y,p02y,p10y,p11y,p12y,p20y,p21y,p22y;
    unsigned char value1,value2,value3;
    short Gx,Gy;
    
    for(i=0;i<h;i++)
        for(j=0;j<w;j++)
    	{
             p00r = GetPix(i-1,j-1,0);  p01r = GetPix(i-1,j,0);  p02r = GetPix(i-1,j+1,0);
             p10r = GetPix(i,j-1,0);    p11r = GetPix(i,j,0);    p12r = GetPix(i,j+1,0);
             p20r = GetPix(i+1,j-1,0);  p21r = GetPix(i+1,j,0);  p22r = GetPix(i+1,j+1,0);
             
             p00g = GetPix(i-1,j-1,1);  p01g = GetPix(i-1,j,1);  p02g = GetPix(i-1,j+1,1);
             p10g = GetPix(i,j-1,1);    p11g = GetPix(i,j,1);    p12g = GetPix(i,j+1,1);
             p20g = GetPix(i+1,j-1,1);  p21g = GetPix(i+1,j,1);  p22g = GetPix(i+1,j+1,1);
             
             p00b = GetPix(i-1,j-1,2);  p01b = GetPix(i-1,j,2);  p02b = GetPix(i-1,j+1,2);
             p10b = GetPix(i,j-1,2);    p11b = GetPix(i,j,2);    p12b = GetPix(i,j+1,2);
             p20b = GetPix(i+1,j-1,2);  p21b = GetPix(i+1,j,2);  p22b = GetPix(i+1,j+1,2);
    
             p00y = ((0x4C*p00r + 0x96*p00g + 0x1D*p00b)) >>8;
             p01y = ((0x4c*p01r + 0x96*p01g + 0x1D*p01b)) >>8;
             p02y = ((0x4c*p02r + 0x96*p02g + 0x1D*p02b)) >>8;
             p10y = ((0x4c*p10r + 0x96*p10g + 0x1D*p10b)) >>8;
             p11y = ((0x4c*p11r + 0x96*p11g + 0x1D*p11b)) >>8;
             p12y = ((0x4c*p12r + 0x96*p12g + 0x1D*p12b)) >>8;
             p20y = ((0x4c*p20r + 0x96*p20g + 0x1D*p20b)) >>8;
             p21y = ((0x4c*p21r + 0x96*p21g + 0x1D*p21b)) >>8;
             p22y = ((0x4c*p22r + 0x96*p22g + 0x1D*p22b)) >>8;
    
    		 Gy = 2*p01y + p00y + p02y - 2*p21y - p20y - p22y;
    		 Gx = 2*p12y + p02y + p22y - 2*p10y - p00y - p20y;
#ifdef DEBUG_NO
             if((i==0) &&(j==1)){
                 printf("p22r = %x\n",p22r);
                 printf("p22g = %x\n",p22g);
                 printf("p22b = %x\n",p22b);

                 printf("p12y = %x\n",p12y);
                 printf("p02y = %x\n",p02y);
                 printf("p22y = %x\n",p22y);
                 printf("p10y = %x\n",p10y);
                 printf("p00y = %x\n",p00y);
                 printf("p20y = %x\n",p20y);
                 printf("Gx = %x\n",Gx);
             }
#endif
#ifdef DEBUG
                 printf("Gx = %x\n",Gx);
#endif
            if(abs(Gx)>=th || abs(Gy)>=th){
//            if(Gx >= 0){
                 value1 = 0x00;
                 value2 = 0x00;
                 value3 = 0x00;
             } else {
                 value1 = 0xff;
                 value2 = 0xff;
                 value3 = 0xff;
             }
             fprintf(pFile,"%02x\n",value1);
             fprintf(pFile,"%02x\n",value2);
             fprintf(pFile,"%02x\n",value3);
    	}
#ifdef DEBUG
    printf("Test Finish!\n");
#endif
    return 1;
}

unsigned char GetPix(int row,int col,int rgb)
{
    if(row>h-1 || col>w-1 || row<0 || col<0)
        return 0;
    else
    {
        if(rgb == 0)
            return pix[row*w+col].r;
        else if(rgb == 1)
            return pix[row*w+col].g;
        else
            return pix[row*w+col].b;
    }
}

unsigned short abs(short a)
{
	if(a>=0)
		return a;
	else
		return -a;
}
