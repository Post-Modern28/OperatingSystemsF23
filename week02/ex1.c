#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(){
	int a;
	unsigned short int b;
	long c;
	float d;
	double f;
	a = INT_MAX;
	b = USHRT_MAX;
	c = LONG_MAX;
	d = FLT_MAX;
	f = DBL_MAX;
	printf("Size of int %d: %lu \n Size of unsigned short %hu: %lu \n Size of long %ld: %lu \n Size of float %f: %lu \n Size of double %lf: %lu", a, sizeof(a), b, sizeof(b), c, sizeof(c), d, sizeof(d), f, sizeof(f));
}
