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
	int a[11][1296]={0};
	int b=0;

	//Tworzę tablicę ze wszystkimi możliwościami
	for (int i=0;i<Możliwości;i++)	a[0][i]=1111+i%6+((i-i%6)/6)%6*10+((((i-i%6)/6)-((i-i%6)/6)%6)/6)%6*100+((((((i-i%6)/6)-((i-i%6)/6)%6)/6)-((((i-i%6)/6)-((i-i%6)/6)%6)/6)%6)/6)%6*1000;
//	for (int i=0;i<Możliwości;i++)	{printf("%d ",a[0][i]);}
//	printf("\n");
	do
	{
		//Biorę losową z możliwych i o nią pytam
		Losowa = rand()%Możliwości;
		printf("%d\n",a[b][0]);
		Pytanie[0]=(a[b][Losowa])/1000;
		Pytanie[1]=(a[b][Losowa])/100%10;
		Pytanie[2]=(a[b][Losowa])/10%10;
		Pytanie[3]=(a[b][Losowa])%10;
		printf("Pytanie %d, %d możliwych pozostało\n", ++Liczba_Pytań, Możliwości);
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
		//Porównuję możliwości
		for (int k = 0; k < Możliwości; k++) {
			Porównanie[0]=(a[b][k])/1000;
			Porównanie[1]=(a[b][k])/100%10;
			Porównanie[2]=(a[b][k])/10%10;
			Porównanie[3]=(a[b][k])%10;
//			printf("%d%d%d%d ",Porównanie[0],Porównanie[1],Porównanie[2],Porównanie[3]);
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
//			printf("%d %d |\n",Licznik_Czerwonych,Licznik_Białych);
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
		//for (int i=0;i<Możliwości;++i) printf("%d ",a[b][i]);
		//printf("\n");
		Nowe_Możliwości=0;
	}	while(Czerwone!=4);
	return 0;
}
