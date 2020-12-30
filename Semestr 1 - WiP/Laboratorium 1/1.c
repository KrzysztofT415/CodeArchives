#include<stdio.h>
int main()
{
	const char *czary = "ABRAKADABRA";
	for(int i=11;i>0;i--)
	{
		for(int t=0;t>i-11;t--)
		{
			printf(" ");
		}
		for(int k=0;k<i;k++)
		{
			printf("%c ",czary[k]);
		}
		printf("\n");
	}
	return 0;
}
