#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
	srand(time(0));
	int Liczba_Pytań = 0;
	int Możliwości = 1296,Nowe_Możliwości = 0;
	int Czerwone,Białe;
	int Licznik_Czerwonych=0,Licznik_Białych=0,Licznik_Liczb=0,Licznik_Obecności=0;
	int Losowa;
	int Pytanie[4];
	int Porównanie[4];
	int a[12][1296]={0};
	int b=0;

	//Tworzę pierwszy rząd tablicy ze wszystkimi możliwościami
	for (int i=0;i<Możliwości;i++)	a[b][i]=1111+i%6+((i-i%6)/6)%6*10+((((i-i%6)/6)-((i-i%6)/6)%6)/6)%6*100+((((((i-i%6)/6)-((i-i%6)/6)%6)/6)-((((i-i%6)/6)-((i-i%6)/6)%6)/6)%6)/6)%6*1000;
	do
	{
		//Biorę najmniejszą z możliwych i o nią pytam
		Pytanie[0]=(a[b][0])/1000;
		Pytanie[1]=(a[b][0])/100%10;
		Pytanie[2]=(a[b][0])/10%10;
		Pytanie[3]=(a[b][0])%10;
		printf("Pytanie %d\n", ++Liczba_Pytań);
		printf("[%d][%d][%d][%d]\n",Pytanie[0],Pytanie[1],Pytanie[2],Pytanie[3]);
		printf("Czerwone : ");
		scanf("%d",&Czerwone);
		printf("   Białe : ");
		scanf("%d",&Białe);
		//Sprawdzam czy wygrałem
		if (Czerwone == 4) {
			printf("Wygrałem w %d pytań\n", Liczba_Pytań);
			break;
		}
		//Porównuję możliwości z pytaniem
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
			//Poprawne umieszczam w nowym wierszu tablicy tablicy
			if(Licznik_Czerwonych!=Czerwone || Licznik_Białych!=Białe)
			else	{
				a[b+1][Nowe_Możliwości]=a[b][k];
				Nowe_Możliwości++;
				}
			Licznik_Czerwonych=0;
			Licznik_Białych=0;
			}
		//Sprawdzam czy nie oszukuje
		if (Nowe_Możliwości == 0) {
			printf("Oszukujesz!\nAlbo popełniłeś błąd :P\nZacznij jeszcze raz!\n");
			break;
			}

		b++;
		Możliwości = Nowe_Możliwości;
		Nowe_Możliwości=0;
	}	while(Czerwone!=4);
	return 0;
}
