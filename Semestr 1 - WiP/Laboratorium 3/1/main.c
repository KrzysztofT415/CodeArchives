#include"1f.h"
#include<stdio.h>
int main(){
	char napis[50];
	scanf("%s",napis);
	if(palindrom(napis))printf("Jest to palindrom\n");
	else printf("Nie jest to palindrom\n");
	return 0;
}
