#include<stdio.h>
int main()
{
	int n;
	printf("Podaj n:\n");
	scanf("%d",&n);
	for(int i=n;i>0;i--)
	{
		for(int l=2*n;l>0;l--)
		printf("*");
	printf("\n");
	}
return 0;
}
