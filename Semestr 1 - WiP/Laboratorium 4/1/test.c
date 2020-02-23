#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

bool match(char* wzorzec, char* łańcuch){
	int w=strlen(wzorzec);
	int ł=strlen(łańcuch);
	int gwiazdki=0,błąd=0,gwiazda=0;
	int j=0;
	for(int i=0;i<w;i++)
		if(wzorzec[i]=='*')
			gwiazdki++;
	if(gwiazdki>0){
		printf("gwiazdki\n");
		for(int i=w;i>0;i++)
			if(wzorzec[i]!=łańcuch[i] && wzorzec[i]!='*'){
				błąd=1;
				break;
				}
		for(int i=0;i<w;i++)
			if(gwiazda==0 && (wzorzec[i]!=łańcuch[i+j] && wzorzec[i]!='*')){
				błąd=1;
				break;
				}
			else if(gwiazda==1){
				if(wzorzec[i]!=wzorzec[i+j]){
					i--;
					j++;
					}
				else	gwiazda=0;
				}
			else if(wzorzec[i]=='*')
				gwiazda=1;
				printf("znaleziona\n");
		return true;
		}
	else if(gwiazdki==0 && w==ł){
		for(int i=0;i<w;i++)
			if(wzorzec[i]!=łańcuch[i] && wzorzec[i]!='?'){
				błąd=1;
				break;
				}
		}		
	else błąd=1;
	if(błąd==1)	
		return false;
	else	return true;
}

int main(){
	char* wzorzec[20],* łańcuch[20];
	bool l=false;
/*	printf("Podaj wzorzec : \n");
	scanf("%s",wzorzec);
	printf("Podaj łańcuch : \n");
	scanf("%s",łańcuch);
*/	
	wzorzec=a*b*a;
	łańcuch=abababababababababababa;
	if(match(wzorzec,łańcuch))	l=true;
	printf("match(a*b*a,abababababababababababa) = %b\n",l);
	return 0;
}




















