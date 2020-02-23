#include<stdio.h>
#include<math.h>
int main(void){
	int n=2,s=1,o=1000,aa,bb,cc;
	double w;
	while(n<=o){
		for(int a=1;a<=n;a++){
			aa=n;
			bb=a;
			while(bb!=0){
				cc=bb;
				bb=aa%bb;
				aa=cc;
			}
			if(aa==1)s=s+2;
		}
		w=(double)s/((double)n*(double)n);
		printf("%d ; %lf\n",n,w);
		n++;
	}
	return 0;
}
