#include "stdio.h"
#include "math.h"
#ifndef FFT_Def
#define FFT_Def

#define PI 3.1415926535
#define uchar unsigned char


#define N   16						//FFT点数（长度）
#define BIT 8						//FFT的位数（每个数据点的类型），只能是8、16、32

#if (BIT==8)						//8-bit 有关常量
	#define BITTYPE char		        	//char代表16位整数
	#define OVS 52					//最大不溢出幅度，如果计算过程中超过此幅度程序将所有点除2
	#define DOVS 104				//最大不溢出幅度*2，如果计算过程中超过此幅度程序将所有点除4
	#define WNS 0x7F				//旋转因子，也就是此位数下的最大整数
	#define SHN 7					//移位因子，当乘以旋转因子后，数值被扩大了2^SHN，因此需要右移

#elif (BIT==16)
	#define BITTYPE short
	#define OVS 13572
	#define DOVS 27145
	#define WNS 0x7FFF
	#define SHN 15 

#elif (BIT==32)
	#define BITTYPE int
	#define OVS 889516850
	#define DOVS 1779033700
	#define WNS 0x7FFFFFFF
	#define SHN  31

#endif
//提示：
//OVS的值是通过设想最坏情况下，在输出不超过此类型允许数值时，加乘运算输入端的最大幅值
//此值的大小是：此类型的最大正数/(1+sqrt(2))

#if (N==2048)
#define FindIndex FindIndex11bit
#elif (N==1024)
#define FindIndex FindIndex10bit
#elif  (N==512)
#define FindIndex FindIndex9bit
#elif  (N==256)
#define FindIndex FindIndex8bit
#elif  (N==128)
#define FindIndex FindIndex7bit
#elif (N==64)
#define FindIndex FindIndex6bit
#elif (N==32)
#define FindIndex FindIndex5bit
#elif (N==16)
#define FindIndex FindIndex4bit
#endif

#if (N==64)
BITTYPE fft_initial_real[64] = {
0x01,0x00,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
0x40
};
BITTYPE fft_initial_imag[64] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00
};
#elif (N==32)
BITTYPE fft_initial_real[32] = {
0x01,0x00,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
0x20
};
BITTYPE fft_initial_imag[32] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00
};
BITTYPE wn_initial_real[16] = {127,124,117,105,89,70,48,24,0,-24,-48,-70,-89,-105,-117,-124
};
BITTYPE wn_initial_imag[16] = {0,-24,-48,-70,-89,-105,-117,-124,-127,-124,-117,-105,-89,-70,-48,-24
};
#elif (N==16)
BITTYPE fft_initial_real[16] = {
0x01,0x00,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
0x10
};
BITTYPE fft_initial_imag[16] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00
};
BITTYPE wn_initial_real[8] = {127,117,89,48,0,-48,-89,-117
};
BITTYPE wn_initial_imag[8] = {0,-48,-89,-117,-127,-117,-89,-48
};
#endif

struct Complex{							//构造复数结构
BITTYPE real;
BITTYPE imag;
};

typedef struct Complex COMPLEX;
//寻找对应当前下标的反转下标

int FindIndex11bit(int k){
	int j;
	k=k&(0x7ff);
	j=((k&0x001)<<10)+((k&0x002)<<8)+((k&0x004)<<6)+((k&0x008)<<4)+((k&0x010)<<2)+((k&0x020))+((k&0x040)>>2)+((k&0x080)>>4)+((k&0x100)>>6)+((k&0x200)>>8)+((k&0x400)>>10);
	return j;
}

int FindIndex10bit(int k){
	int j;
	k=k&(0x3ff);
	j=((k&0x001)<<9)+((k&0x002)<<7)+((k&0x004)<<5)+((k&0x008)<<3)+((k&0x010)<<1)+((k&0x020)>>1)+((k&0x040)>>3)+((k&0x080)>>5)+((k&0x100)>>7)+((k&0x200)>>9);
	return j;
}

int FindIndex9bit(int k){
	int j;
	k=k&(0x1ff);
	j=((k&0x001)<<8)+((k&0x002)<<6)+((k&0x004)<<4)+((k&0x008)<<2)+((k&0x010))+((k&0x020)>>2)+((k&0x040)>>4)+((k&0x080)>>6)+((k&0x100)>>8);
	return j;
}

uchar FindIndex8bit(uchar k){
	uchar j;
	k=k&(0xff);
	j=((k&0x001)<<7)+((k&0x002)<<5)+((k&0x004)<<3)+((k&0x008)<<1)+((k&0x010)>>1)+((k&0x020)>>3)+((k&0x040)>>5)+((k&0x080)>>7);
	return j;
}

uchar FindIndex7bit(uchar k){
	uchar j;
	k=k&(0x7f);
	j=((k&0x001)<<6)+((k&0x002)<<4)+((k&0x004)<<2)+((k&0x008))+((k&0x010)>>2)+((k&0x020)>>4)+((k&0x040)>>6);
	return j;
}

uchar FindIndex6bit(uchar k){
	uchar j;
	k=k&(0x3f);
	j=((k&0x001)<<5)+((k&0x002)<<3)+((k&0x004)<<1)+((k&0x008)>>1)+((k&0x010)>>3)+((k&0x020)>>5);
	return j;
}

uchar FindIndex5bit(uchar k){
	uchar j;
	k=k&(0x1f);
	j=((k&0x001)<<4)+((k&0x002)<<2)+((k&0x004))+((k&0x008)>>2)+((k&0x010)>>4);
	return j;
}

