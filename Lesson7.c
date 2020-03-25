#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define eps 0.0000000001
//#define swap(x,y) {double t = x; x = y; y = t;}

static double norma (double **a, int n, int m)
{
    int i, j, k=0;
    for (j=0; j<n; j++)
        for (i=0; i<m; i++)
         if (fabs(a[j][i])>eps) k=1;
    return k;
}

static int rang (double **a, int n, int m)
{
    int k, i;
    i=m;
    k=n-1;
    while((i==m)&&(k>=0))
    {
        i=0;
        while ((fabs(a[k][i])<eps)&&(i<m)) i++;
        if (i==m)k--;
    }
    return k+1;
}
static void swap (double a, double b)
{
    double x;
    x = a;
    a = b;
    b = x;
}
static void type1 (double **a, int m, int j, int t)
{
    int k = 0;
    for (k=0; k< m; k++)
        swap(a[j][k], a[t][k]);
}
static void type2 (double **a, int m, int k, int j, double x)
{
    int i=0;
    for (i=0; i<m; i++)
    {
        a[j][i]=a[j][i]-x*a[k][i];
    }
}
static void Gaus (double **a, int n, int m)
{
     int i, j=0;
     int min;
     int sh;
     sh = 0;
     if (n > m) min = m;
     else min = n;
     i = 0;
     while (i<min && i + sh < m)
     {
         j = i;
         while (j < n && fabs(a[j][i + sh])<eps) j++;
         if (j<n)
         {
             printf("%d %d\n", j, sh);
             type1(a, m, j, i);
             for (j=i+1; j<n; j++) type2(a, m, i, j, a[j][i + sh]/a[i][i + sh] );
             i++;
         }
         else
         {
             sh++;
         }
     }
}

int main(void)
{
    FILE *f, *g;
    double **a;
    int n, m, i, j, x=0, nom;
    f = fopen ("input.txt", "r");
    g = fopen ("output.txt", "w");
    fscanf(f, "%d %d", &n, &m);
    a = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
    {
        a[i] = (double *)calloc(m, sizeof(double));
    }
    for (j=0; j<n; j++)
        for (i=0; i<m; i++)
        fscanf(f, "%lf", &a[j][i]);
     nom=norma(a, n, m);
     if (nom==0) x=0;
     else{
    Gaus(a,n,m);
    x=rang(a, n, m);
    }
    fprintf(g, "%d", x);
    fclose(g);
    fclose(f);
    return 0;
}
