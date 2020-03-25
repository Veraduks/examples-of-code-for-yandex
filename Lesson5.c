#include <stdio.h>
#include <math.h>
#include <stdlib.h>
struct point {
   double x;
   double y;
};
static int compare (const void *l, const void *r) {
	 struct point *L = (struct point *)l;
	 struct point *R = (struct point *)r;
	 if (L->x < R->x)
	 	return -1;
	return 1;
}
static void interpolation (struct point a1, struct point a2, struct point a3, double *a, double *b, double *c) {
double x1  = a1.x, y1 = a1.y, x2 = a2.x, y2 = a2.y, x3 = a3.x, y3 = a3.y;
double D = (x3 - x2) * (x3 - x1) * (x2 - x1);
double D_c = y1 * x2 * x3 * (x3 - x2) + x1 * y2 * x3 * (x1 - x3) + x1 * x2 * y3 * (x2 - x1);
double D_b = -(y1 * (x3 * x3 - x2 * x2) + y2 * (x1 * x1 - x3 * x3) + y3 * (x2 * x2 - x1 * x1));
double D_a = -(y2 * x3 - y3 * x2 - y1 * x3 + y3 * x1 + y1 * x2 - y2 * x1);
*a = D_a / D;
*b = D_b / D;
*c = D_c / D;
return;
}
static int position (struct point *mas, int n, double x0){
	int i = -1;
	while ((x0 > mas[i + 1].x) && (i <= n))
	i++;
	return i;
}

static double polinom (double x0, struct point p1, struct point p2, struct point p3){
double a, b, c;
interpolation (p1, p2, p3, &a, &b, &c);
return a * x0 * x0 + b * x0 + c;
}

static double solving (struct point *mas, int N, double x0){
int i;
	qsort (mas, N, sizeof (struct point), compare);
	i = position (mas, N, x0);
	if (i < N - 2)
		return polinom(x0, mas[i], mas[i + 1], mas[i + 2]);
	return polinom (x0, mas[i - 1], mas[i], mas[i + 1]);


}

int main (void) {
double x0;
FILE *f, *g;
struct point *mas;
int i = 0, N = 1;
f = fopen("input.txt", "r");
fscanf(f, "%lf", &x0);
mas = malloc (N * sizeof(struct point));
while (!(feof(f))) {
fscanf(f, "%lf%lf", &mas[i].x, &mas[i].y);
i++;
if (i >= N)
mas = realloc (mas, (N *= 2) * sizeof (struct point));
}
N = i - 1;
g = fopen("output.txt", "w");
fprintf (g, "%lf", solving(mas, N, x0));
printf("%lf\n\n", solving(mas, N, x0));
return 0;
	
}