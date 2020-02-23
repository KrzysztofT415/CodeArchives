#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

const char *mm_numbers = "123456";





int main(void)
{
	int Liczba_Rund = 0;
	long Możliwości;
	int r,w;

	int g, ggg;
	long *b, Nowe_Możliwości;
	char *gstr;

	int *ct, *cg, rr = 0, ww = 0, tt, gg;
	char *ra;
	ra = calloc(5,1);

	srand48(time(0));

	long *a,z;
	a=calloc(1296,sizeof(long));
	for (int k=z=0;k<1296;++k) a[z++] = k;
	Możliwości = 1296;
						for (int i=0;i<1296;++i) printf("%ld ",a[i]);
	do
	{
		Nowe_Możliwości = 0;
		g = a[(long)(Możliwości * drand48())];
		printf("Runda %d, %ld możliwych pozostało\n", ++Liczba_Rund, Możliwości);
		ggg=g;
		for (int j = 0; j < 4; ++j, ggg /= 6)
			ra[j] = mm_numbers[g%6];
		gstr = ra;
		printf("[%s]\n", gstr);
		free(gstr);
		printf("  red : ");
		scanf("%d",&r);
		printf("white : ");
		scanf("%d",&w);

		if (r == 4) {
			printf("Wygrałem w %d pytań\n", Liczba_Rund);
			break;
		}

		b = calloc(Możliwości, sizeof(long));
		for (int k = 0; k < Możliwości; ++k) {
			unsigned r0;
			ct = alloca(6 * sizeof(int)); memset(ct, 0, 6 * sizeof(int));
			cg = alloca(6 * sizeof(int)); memset(cg, 0, 6 * sizeof(int));
			for (int j = 0; j < 4; ++j, a[k] /= 6, g /= 6) {
				tt = a[k] % 6, gg = g % 6;
				if (tt == gg) ++ww;
				++ct[tt], ++cg[gg];
				}
			for (int i = 0; i < 6; ++i)
				ww += ct[i] < cg[i]? ct[i] : cg[i];
			r0 = (unsigned)rr<<16 | (ww-rr);
			if (r0>>16 == r && (r0&0xffff) == w)
				b[Nowe_Możliwości++] = a[k];
		}

		free(a);
		a = b, Możliwości = Nowe_Możliwości;
		if (Nowe_Możliwości == 0) {
			printf("Oszukujesz!\n");
			break;
		}
//						for (int i=0;i<Nowe_Możliwości;++i) printf("%ld ",a[i]);
	}	while(r!=4);
	return 0;
}
