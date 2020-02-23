#include<stdio.h>
#include<math.h>
int main()
{
	float a,b,c,d,k,t;
	printf("Podaj wspolczynnik a:\n");
	scanf("%f",&a);
	printf("Podaj wspolczynnik b:\n");
	scanf("%f",&b);
	printf("Podaj wspolczynnik c:\n");
	scanf("%f",&c);
	d=b*b-4*a*c;
	if(d<0)
	printf("Nie ma rozwiazania w R\n");
	else
	{
	if(d==0)
	{
	k=(-b)/2*a;
	printf("Posiada jedno rozwiazanie: %f\n",k);
	}
	else
	{
	k=((-b)-sqrt(d))/2*a;
	t=((-b)+sqrt(d))/2*a;
	printf("Posiada dwa rozwiazania: %f i %f\n",k,t);
	}
	}
	return 0;

}
