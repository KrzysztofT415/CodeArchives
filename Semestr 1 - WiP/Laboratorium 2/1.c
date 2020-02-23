#include<stdio.h>
int main(void){
	int z=0,g=0,i=0,k[]={200,100,50,20,10,5,2,1},l,t=0;
	printf(" Podaj liczbe zloty : ");
	scanf("%d",&z);
	printf("Podaj liczbe groszy : ");
	scanf("%d",&g);
	printf("Banknoty:\n");
	while(z>0){
		if(z%k[i]!=z){
			l=(z-z%k[i])/k[i];
			printf("%d x %dzl\n",l,k[i]);
			z=z%k[i];
			if(z<10&&t==0){
				printf("Monety:\n");
				t++;
			}
		}
		i++;
	}
	i=i-6;
	while(g>0){
		if(g%k[i]!=g){
			l=(g-g%k[i])/k[i];
			printf("%d x %dgr\n",l,k[i]);
			g=g%k[i];
		}
		i++;
	}
	return 0;
}
