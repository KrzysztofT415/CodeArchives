#include<stdio.h>
int main(void){
	double s=1.0,o=10;
	int n=1;
	while(s<=o){
		n++;
		s=s+1.0/(double)n;
	}
	printf("Najmniejsze takie n: %d\n",n);
	return 0;
}
