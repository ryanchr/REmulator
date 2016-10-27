#include <stdio.h>       
#include <stdlib.h>       
#include "time.h"       
      
int main( )        
{        
    long i = 10000000L;
		int image[600][400];
    int tone[256];
		for(int i=0; i<600; i++)
			for(int j=0; j<400; j++)
				image[i][j] = 0;
    for(int i=0; i<256; i++)
				tone[i] = 0;

    clock_t start, finish;        
    double Total_time;        
    /* 测量一个事件持续的时间*/        
    printf( "Time to do %ld empty loops is ", i );        
    start = clock();  

		for(int i=0; i<600; i++)
		 for(int j=0; j<400; j++)
			tone[image[i][j]] = tone[image[i][j]]+1;

    //while( i--) ;        
    finish = clock();        
    Total_time = (double)(finish-start) / CLOCKS_PER_SEC;        
    printf( "%f seconds\n", Total_time);        
    return 0;       
}       