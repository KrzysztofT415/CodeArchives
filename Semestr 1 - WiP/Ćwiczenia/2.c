#include<stdio.h>
#include<time.h>
#include<math.h>
int p[1000000]={2,};
clock_t clock();
int main(void)
{
	int l=1,i=3,n;
	scanf("%d", &n);
	printf("1 liczba pierwsza: 2\n");
	while(l<n){
		for(int k=0;k<l;k++){
			if(i%p[k]==0)k++;continue;
		}
		p[l]=i;
		l++;
		printf("%d liczba pierwsza: %d\n",l,i);
		i=i+2;
	}
	printf("%ld\n",(1000*clock())/CLOCKS_PER_SEC);
	return 0;
}
