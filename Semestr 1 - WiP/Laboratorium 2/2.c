#include<stdio.h>
int main(void){
	int n;
	double s,r;
	printf("Podaj liczbę:");
	scanf("%d",&n);
	if(n==0)printf("Liczba n musi być dodatnia\n");
	else{
		for(int i=0;i<n;i++){
			scanf("%lf",&r);
			s=s+r;
		}
		s=s/n;
		printf("Srednia wynosi: %lf\n",s);
	}
	return 0;
}
