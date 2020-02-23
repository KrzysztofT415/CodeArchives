#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

bool match(char* wzorzec, char* łańcuch){
	int w=strlen(wzorzec);
	int ł=strlen(łańcuch);
	int gwiazdki=0,błąd=0,gwiazda=0;
	int j=0,k=1,p=0,q=1;
	//Szukam gwiazdek
	for(int i=0;i<w;i++)
		if(wzorzec[i]=='*')
			gwiazdki++;
	//Jeżeli występują gwiazdki
	if(gwiazdki>0){
		//Sprawdzam końcówkę
		for(int i=0;i<w && błąd==0;i++){
			if(wzorzec[w-i-1]!=łańcuch[ł-i-1] && wzorzec[w-i-1]!='*' && wzorzec[w-i-1]!='?')	błąd=1;
			else if(wzorzec[w-i-1]=='*')	i=w;
			}
		if(ł<w-gwiazdki) błąd=1;
		//Sprawdzam od początku
		for(int i=0;i+k<w && i+j+p<ł && błąd==0;i++){
			if(gwiazda==0){
				if(wzorzec[i]=='*'){
					gwiazda=1;
					if(gwiazdki==1)	{ 
						gwiazda=0;
						i=w+1;
						}
					while(wzorzec[i+q]=='*'){
						q++;
						k++;
						}
					}
				else if(wzorzec[i]!=łańcuch[i+p] && wzorzec[i]!='?')	błąd=1;

				}
			if(gwiazda==1){
				if(wzorzec[i+k]!=łańcuch[i+j+p] && wzorzec[i+k]!='?'){
					if(i+j+p==ł-1)	błąd=1;
					j++;
					k=1;
					}
				else	{
					j++;
					k++;
					if(wzorzec[i+k]=='*'){
						i=i+k;
						p=p+j-2;
						j=0;
						k=1;
						if(gwiazdki==2)	i=w+1;
						}
					}
				i--;
				}
			}
		}
	//Jeżeli nie ma gwiazdek i są równej długości to sprawdzam zgodność
	else if(gwiazdki==0 && w==ł){
		for(int i=0;i<w && błąd==0;i++)
			if(wzorzec[i]!=łańcuch[i] && wzorzec[i]!='?'){
				błąd=1;
				}
		}
	//Jeżeli nie ma gwiazdek i nie są równej długości są błędne		
	else błąd=1;
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
		printf("Łańcuch zgodny ze wzorcem.\n");
	else	printf("Łańcuch nie jest zgodny ze wzorcem.\n");
	return 0;
}
