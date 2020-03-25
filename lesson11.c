#include <stdio.h>
#include <math.h>
static double f_t (double t) {
return sqrt (t + 1/(1 + t * t));
}
static double integrate (double (*f_t) (double x), double x) {
double s = 0;
double a = 1; double eps = (x - 1) /100000;
double b = a + eps;
while (b <= x) {
s += eps * (f_t(a) + f_t(b)) / 2;
a = b;
b = a + eps;
}
	return s;
}
static double f (double (*f_t)(double t), double x, double alpha) {
return integrate(f_t, x) - alpha * x;
}
static double solve (double (*f)(double (*f_t)(double t), double x, double alpha), double alpha, double a, double b) {
double m = (a + b)/2;
if (fabs (a - b) < 1e-13)
return m;
if (f(f_t, a, alpha) * f(f_t, m, alpha) < 0)
return solve(f, alpha, a, m);
if (f(f_t, b, alpha) * f(f_t, m, alpha) < 0)
return solve(f, alpha, m, b);
return solve(f, alpha, a + 1e-13, b - 1e-13);
}
int main (void) {
	double a;
	scanf("%lf", &a);
	printf("%.10lf\n", solve(f, a, 0,  100 * a));
	return 0;
}