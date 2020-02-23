#include<math.h>
int phi(long int n){
	int s=0,aa,bb,cc;
	double w;
	for(int a=1;a<=n;a++){
		aa=n;
		bb=a;
		while(bb!=0){
			cc=bb;
			bb=aa%bb;
			aa=cc;
		}
		if(aa==1)s=s+1;
	}
	return s;
}
