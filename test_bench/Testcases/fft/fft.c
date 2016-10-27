#include "stdio.h"
#include "math.h"
#include "fft.h"

int main()
{
    int i;

    //计算
    //定义FFT计算缓冲区
    COMPLEX FFTData[N];
    
    for (i=0;i<N;i++)
    {
    	FFTData[i].real=fft_initial_real[i];
    	FFTData[i].imag=fft_initial_imag[i];
    }

#ifdef DEBUG
    for (i=0;i<N;i++)
    {
        printf("FFT_DATA[%d].real = %d ",i,FFTData[i].real);
        printf("FFT_DATA[%d].imag = %d \n",i,FFTData[i].imag);
    }
#endif

    fft(FFTData);
    
#ifdef DEBUG
    for (i=0;i<N;i++)
    {
        printf("FFT_DATA[%d].real = %d ",i,FFTData[i].real);
        printf("FFT_DATA[%d].imag = %d \n",i,FFTData[i].imag);
    }
#endif
     
    return(1);
}

