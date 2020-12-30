#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void)
{
	int n=0,l=0;
	char t[50];
	scanf("%s",t);
	int i=strlen(t);
	while(i/2>n)
	{
		if(t[n]==t[i-n-1])++n;
		else
		{
			printf("Nie jest to palindrom\n");
			++l;
			break;
		}
	}
	if(l==0)printf("Jest to palindrom\n");
	return 0;
}
