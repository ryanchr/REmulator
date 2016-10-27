#include <stdio.h>
main()
{
	int x[4]={7,3,1,1};
	int y[6]={0};
	int h[3]={5,2,3};
	int n,k;
	int s[6][3];
	for(n=0;n<6;n++)
	{
		for(k=0;k<3;k++)
		{
			if((n>=k)&&(n-k<4)) s[n][k]=x[n-k];
			else s[n][k]=0;
		}
	}
	for(n=0;n<6;n++)
	{
		for(k=0;k<3;k++)
		{
			y[n]+=h[k]*s[n][k];
		}
	}
	for(n=0;n<6;n++)
		printf("%d ",y[n]);
}