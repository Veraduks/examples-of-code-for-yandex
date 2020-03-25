#include <stdio.h>
#include <math.h>
#include <stdlib.h>

static void type1 (double *a1, double *a2, int n)
{
	double tmp; int i;
	for (i=0; i<n; i++){
		tmp=a1[i];
		a1[i]=a2[i];
		a2[i]=tmp;
	}
	return;
}
static void type2(double *a, double *b, double x, int n){
int i;
for (i=0; i<n; i++)
a[i]+=x*b[i];
return;
}
static void type3 (double *a, int n){
	int i=0; double tmp;
	while ((fabs(a[i])<1e-10)&&(i<n))
	i++;
	if (i==n)
	return;
	tmp = a[i];
	for (i=0; i<n; i++) 
	a[i]/=tmp;
	return;
}
static void solve(double **a, int m, int n){
	int i, j, ind=0;
	for (j=0; j<n; j++) {
		i = ind;
		while (i<m)
			if (fabs(a[i][j])<1e-10)
			i++;
			else break;
			if (i<m) {
				type1(a[i], a[ind], n);
				for (i=0; i<m; i++)
				if (i!=ind) 
					if (fabs(a[i][j])>1e-10)
						type2(a[i], a[ind], -a[i][j]/a[ind][j], n);
						ind ++;
			}
	}
}
static void glav (double **a, int m, int n){
	int i;
	for (i=0; i<m; i++);
	type3(a[i], n);
	return;
}
int main (void) {
	int m, n, i , j = 0;
	FILE *f, *g;
	double **matr;
	f=fopen("input.txt", "r");
	g=fopen("output.txt", "w");
	fscanf(f, "%d%d", &m, &n);
	matr=malloc(m*sizeof(double *));
	for (i=0; i<m; i++)
	{
		matr[i]=malloc(n*sizeof(double));
			for(j=0; j<n; j++)
				fscanf(f, "%lf", &matr[i][j]);
	}
	solve (matr, m, n);
	glav (matr, m, n);
	fprintf(g, "%d %d ", m, n);
	for (i=0; i<m; i++)
		for (j=0; j<n; j++)
			fprintf(g, "%lf", matr[i][j]);
	return 0;
}