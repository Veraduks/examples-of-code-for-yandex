#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define eps 1e-10
static void Trans(double *matrix1, int n){
	int i, j;
	double *c;
	c=(double*)malloc(n*n*sizeof(double));
    memset(c, 0, n*n*sizeof(double));
	for (i=0; i<n; i++){
        for(j=0; j<n; j++){
            c[i*n+j]=matrix1[j*n+i];
        }
	}
	for (i=0; i<n; i++){
        for(j=0; j<n; j++){
            matrix1[i*n+j]=c[i*n+j];
        }
	}
}
static void type1(double *matrix1, double *matrix2, int n){
    int i, j, p;
    double *c;
    c=(double*)malloc(n*n*sizeof(double));
    memset(c, 0, n*n*sizeof(double));
    for(i=0; i < n; i++){
        for(j=0; j < n; j++){
            for(p=0; p < n; p++){
                c[i*n+j]+=matrix1[i*n+p]*matrix2[p*n+j];
            }
        }
    }
    for (i=0; i < n; i++){
        for(j=0; j < n; j++) {matrix1[i*n+j] = c[i*n+j];}
    }
    free(c);
}
static void type2(double *matrix1, double *matrix2, int n){
    int i, j, p;
    double *c;
    c=(double*)malloc(n*n*sizeof(double));
    memset(c, 0, n*n*sizeof(double));
    for(i=0; i < n; i++){
        for(j=0; j < n; j++){
            for(p=0; p < n; p++){
                c[i*n+j]+=matrix1[i*n+p]*matrix2[p*n+j];
            }
        }
    }
    for (i=0; i < n; i++){
        for (j=0; j < n; j++){matrix2[i*n+j] = c[i*n+j];}
    }
    free(c);
}
static void Rotation(double *matrix1, double *matrix2, int n){
    double x1 = 0, x2 =0;
    int i, k, p;
    for(k=0; k<n; k++){
        for(i=k+1; i<n; i++){
            double t = atan2(matrix1[i*n+k],matrix1[k*n+k]);
            for(p = k; p<n; p++){
                x1 = matrix1[k*n+p];
                matrix1[k*n+p]=x1*cos(t)+matrix1[i*n+p]*sin(t);
                matrix1[i*n+p]=(-1)*x1*sin(t)+matrix1[i*n+p]*cos(t);
            }
            for(p = 0; p<n; p++){
                x2 = matrix2[k*n+p];
                matrix2[k*n+p]=x2*cos(t)+matrix2[i*n+p]*sin(t);
                matrix2[i*n+p]=(-1)*x2*sin(t)+matrix2[i*n+p]*cos(t);
           }
        }
    }
}
int main(void) {
    FILE *in=fopen("input.txt", "r"),*out=fopen("output.txt", "w");
    int i, j, n, q=1;
    double *matrix1, *matrix2, *c;
    fscanf(in,"%d%d",&n, &n);
    matrix1 = malloc(n*n*sizeof(double));
    matrix2 = malloc(n*n*sizeof(double));
    c = malloc(n*n*sizeof(double));
    for(i = 0; i<n; i++){
        for(j = 0; j<n; j++){
            if(i==j){c[i*n+j]=1;}
            else{c[i*n+j]=0;}
        }
    }
    for(int i = 0; i<n*n; i++){fscanf(in,"%lf",&matrix1[i]);}
    while(q>0){
        for(i=0; i < n; i++){
            for(j=0; j < n; j++){
                if(i==j){matrix2[i*n+j]=1;}
                else{matrix2[i*n+j]=0;}
            }
        }
        q = 0;
        Rotation(matrix1, matrix2, n);
        type2(matrix2, c, n);
        Trans(matrix2, n);
        type1(matrix1, matrix2, n);
        for(i=0; i < n; i++){
            for(j=0; j < n; j++){
                if(i!=j){
                    if(fabs(matrix1[i*n+j])>eps){q=1; break;}
                }
            }
        }
    }
    for(i=0; i < n; i++){matrix1[i*n+i]=pow(matrix1[i*n+i], 0.5);}
    type1(matrix1, c, n);
    Trans(c, n);
    type1(c, matrix1, n);
    fprintf(out, "%d %d ", n, n);
    for(i=0; i < n*n; i++){fprintf(out, "%.10lf ", c[i]);}
    return 0;
}
