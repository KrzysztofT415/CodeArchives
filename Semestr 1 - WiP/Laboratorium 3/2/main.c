#include<math.h>
#include<stdio.h>
#include<assert.h>
#include"2f.h"
int main(){
	double a,b,eps;
	printf("Podaj a:");
	scanf("%lf",&a);
	printf("Podaj b:");
	scanf("%lf",&b);
	assert(f(a)*f(b)<0);
	for(int k=1;k<=8;k++){
		eps=pow(10,-k);
		printf("Z dokładnością eps dla k=%d, miejscem zerowym jest: %lf\n",k,rozwiazanie(a,b,eps));
	}
	return 0;
}
