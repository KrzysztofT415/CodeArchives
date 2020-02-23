#include"agents.h"
#include<math.h>
#include<stdio.h>
#include<assert.h>
double distance(struct agent a1,struct agent a2){
	double d=0;
	d=sqrt(pow((a1.x-a2.x),2)+pow((a1.y-a2.y),2));
	assert(d>0);
	return d;
}
