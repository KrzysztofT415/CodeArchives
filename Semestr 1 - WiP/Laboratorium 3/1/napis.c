#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
bool palindrom(char napis[]){
	int n=0,l=0;
	while((double)strlen(napis)/2.0>(double)n){
		if(napis[n]==napis[strlen(napis)-n-1])n++;
		else{
			l++;
			break;
		}
	}
	if(l==0)return true;
	else return false;
}
