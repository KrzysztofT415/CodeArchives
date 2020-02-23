#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

int main(void){
	int Kod[4];
	int c[1296]={0};
	int Losowa;
	srand(time(0));
	for (int i=0;i<1296;i++)	c[i]=1111+i%6+((i-i%6)/6)%6*10+((((i-i%6)/6)-((i-i%6)/6)%6)/6)%6*100+((((((i-i%6)/6)-((i-i%6)/6)%6)/6)-((((i-i%6)/6)-((i-i%6)/6)%6)/6)%6)/6)%6*1000;
	Losowa = rand()%1296;
	Kod[0]=(c[Losowa])/1000;
	Kod[1]=(c[Losowa])/100%10;
	Kod[2]=(c[Losowa])/10%10;
	Kod[3]=(c[Losowa])%10;
	printf("Kod:\n[%d][%d][%d][%d]\n",Kod[0],Kod[1],Kod[2],Kod[3]);
	srand(time(0)+1);
	int Liczba_Pytań = 0;
	int Możliwości = 1296,Nowe_Możliwości = 0;
	int Czerwone,Białe;
	int Licznik_Czerwonych=0,Licznik_Białych=0,Licznik_Liczb=0,Licznik_Obecności=0;
	int Pytanie[4];
	int Porównanie[4];
	int a[8][1296]={0};
	int b=0;	
	//Tworzę tablicę ze wszystkimi możliwościami
	for (int i=0;i<Możliwości;i++)	a[0][i]=1111+i%6+((i-i%6)/6)%6*10+((((i-i%6)/6)-((i-i%6)/6)%6)/6)%6*100+((((((i-i%6)/6)-((i-i%6)/6)%6)/6)-((((i-i%6)/6)-((i-i%6)/6)%6)/6)%6)/6)%6*1000;
	do	{
		//Biorę losową z możliwych i o nią pytam
		Losowa = rand()%Możliwości;
		Pytanie[0]=(a[b][Losowa])/1000;
		Pytanie[1]=(a[b][Losowa])/100%10;
		Pytanie[2]=(a[b][Losowa])/10%10;
		Pytanie[3]=(a[b][Losowa])%10;
		printf("Pytanie %d, %d możliwych pozostało\n", ++Liczba_Pytań, Możliwości);
		printf("[%d][%d][%d][%d]\n",Pytanie[0],Pytanie[1],Pytanie[2],Pytanie[3]);
		//Liczę czerwone
		for (int j = 0; j < 4; j++)
			if (Kod[j] == Pytanie[j])
				Licznik_Czerwonych++;
		//Liczę białe
		for (int i = 1; i < 7; i++){
			for (int j = 0; j < 4; j++)
				if(Pytanie[j]==i && Pytanie[j]!=Kod[j])
					Licznik_Liczb++;
			for (int j = 0; j < 4; j++)
				if(Kod[j]==i && Pytanie[j]!=Kod[j] && Licznik_Obecności<Licznik_Liczb)
					Licznik_Obecności++;
			Licznik_Białych+=Licznik_Obecności;
			Licznik_Obecności=0;
			Licznik_Liczb=0;
			}
		Czerwone=Licznik_Czerwonych;
		Białe=Licznik_Białych;
		Licznik_Czerwonych=0;
		Licznik_Białych=0;
		printf("Czerwone : %d;",Czerwone);
		printf("   Białe : %d;\n",Białe);
		//Sprawdzam czy wygrałem
		if (Czerwone == 4) {
			printf("Wygrałem w %d pytań\n", Liczba_Pytań);
			break;
		}
		//Porównuję możliwości
		for (int k = 0; k < Możliwości; k++) {
			Porównanie[0]=(a[b][k])/1000;
			Porównanie[1]=(a[b][k])/100%10;
			Porównanie[2]=(a[b][k])/10%10;
			Porównanie[3]=(a[b][k])%10;
			//Liczę czerwone
			for (int j = 0; j < 4; j++)
				if (Porównanie[j] == Pytanie[j])
					Licznik_Czerwonych++;
			//Liczę białe
			for (int i = 1; i < 7; i++){
				for (int j = 0; j < 4; j++)
					if(Pytanie[j]==i && Pytanie[j]!=Porównanie[j])
						Licznik_Liczb++;
				for (int j = 0; j < 4; j++)
					if(Porównanie[j]==i && Pytanie[j]!=Porównanie[j] && Licznik_Obecności<Licznik_Liczb)
						Licznik_Obecności++;
				Licznik_Białych+=Licznik_Obecności;
				Licznik_Obecności=0;
				Licznik_Liczb=0;
				}
			//Kasuję niepoprawne a poprawne umieszczam w nowej tablicy
			a[b][Losowa]=0;
			if(Licznik_Czerwonych!=Czerwone || Licznik_Białych!=Białe){
				a[b][k]=0;
				}
			else	{
				a[b+1][Nowe_Możliwości]=a[b][k];
				Nowe_Możliwości++;
				}
			Licznik_Czerwonych=0;
			Licznik_Białych=0;
			}
		//Przechodzę dalej
		b++;
		Możliwości = Nowe_Możliwości;
		if (Nowe_Możliwości == 0) {
			printf("Oszukujesz!\n");
			break;
			}
		Nowe_Możliwości=0;
		
		} while(Czerwone!=4);
	return 0;
	}
