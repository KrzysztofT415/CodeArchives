#include<stdio.h>
#include<math.h>
int p[1000000]={2,};
int main(void){
	int i=3,l=1,s=0,o=100000;
	double w;
	while(i<=o){
		for(int k=0;k<sqrt(l);k++)if(i%p[k]==0)goto r;
		p[l]=i;
		l++;
		r:
		i=i+2;
	}
	for(int n=2;n<=o;n++){
		for(int k=0;p[k]<=n&&k<l;k++)s++;
	w=(double)s/((double)n/(double)log(n));
	printf("%d ; %lf\n",n,w);
	s=0;
	}
	return 0;
}
