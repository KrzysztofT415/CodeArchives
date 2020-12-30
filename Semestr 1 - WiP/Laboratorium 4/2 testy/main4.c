#include<stdio.h>
#include<assert.h>

int main(){
	int pytanie[4]={1,1,1,1};
	int r=0,w=0,r2=0,w2=0;
	int krok=1;
	int l=0,r0=0,r1=0,n=3,k=0,postep=0,postep2=0,wersja1=1,postep3=0,u=0,s=1,z=0,q=3,rw=0;
	do {
		printf("[%d] [%d] [%d] [%d]?\n",pytanie[0],pytanie[1],pytanie[2],pytanie[3]);
		printf("  red : ");
		scanf("%d",&r);
		assert(r<5);
		printf("white : ");
		scanf("%d",&w);
		assert(w<5);
		if(postep==0)
			{
			 if(r>0)
				{
				 r0=r;
				 postep++;
				}
			 else 	for(int i=0;i<4;i++)	{ pytanie[i]++; }
			}
		if(postep==1)
			{
			 printf("mam najmniejsze\n");
			 if(r0==1)
				{
				 if(w==0)
					{
					 if(l==0)
						{
						 for(int i=3;i>=1;i--)	{ pytanie[i]++; }
						 l++;
						}
					 else	{
						 postep++;
						 l=0;
						}
					}
				 else if(w==2)
					{
					 k=pytanie[l-1];
					 pytanie[l-1]=pytanie[l];
					 pytanie[l]=k;
					 l++;
					 if(r!=2)
						{
						 postep++;
						 postep2++;
						 r1=r+1;
						 w=0;
						 l=0;
						 if(r==1) wersja1=2;
						}
					}
				 else if(w==1)
					{
					 
					}
				}
			else if(r0==2)
				{
				 for(int i=3;i>=2;i--)	{ pytanie[i]++; }
				}
			else	{
				 if(r==3 && w==0)	{ pytanie[n]++; }
				 else	{
					 k=pytanie[n];
					 pytanie[n]=pytanie[n-1];
					 n--;
					 pytanie[n]=k;
					 if(w==1) pytanie[n]++;
					}
				}
			}
		 if(postep==2)
			{
			 if(wersja1==1)
				{
				 printf("mam pierwszego pewnego\n");
				 if(postep2==0)
					{
					 if(r>1)
						{
						 r1=r-1;
						 postep2++;
						}
					 else 	for(int i=1;i<4;i++)	{ pytanie[i]++; }
					}
				 if(postep2==1)
					{
					 printf("mam najmniejsze\n");
					 if(r1==1)
						{
						 if(w==0)
							{
							 if(l==0)
								{
								 for(int i=3;i>=2;i--)	{ pytanie[i]++; }
								 l++;
									}
							 else	{
								 r2=r-1;
								 postep++;
								 l--;
								}
								}
						 else if(w==2)
							{
							 k=pytanie[s];
							 pytanie[s]=pytanie[s+1];
							 pytanie[s+1]=k;
							 s++;
							 if(r!=2) { postep++; postep3++; }
							}
						 else if(w==1)
							{
							 
							}
						}
					 else	{
						 if(r==3)
							{
							 pytanie[n]++;
							 l++;
							}
				 		 else	{
							 k=pytanie[n];
							 pytanie[n]=pytanie[n-1];
							 n--;
							 pytanie[n]=k;
							 if(w==1) pytanie[n]++;
							}
						}
					}
				}
		 	 if(wersja1==2)
				{
				 
				}
			}
		 if(postep==3)
			{
			 printf("mam dwa pewne\n");
			 if(postep3==0)
				{
				 if(r>2)
					{
					 r2=r-1;
					 postep3++;
					}
				 else 	for(int i=2;i<4;i++)	{ pytanie[i]++; }
				}
			 if(postep3==1)
				{
				 if(r==2)
					{
					 k=pytanie[3];
					 pytanie[3]=pytanie[2];
					 pytanie[2]=k;
					 if(w==1) {q--; pytanie[q]++; }
					}
				 else	{
					 pytanie[q]++;
					}
				}
			}
		 krok++;
		}
	while(r!=4);
	printf("Wygrałem :P\nIlość pytań : %d\n",krok);
	return 0;
}
