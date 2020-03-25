#include <stdio.h>
#include <stdlib.h>
#include <math.h>
static double sinus(double x)
{
    double a, s;
	int i=1;
    a = x; s = x;
    while (fabs(a)>10e-10)
    {
        a = -a*x*x / (2 * i*(2 * i + 1));
        s += a;
		i++;
    }
	return s;
	}

int main (void)
{
	double x, solve;
	scanf("%lf", &x);
	if (x>M_PI) x=fmod(x,2*M_PI);
	solve = sinus(x);
	printf("%.12g", solve);
	return 0;
}
