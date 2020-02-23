#include"2f.h"
#include<stdio.h>
double rozwiazanie(double a,double b,double eps){
	double c;
	while(b-a>eps){
		c=(b+a)/2;
		if(f(a)*f(c)<0.0)
			b=c;
		else
			a=c;
	}
	return a;
}
