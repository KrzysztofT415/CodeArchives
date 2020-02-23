#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

bool match(char* wzorzec, char* łańcuch){
	int w=strlen(wzorzec);
	int ł=strlen(łańcuch);
	int błąd=0,gwiazda=0;
	int l=0,l0=0,i0=0,p=0;
	for(int i=0;i<w && błąd==0;i++){
		if(wzorzec[i]==łańcuch[i+p] || wzorzec[i]=='?'){
			if(wzorzec[i+1]=='*' && gwiazda==1){
				}
			}
		else	if(wzorzec[i]=='*'){
				gwiazda=1;
				i0=i;
				}
		else 	{
			if(gwiazda==0)
				błąd=1;
			else	{
				if(i==i0)
				i=i0;
				}
			}
		}
	if(błąd==1)	
		return false;
	else	return true;
}

int main(){
	char wzorzec[100], łańcuch[100];
	printf("Podaj wzorzec : \n");
	scanf("%s",wzorzec);
	printf("Podaj łańcuch : \n");
	scanf("%s",łańcuch);
	if(match(wzorzec,łańcuch)==true)
		printf("Zgodny ze wzorcem.\n");
	else	printf("Nie jest zgodny ze wzorcem.\n");
	return 0;
}
