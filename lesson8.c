#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M(i,j) arr[(i)*n+(j)]
#define M2(i,j) arr2[(i)*n+(j)]
#define M3(i,j) arr3[(i)*n+(j)]
#define eps 1e-10 
static void type1(double *arr3,double *arr,double *arr2,int n) {
int i,j,t;
for (i=0;i<n;i++) {
for (j=0;j<n;j++) {
for (t=0;t<n;t++) {
M3(i,j) += (M(t,j)*M2(i,t));}}}
return;}
static void type2(double *arr3,double *arr,double c,int n) {
int i,j;
for (i=0;i<n;i++) {
for (j=0;j<n;j++) {
M3(i,j)= M(i,j)*c;}}
return;}
static void summa(double *arr3,double *arr,double *arr2,int n) {
int i;
for (i=0;i<n*n;i++) {
arr3[i]=arr[i]+arr2[i];}
return;}
static void teylor(double *arr,double* res,int n){
double *m1,*m2;                               
int i,f=0;
double k=0;
m1=(double*)malloc(n*n*sizeof(double));
m2=(double*)malloc(n*n*sizeof(double));
for (i=0;i<(n*n);i++) {               
m1[i]=arr[i];}
for (i=0;i<(n*n);i++) {               
if (fabs(m1[i])>eps) f++;}
if (f==0) return; 
else {                  
type1(m2, arr, arr, n);                       
for (i=0;i<(n*n);i++) {
arr[i]=m2[i];}
for (i= 0;i<(n*n);i++) {
m2[i]=0;}
while (f != 0) {
k += 2;
type1(m2,m1,arr,n);                
for (i=0;i<(n*n);i++) {
m1[i]=m2[i]; }
for (i=0;i<(n*n);i++) {
m2[i]=0;}
type2(m2,m1,-1./(k*(k+1)), n);  
for (i=0;i<(n*n);i++) {
m1[i]=m2[i];}
for (i=0;i<(n*n);i++) {
m2[i]=0;}
summa(m2,res,m1,n);                   
for (i=0;i<(n*n);i++) {
 res[i]=m2[i];
 }
 for (i=0;i<(n*n);i++) {
m2[i]=0;}
 f=0;                              
for (i=0;i<(n*n);i++) {  
if (fabs(m1[i])>eps) f++;}}}
    return;}
int main (void) {
double *arr,*res;
int n=0,i,j;
FILE *f,*g;
f=fopen("input.txt","r");
g=fopen("output.txt","w");
fscanf(f,"%d%d",&n,&n);
arr=(double*)malloc(n*n*sizeof(double));
for (i=0;i<n;i++){
for (j=0;j<n;j++) { 
fscanf(f,"%lf",&M(i,j));}}
res=(double*)malloc(n*n*sizeof(double));
for(i=0;i<(n*n);i++) {
res[i]=arr[i];}
teylor(arr,res,n); 
fprintf(g,"%d ",n);
fprintf(g,"%d ",n);
for (i=0;i<(n*n);i++) {
if ((i+1)%n == 0) { fprintf(g,"%.11lf\n",res[i]);} else { fprintf(g,"%.11lf ",res[i]);}}
fclose(f);
fclose(g);
return 0;
}