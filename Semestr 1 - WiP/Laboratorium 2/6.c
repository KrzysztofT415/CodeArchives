#include<stdio.h>
int main(void){
	int s=0,w=0,p=1000;
	for(int i=2;i<p;i++){
		for(int k=1;k<i;k++)if(i%k==0)s=s+k;
		if(s==i)printf("%d to liczba doskonala\n",i);
		else if(s<p){
			for(int l=1;l<s;l++)if(s%l==0)w=w+l;
			if(w==i&&w<s)printf("%d i %d to liczby zaprzyjaznione\n",i,s);
			w=0;
		}
		s=0;
	}
	return 0;
}
