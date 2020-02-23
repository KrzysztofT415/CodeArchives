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
	int a[12][1296][4]={0};
	int b=0,z;
	//Tworzę pierwszy rząd tablicy ze wszystkimi możliwościami
	for (int i=0;i<Możliwości;i++)
		{
		 a[b][i][3]=1+i%6;
		 a[b][i][2]=1+((i-i%6)/6)%6;
		 a[b][i][1]=1+((((i-i%6)/6)-((i-i%6)/6)%6)/6)%6;
		 a[b][i][0]=1+((((((i-i%6)/6)-((i-i%6)/6)%6)/6)-((((i-i%6)/6)-((i-i%6)/6)%6)/6)%6)/6)%6;
		}
	do
	{
		//Biorę najmniejszą z możliwych i o nią pytam
		z = rand()%Możliwości;
		printf("Pytanie %d\n", ++Liczba_Pytań);
		printf("[%d][%d][%d][%d]\n",a[b][z][0],a[b][z][1],a[b][z][2],a[b][z][3]);
		printf("Czerwone : ");
		scanf("%d",&Czerwone);
		printf("   Białe : ");
		scanf("%d",&Białe);
		//Sprawdzam czy wygrałem
		if (Czerwone == 4)
			{
			 printf("Wygrałem w %d pytań\n", Liczba_Pytań);
			 break;
			}
		//Porównuję wszystkie możliwości z pytaniem
		for (int k = 1; k < Możliwości; k++)
			{
			 //Liczę czerwone
			 for (int j = 0; j < 4; j++)
				if (a[b][k][j] == a[b][z][j])
					Licznik_Czerwonych++;
			 //Liczę białe
			 for (int i = 1; i < 7; i++){
				for (int j = 0; j < 4; j++)
					if(a[b][z][j]==i && a[b][k][j]!=a[b][z][j])
						Licznik_Liczb++;
				for (int j = 0; j < 4; j++)
					if(a[b][k][j]==i && a[b][k][j]!=a[b][z][j] && Licznik_Obecności<Licznik_Liczb && Licznik_Liczb>0)
						Licznik_Obecności++;
				Licznik_Białych+=Licznik_Obecności;
				Licznik_Obecności=0;
				Licznik_Liczb=0;
				}
			 //Poprawne umieszczam w nowym wierszu tablicy tablicy
			 if(Licznik_Czerwonych==Czerwone && Licznik_Białych==Białe){
				for(int j = 0; j < 4; j++)
					{
					 a[b+1][Nowe_Możliwości][j]=a[b][k][j];
					}
				 Nowe_Możliwości++;
				}
			 Licznik_Czerwonych=0;
			 Licznik_Białych=0;
			}
		b++;
		Możliwości = Nowe_Możliwości;
		//Sprawdzam czy nie oszukuje
		if (Możliwości == 0) {
			printf("Oszukujesz!\nAlbo popełniłeś błąd :P\nZacznij jeszcze raz!\n");
			break;
			}
		Nowe_Możliwości=0;
	}	while(Czerwone!=4);
	return 0;
}