uchar FindIndex4bit(uchar k){
	uchar j;
	k=k&(0xf);
	j=((k&0x001)<<3)+((k&0x002)<<1)+((k&0x004)>>1)+((k&0x008)>>3);
	return j;
}

//反转下标
void ReverseIndex(COMPLEX *x){
int i,j;
COMPLEX tmp;
for (i=0;i<N;i++){
	j=FindIndex(i);
	if (j>i){
		tmp.real=x[i].real;
		tmp.imag=x[i].imag;
		x[i].real =x[j].real;
		x[i].imag =x[j].imag;
		x[j].real=tmp.real;
		x[j].imag=tmp.imag;
		}
	}
}
//按时间抽取法的fft变换，输入反序，输出正序
void fft(COMPLEX *x){				//x为欲变换数组，也当作输出数组，N为点数，支持1024（其它的点数请自行修改反转下标函数即可）
	int i,j,k,u=0,l=0,wi=0;				//j第二层循环（子块中的每个蝶形的循环计数）
										//k第一层循环（横向fft变换阶数，为log2（N）
										//u 蝶形上标x[upper],l 蝶形下标x[lower]，wi旋转因子下标wn[wi]
	int SubBlockNum,SubBlockStep=1;		//SubBlockNum当前k层子块数量，SubBlockStep当前k层不同子块的相同位置元素间间隔
	bool ov,ovd;							//溢出标志
	COMPLEX wn[N/2],XkWn;				//wn为旋转因子数组，XkWn为临时存储当前蝶形的旋转因子的临时变量			
	for (k=0;k<N/2;k++){				//初始化wn数组，在嵌入式设备中，此数组请预先计算并写成常量数组，以便于节省时间
#ifdef DEBUG
			wn[k].real= wn_initial_real[k];
			wn[k].imag= wn_initial_imag[k];
#endif
#ifdef DEBUG_X
			wn[k].real=(BITTYPE)(cos(2*PI*k/N)*WNS);
			wn[k].imag=(BITTYPE)(sin(-2*PI*k/N)*WNS);
#endif
#ifdef DEBUG
            printf("FFT_WN[%d].real = %d ",k,wn[k].real);
            printf("FFT_WN[%d].imag = %d \n",k,wn[k].imag);
#endif
		}
	ReverseIndex(x);					//输入反序
	for(k=N;k>1;k=(k>>1)){				//第一个循环，代表log2(k)阶的变换
#ifdef DEBUG_X
		ov=0;ovd=0;						//溢出缩放检查
		for(i=0;i<N;i++)				//遍历查找是否溢出
			if (x[i].real>DOVS || x[i].imag>DOVS || x[i].real<-DOVS || x[i].imag<-DOVS)				//超出两倍允许值，所有值右移2个bit
			{
				ovd=1;
				break;
			}
			else if (x[i].real>OVS || x[i].imag>OVS || x[i].real<-OVS || x[i].imag<-OVS)			//超出允许值，所有值右移1个bit
			{
				ov=1;
			}
		if (ovd==1)
			for(i=0;i<N;i++)
			{
				x[i].real=x[i].real>>2;
				x[i].imag=x[i].imag>>2;
			}
		else if(ov==1)
			for(i=0;i<N;i++)
			{
				x[i].real=x[i].real>>1;
				x[i].imag=x[i].imag>>1;
			}
#endif
		SubBlockNum=k>>1;				//子块个数为所做点数的一半
		SubBlockStep=SubBlockStep<<1;	//子块间同等地位的元素间隔以2为倍数递增
		wi=0;							//旋转因子初始化
		for(j=0;j<SubBlockStep>>1;j++){	//第二层循环，更新j值，j表示各个子块的第j个蝶形。因为每个子块的同地位蝶形具有相同的wn，所以用第二层循环控制wn
			for(u=j;u<N;u+=SubBlockStep){		//第三层循环，循环于各个子块间的第j个蝶形，计算所有蝶形。直到下标u越界。(u>N)		
						l=u+(SubBlockStep>>1);	//下标l计算
						#if (BIT==32)			//注：__int64加入的目的是保留32位相乘结果的高32位，不加入则高32位会忽略。此句需要针对平台修改。
						XkWn.real=(((__int64)x[l].real*wn[wi].real)>>SHN)-(((__int64)x[l].imag*wn[wi].imag)>>SHN);//蝶形x[u]=x[u]+x[l]*Wn,x[l]=x[u]-x[l]*Wn的复数计算
						XkWn.imag=(((__int64)x[l].imag*wn[wi].real)>>SHN)+(((__int64)x[l].real*wn[wi].imag)>>SHN);
						#else
						XkWn.real=((x[l].real*wn[wi].real)>>SHN)-((x[l].imag*wn[wi].imag)>>SHN);//蝶形x[u]=x[u]+x[l]*Wn,x[l]=x[u]-x[l]*Wn的复数计算
						XkWn.imag=((x[l].imag*wn[wi].real)>>SHN)+((x[l].real*wn[wi].imag)>>SHN);
						#endif
						x[l].real=x[u].real-XkWn.real;
						x[l].imag=x[u].imag-XkWn.imag;
						x[u].real=x[u].real+XkWn.real;
						x[u].imag=x[u].imag+XkWn.imag;
			}
			wi+=SubBlockNum;			//第二层循环更新wi值
		}
	}

}

#endif
