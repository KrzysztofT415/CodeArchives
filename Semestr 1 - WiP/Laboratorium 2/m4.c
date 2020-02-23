#include<stdio.h>
#include<math.h>
int p[1000000]={2,};
int main(void){
	int i=3,l=1,s=0,k=0,o=1000;
	double w;
	while(i<=o){
		for(int k=0;k<sqrt(l);k++)if(i%p[k]==0)goto r;
		p[l]=i;
		l++;
		r:
		i=i+2;
	}
	for(int n=2;n<=o;n++){
		if(p[k]<=n){
			s++;
			k++;
			}
		w=(double)s/((double)n/(double)log(n));
	printf("%d ; %lf\n",n,w);
	}
	return 0;
}
