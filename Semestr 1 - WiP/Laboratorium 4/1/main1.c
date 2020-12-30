#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

bool match(char* wzorzec, char* łańcuch){
	int w=strlen(wzorzec);
	int ł=strlen(łańcuch);
	int gwiazdki=0,błąd=0,gwiazda=0;
	int j=0,k=1,p=0;
	//Szukam gwiazdek
	for(int i=0;i<w;i++)
		if(wzorzec[i]=='*')
			gwiazdki++;
	printf("znalazłem %d gwiazdek\n",gwiazdki);
	//Jeżeli występują gwiazdki
	if(gwiazdki>0){
		//Sprawdzam końcówkę
		printf("Sprawdzam końcówkę\n");
		for(int i=0;i<w && błąd==0;i++){
			if(wzorzec[w-i-1]!=łańcuch[ł-i-1] && wzorzec[w-i-1]!='*' && wzorzec[w-i-1]!='?'){
				printf("wzorzec[%d]=%c =/= łańcuch[%d]=%c\n",w-i,wzorzec[w-i-1],ł-i,łańcuch[ł-i-1]);
				błąd=1;
				}
			else if(wzorzec[w-i-1]=='*'){
				printf("wzorzec[%d] == *\n",w-i);
				i=w;
				}
			else printf("wzorzec[%d]=%c === łańcuch[%d]=%c\n",w-i,wzorzec[w-i-1],ł-i,łańcuch[ł-i-1]);
			}
		if(błąd==1)	printf("Błędna końcówka\n");
		else		printf("Zgodna końcówka\nSprawdzam od początku\n");
		//Sprawdzam od początku
		for(int i=0;i+k<w && i+j+p<ł && błąd==0;i++){
			if(gwiazda==0){
				if(wzorzec[i]=='*'){
					printf("wzorzec[%d] == *\n",i);
					gwiazda=1;
					if(gwiazdki==1)	{ gwiazda=0; i=w+1; }
					}
				else if(wzorzec[i]!=łańcuch[i+p] && wzorzec[i]!='?'){
					printf("wzorzec[%d]=%c =/= łańcuch[%d]=%c\n",i,wzorzec[i],i+p,łańcuch[i]);
					błąd=1;
					}
				else printf("wzorzec[%d]=%c === łańcuch[%d]=%c\n",i,wzorzec[i],i+p,łańcuch[i+p]);
				}
			if(gwiazda==1){
				if(wzorzec[i+k]!=łańcuch[i+j+p] && wzorzec[i+k]!='?'){
					if(i+j+p==ł-1)	błąd=1;
					printf("wzorzec[%d]=%c =/= łańcuch[%d]=%c\n",i+k,wzorzec[i+k],i+j+p,łańcuch[i+j+p]);
					j++;
					k=1;
					}
				else	{
					printf("wzorzec[%d]=%c === łańcuch[%d]=%c\n",i+k,wzorzec[i+k],i+j+p,łańcuch[i+j+p]);
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
		printf("Zgodny ze wzorcem.\n");
	else	printf("Nie jest zgodny ze wzorcem.\n");
	return 0;
}
