#include<stdio.h>
#include"3f.h"
#include<assert.h>
int main(){
	long int n;
	scanf("%ld",&n);
	assert(n>0.0);
	printf("%d\n",phi(n));
	return 0;
}

