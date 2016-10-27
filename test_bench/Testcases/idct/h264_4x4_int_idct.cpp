

#include <stdio.h>
#include <stdlib.h>

typedef signed char  int8_t;
typedef signed short int16_t;
typedef signed int   int32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

typedef short DCTELEM;

typedef unsigned int size_t;



static inline  int av_clip(int a, int amin, int amax)
{
    if      (a < amin) return amin;
    else if (a > amax) return amax;
    else               return a;
}

 static __inline void idct_internal(uint8_t *dst, DCTELEM *block, int stride, int block_stride, int shift){
   
	 int i,j;
    
    block[0] += 1<<(shift-1) ;//相当于在最后一步做四舍五入

    for( i=0; i<4; i++){
        const int z0=  block[0 + block_stride*i]     +  block[2 + block_stride*i];
        const int z1=  block[0 + block_stride*i]     -  block[2 + block_stride*i];
        const int z2= (block[1 + block_stride*i]>>1) -  block[3 + block_stride*i];
        const int z3=  block[1 + block_stride*i]     + (block[3 + block_stride*i]>>1);

        block[0 + block_stride*i]= z0 + z3;
        block[1 + block_stride*i]= z1 + z2;
        block[2 + block_stride*i]= z1 - z2;
        block[3 + block_stride*i]= z0 - z3;
    } //行变换

    for(i=0; i<4; i++){
        const int z0=  block[i + block_stride*0]     +  block[i + block_stride*2];
        const int z1=  block[i + block_stride*0]     -  block[i + block_stride*2];
        const int z2= (block[i + block_stride*1]>>1) -  block[i + block_stride*3];
        const int z3=  block[i + block_stride*1]     + (block[i + block_stride*3]>>1);

		block[i + 0*block_stride]= ((z0 + z3) >> shift);
        block[i + 1*block_stride]= ((z1 + z2) >> shift);
        block[i + 2*block_stride]= ((z1 - z2) >> shift);
        block[i + 3*block_stride]= ((z0 - z3) >> shift);

    }//列变换
    for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
		{
			dst[j + i*stride]= av_clip( dst[j + i*stride] + block[j + i*block_stride], 0, 255);
		}
	}

}
/*
16个4x4亮度块,存储顺序
0	1   |	4	5	
2	3   |	6	7	
------------------
8	9   |	12	13	
10	11  |	14	15	
*/

int block_offset[] ={0,4,64,68,8,12,72,76,128,132,192,196,136,140,200,204};
int main()
{
	DCTELEM block[256];
	uint8_t dst[256];
	int stride = 16;
    int block_stride = 4;	

    int shift = 6;

	FILE *fp1;
	FILE *fp2;
	
	int i,j;
    
	for (i=0; i< 256; i++)
	{
		block[i] = 60*i;  
	}

	for (i=0; i< 256; i++)
	{
		dst[i] = 0;
	}

//print input
	if((fp1=fopen("input.txt", "w"))==NULL)
{
	printf("Cannot open this file!\n");
	return 0 ;
}
	for(i=0;i<256;i++) 
	{
		fprintf(fp1,"block[%d]=0x%x(%d)\n",i,block[i],block[i]);
	}
	fclose(fp1);
 /*//print input
    for(i=0;i<16;i++)
  {
      for(j=0;j<16;j++)
        printf("%d,",block[16*i+j]);
        printf("\n");
  }
      printf("\n"); */

/*做16个4x4IDCT组成16X16,源数据block是顺序存放，目的数据dest是Z形存放,注意是先4x4 Z型组成8x8,8x8 Z型组成16X16，最后16X16应该顺序存放*/
    for (i=0; i< stride; i++)
       idct_internal(dst+ block_offset[i], block+stride*i, stride, block_stride, shift);

 //print output
    if((fp2=fopen("output.txt", "w"))==NULL)
{
	printf("Cannot open this file!\n");
	return 0;
}
	for(i=0;i<256;i++) 
	{
		fprintf(fp2,"dst[%d]=0x%x(%d)\n",i,dst[i],dst[i]);
	}
	fclose(fp2);

  /*  for( i=0;i<16;i++)
  {
     for( j=0;j<16;j++)
       printf("%d,",dst[16*i+j]);
       printf("\n");
  }
     printf("\n"); */


 return 0;
}
