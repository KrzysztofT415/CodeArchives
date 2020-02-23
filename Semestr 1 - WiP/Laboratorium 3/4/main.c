#include"agents.h"
#include<stdio.h>
int main(){
	struct agent Bob = newagent(0,0);
	struct agent Alice = newagent(3,3);
	north(&Bob);
	south(&Alice);
	west(&Alice);
	north(&Bob);
	east(&Bob);
	south(&Alice);
	printf("odległość = %f\n",distance(Bob,Alice));
	return 0;
}
