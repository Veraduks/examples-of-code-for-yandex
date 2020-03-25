#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define eps 10e-11
static void qwe(double **a, int n)
{
    int i, j;
    printf("=================\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%lf\t", a[i][j]);
        }
        printf("\n");
    }
    printf("=================\n");
}
static void max (double **a, int n)
{
    int i, j;
    double t;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (a[i][i] > a[j][j])
            {
                t = a[i][i];
                a[i][i] = a[j][j];
                a[j][j] = t;
            }
        }
    }
}
static void qwerty (double **a, double **b, int x, int y, int n, double phi)
{
    int i;
    double x1, x2, y1, y2;
    for (i=0; i<n; i++)
    {
        x1=a[x][i];
        y1=a[y][i];
        a[x][i] = x1*cos(phi)+y1*sin(phi);
        a[y][i] = y1*cos(phi)-x1*sin(phi);
        x2=b[x][i];
        y2=b[y][i];
        b[x][i] = x2*cos(phi)+y2*sin(phi);
        b[y][i] = y2*cos(phi)-x2*sin(phi);

    }
}
static void edin(double **c,int n)
{
int i, j;
for (j=0; j<n; j++)
{
for(i=0; i<n; i++)
if (i==j) c[i][j]=1;
else c[i][j]=0;
    }
}
static void expo (double **a, double **b, int n)
{
int j, i, k;
double **c;
c = (double **)malloc(n * sizeof(double *));
for (i = 0; i < n; i++)
 {
c[i] = (double *)calloc(n, sizeof(double));
 }
for (j=0; j<n; j++)
 {
for(i=0; i<n; i++)
for (k=0; k<n; k++)
c[j][i] = c[j][i] + a[j][k] * b[k][i];
    }
for (j=0; j<n; j++)
for(i=0; i<n; i++)
a[j][i]=c[j][i];
}
static void trans (double **c, int n)
{
    int j, i;
    double s = 0;
    for (j=0; j<n; j++)
    {
        for(i=j+1; i<n; i++)
        {
            s=c[j][i];
            c[j][i]=c[i][j];
            c[i][j]=s;
        }
    }
}
static int srav (double **c, int n) 
{
    int j, i, p = 1;
    double s=0;
    for (j=0; j<n; j++)
    {
        for(i=0; i<n; i++)
            if (i!=j)
                s=s+fabs(c[j][i]);
    }
    if (s>eps) p=0;
    return p;
}
    static void RAQET (double **a, double **b, int n)
    {
        int i, j, k;
        double phi;
        j = 0;
        for (i=0; i<n; i++)
        {
            while ((fabs(a[j][i]) < eps) && j < n) j++;
            if (j < n)
            {
                for (k = i + 1; k < n; k++)
                {
                    phi=atan2(a[i][k], a[i][i]);
                    qwerty(a, b, i, k, n, phi);

                }
            }
            j=0;
        }
    }
    static void QRpro (double **A, int n)
    {
        int i, p=0;
        double **Q;
        Q = (double **)malloc(n * sizeof(double *));
        for (i = 0; i < n; i++)
        {
            Q[i] = (double *)calloc(n, sizeof(double));
            Q[i][i]=1;

        }
        qwe(A, n);
        while (p==0)
        {
            RAQET(A, Q, n);
            qwe(A, n);
            trans(Q, n);
            qwe(A, n);
            expo(A, Q, n);
            p = srav(A, n);
            edin(Q, n);
            qwe(A, n);
        }
    }
    int main(void)
    {
        FILE *f, *g;
        double **a;
        int n, m, i, j;
        n = 0;
        f = fopen ("input.txt", "r");
        g = fopen ("output.txt", "w");
        fscanf(f, "%d %d", &n, &m);
        a = (double **)malloc(n * sizeof(double *));
        for (i = 0; i < n; i++)
        {
            a[i] = (double *)calloc(n, sizeof(double));
        }
        for (j=0; j<n; j++)
            for (i=0; i<m; i++)
                fscanf(f, "%lf", &a[j][i]);
        QRpro(a,n);
        max(a,n);
        for (i = 0; i < n; i++)
        {
            fprintf(g, "%.11g ", a[i][i]);
        }
        fclose(g);
        fclose(f);
        return 0;
    }
