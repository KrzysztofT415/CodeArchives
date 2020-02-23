#include<stdio.h>
int main()
{
	int n;
	printf("Podaj n:\n");
	scanf("%d",&n);
	for(int k=1;k<=n;k++)
	{
		for(int i=n-k;i>0;i--)
		{
			printf(" ");
		}
		for(int l=2*k-1;l>0;l--)
		{
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
