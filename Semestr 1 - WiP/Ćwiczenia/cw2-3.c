#include<stdio.h>
int p[1000000]={2,};
int main(void)
{
	int i=2,n,l=0;
	scanf("%d", &n);
	while(n!=p[l])
	{
		if(n%p[l]==0)
		{
			n=n/p[l];
			printf("%d\n",p[l]);
		}
		else
		{
		for(int k=0;k<l+1;k++)
		{
			if(i%p[k]==0)goto r;
		}
		p[l+1]=i;
		l++;
		r:
		i++;
		}
	}
	printf("%d\n",p[l]);
	return 0;
}
