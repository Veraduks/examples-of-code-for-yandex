#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static double f1 (double x)
{
	return 2*x - 5;
}

static double f2 (double x)
{
	return 1 / (x * log(2));
}

static double integrate(double a, double b, int N, double (*f)(double x))
{
double d, s=0;
int i;
	d=(b-a)/N;
for(i=0;i<N;i++)
	s+=f((a+i*d+a+(i+1)*d)/2)*d;
		return s;
}

int main (void)
{
	double a, b, solve;
	int N;
	scanf("%lf%lf%d", &a, &b, &N);
	solve=integrate(a,b,N,f1);
	printf("%.12g ", solve);
	solve=integrate(a,b,N,f2);
	printf("%.12g", solve);
	return 0;
}