#include <stdio.h>
#include <math.h>
#include <stdlib.h>

static double f(double x){
return x - log(x);
}
static double solve (double a, double b, double (*f)(double x)){
double m = (a + b) /2;
int i, imin; double x1, x2, xmin;
double *array;
if ((b - a) < 1e-10) return m;
x1 = (a + m) /2; x2 = (m + b) /2;
array = malloc(5 * sizeof(double));
array[0] = a;
array[1] = x1;
array[2] = m;
array[3] = x2;
array[4] = b;
xmin = array[0];
imin = 0;
for (i = 1; i < 5; i++)
if (f(array[i]) < f(xmin)) {
xmin = array[i];
imin = i;
}
if (imin == 0) {
free(array);
return solve (a, x1, f);
}
if (imin == 4) {
free(array);
return solve (x2, b, f);
}
return solve (array[imin - 1], array[imin + 1], f);
free(array);
}
int main (void){
double a, b;
scanf("%lf%lf", &a, &b);
printf ("%lf\n", solve(a, b, f));
return 0;
}