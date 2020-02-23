#include<stdio.h>
#include<assert.h>
int main(){
	int p[6][4]={{1,1,1,1},{2,2,2,2},{3,3,3,3},{4,4,4,4},{5,5,5,5},{6,6,6,6}};
	int q[2][4]={{1,1,1,1},{1,1,1,1}};
	int q0[4]={0,0,0,0};
	int a[4]={0,0,0,0};
	int postep=0,pytanie=0;
	int r=0,w=0;
	int r0=0,w0=0;
	int licznik1=0,licznik2=0,licznik3=0;
	int bufor=0,maks=0,pewniaki=0;
	while(r!=4){
		//Jeżeli nie znalazłem wszystkich liczb to szukam wolnych miejsc i do nich dodaje
		if(a[3]==0)
			for(int j=0;j<4;j++)
				if(q[1][j]==0)
					q[0][j]++;

		//Pytam się
		printf("[%d] [%d] [%d] [%d]?\n",q[0][0],q[0][1],q[0][2],q[0][3]);
		printf("  red : ");
		scanf("%d",&r);
		assert(r<5);
		printf("white : ");
		scanf("%d",&w);
		assert(w<5);

		//Jeżeli nie znalazłem wszystkich liczb i znalazłem nową to dopisuję ją do znalezionych
		if(a[3]==0)
			if(r+w>r0+w0)
				for(int i=licznik1;i<r+w;i++){
					a[i]=pytanie+1;
					licznik1++;
					}

		//Blokuję te co powinienem
		switch(postep){
			case 0:
				//Szukam najmniejszej liczby, jeżeli nie znalazłem kasuję dany wiersz
				if(r>0)	postep++;
				else	for(int j=0;j<4;j++)
						p[pytanie][j]=0;
				break;
			case 1:
				if(r0==1)
				else if(r0==2)
				else if(r0==3){
					for(
				postep++;
				break;
			case 2:
				if(r0==1)
				else if(r0==2)
				else if(r0==3)
				break;
		}
/*
		//Sprawdzenie nowych pewniaków
		for(int t=0;t<4;t++){
			if(a[t]!=0){
				if(a[t]==a[t+2] && t+2<4){
					maks=3;
					t=t+2;
					}
				else if(a[t]==a[t+1] && t+1<4){
					maks=2;
					t++;
					}
				else maks=1;
				for(int j=0;j<4;j++)
					if(p[a[t]-1][j]==a[t])
						licznik2++;
				if(licznik2==maks)
					for(int j=0;j<4;j++){
						if(p[a[t]-1][j]==a[t])
							for(int i=0;i<6;i++){
								if(p[i][j]!=a[t])
									p[i][j]=0;
								}
						else	q[1][j]=1;
						}
				licznik2=0;
				bufor=0;
				maks=0;
			}
		}
*/
		//Blokuję pewniaki
		for(int t=0;t<pewniaki-1;t++)
			q[1][t]=1;

		//Blokuję liczby znalezione na miejscach niepewnych
		for(int t=0;t<4;t++){
			if(a[t]==a[t+2] && t+2<4){
				maks=3;
				t=t+2;
				}
			else if(a[t]==a[t+1] && t+1<4){
				maks=2;
				t++;
				}
			else maks=1;
			if(a[t]!=0){
				if(pewniaki>0)
					for(int r=pewniaki-1;r>0;r++)
						if(a[t]==q[0][r])
							maks--;
				for(int j=pewniaki-1;j<4 && maks>0;j++)
					if(q[1][j]==0 && p[a[t]-1][j]!=0){
						q[0][j]=a[t];
						q[1][j]=1;
						maks--;
						}
				}
			else break;
			maks=0;
			}


		/*
		for(int j=0;j<4;j++){
			for(int i=0;i<6;i++)
				if(p[i][j]!=0){
					bufor=i;
					licznik2++;
				}
			if(licznik2==1)
				for(int t=0;t<4;t++){
					if(a[t]==bufor+1){
						if(a[t]==a[t+2] && t+2<4){
							maks=3;
							t=t+2;
							}
						else if(a[t]==a[t+1] && t+1<4){
							maks=2;
							t++;
							}
						else maks=1;
						for(int jj=0;jj<4;jj++)
							if(p[bufor][jj]!=0) licznik3++;
						if(licznik2==maks)
							for(int jj=0;jj<4;jj++)
								if(jj!=j)
									p[bufor][jj]=0;
			licznik3=0;
			licznik2=0;
			bufor=0;
		}
		*/

		//Wypisanie macierzy i liczb
		for(int i=0;i<6;i++){
			for(int j=0;j<4;j++) printf("[%d] ",p[i][j]);
			printf("\n");
		}
		printf("liczby:");
		for(int i=0;i<4;i++) printf("|%d",a[i]);
		printf("|\n");
		for(int j=0;j<4;j++) printf("%d %d\n",q[0][j],q[1][j]);

		r0=r;
		w0=w;
		pytanie++;
	}
	printf("Wygrałem :P\nIlość pytań : %d\n",pytanie);
	return 0;
}
