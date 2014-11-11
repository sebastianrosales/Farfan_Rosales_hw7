#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define gamma 1.4


double func1(double u1, double u2, double u3){
return u2;
}
double func2(double u1, double u2, double u3){
return pow(u2,2)/u1+(gamma-1)*(u3-(0.5*pow(u2,2)/u1));
}
double func3(double u1, double u2, double u3){
return (u3+(gamma-1)*(u3-0.5*pow(u2,2)/u1))*u2/u1;
}

int imprimirvector(double *vector, int tamano){
int j;
for(j=0;j<(tamano);j++){
printf(" i; %d, valor: %f \n",j,  vector[j]);
}
return 0;
}
int main(int argc, char **argv){
//Condiciones iniciales
double rhoinicializq,rhoinicialder,pinicializq,pinicialder;
rhoinicializq=1.0;
rhoinicialder=0.125;
pinicializq=pow(10,5);
pinicialder=pow(10,3);
//Variables del programa 
double tmax,tmin,xmin,xmax,dx,dt;
int xpoints, tpoints;
tmax=atof(argv[1]);;
tmin=0.0;
xmin=-10.0;
xmax=10.0;
tpoints=1000;
xpoints=1000; 
dx=(xmax-xmin)/xpoints;
dt=(tmax-tmin)/tpoints;
//Punteros importantes
double *x;

double *uinicial1,*uinicial2,*uinicial3; 
double *u1,*u2,*u3;
double *umedio1,*umedio2,*umedio3;
double *ufuturo1,*ufuturo2,*ufuturo3;

double *finicial1,*finicial2,*finicial3; 
double *f1,*f2,*f3;
double *fmedio1,*fmedio2,*fmedio3;
double *ffuturo1,*ffuturo2,*ffuturo3;
//Contadores// i en x & n en t
int i,n; 

//Inicializar punteros 
uinicial1=malloc(xpoints*sizeof(double));
uinicial2=malloc(xpoints*sizeof(double));
uinicial3=malloc(xpoints*sizeof(double));
u1=malloc(xpoints*sizeof(double));
u2=malloc(xpoints*sizeof(double));
u3=malloc(xpoints*sizeof(double));
umedio1=malloc(xpoints*sizeof(double));
umedio2=malloc(xpoints*sizeof(double));
umedio3=malloc(xpoints*sizeof(double));
ufuturo1=malloc(xpoints*sizeof(double)); 
ufuturo2=malloc(xpoints*sizeof(double));
ufuturo3=malloc(xpoints*sizeof(double));

finicial1=malloc(xpoints*sizeof(double));
finicial2=malloc(xpoints*sizeof(double));
finicial3=malloc(xpoints*sizeof(double)); 
f1=malloc(xpoints*sizeof(double));
f2=malloc(xpoints*sizeof(double));
f3=malloc(xpoints*sizeof(double));
fmedio1=malloc(xpoints*sizeof(double));
fmedio2=malloc(xpoints*sizeof(double));
fmedio3=malloc(xpoints*sizeof(double));
ffuturo1=malloc(xpoints*sizeof(double));
ffuturo2=malloc(xpoints*sizeof(double));
ffuturo3=malloc(xpoints*sizeof(double));
//Generar uninicial

for(i=0;i<(xpoints/2);i++){
uinicial1[i]=pinicializq;
uinicial2[i]=0.0;
uinicial3[i]= pinicializq/((gamma-1.0));
}
for(i=(xpoints/2);i<(xpoints);i++){
uinicial1[i]=pinicialder;
uinicial2[i]=0.0;
uinicial3[i]= pinicialder/((gamma-1.0));
}

//Generar finicial
for(i=0;i<(xpoints);i++){
finicial1[i]=func1(uinicial1[i],uinicial2[i],uinicial3[i]);
finicial2[i]=func3(uinicial1[i],uinicial2[i],uinicial3[i]);
finicial3[i]=func3(uinicial1[i],uinicial2[i],uinicial3[i]);
}

//Primer Paso
for(i=(0);i<(xpoints-1);i++){
umedio1[i]=0.5*(uinicial1[i+1]+uinicial1[i])-(dt/(2*dx))*(finicial1[i+1]-finicial1[i]);
umedio2[i]=0.5*(uinicial2[i+1]+uinicial2[i])-(dt/(2*dx))*(finicial2[i+1]-finicial2[i]);
umedio3[i]=0.5*(uinicial3[i+1]+uinicial3[i])-(dt/(2*dx))*(finicial3[i+1]-finicial3[i]);
fmedio1[i]=func1(umedio1[i],umedio2[i],umedio3[i]);
fmedio2[i]=func2(umedio1[i],umedio2[i],umedio3[i]);
fmedio3[i]=func3(umedio1[i],umedio2[i],umedio3[i]);
}
for(i=(1);i<(xpoints-1);i++){
u1[i]=uinicial1[i]-(dt/dx)*(fmedio1[i-1]-fmedio1[i]);
u2[i]=uinicial2[i]-(dt/dx)*(fmedio2[i-1]-fmedio2[i]);
u3[i]=uinicial3[i]-(dt/dx)*(fmedio3[i-1]-fmedio3[i]);
}
u1[0]=uinicial1[0];
u2[0]=uinicial2[0];
u3[0]=uinicial3[0];
u1[(xpoints-1)]=uinicial1[(xpoints-1)];
u2[xpoints-1]=uinicial2[xpoints-1];
u3[xpoints-1]=uinicial3[xpoints-1];


//El resto de pasos 
//Generar finicial
for(i=0;i<(xpoints);i++){
f1[i]=func1(u1[i],u2[i],u3[i]);
f2[i]=func3(u1[i],u2[i],u3[i]);
f3[i]=func3(u1[i],u2[i],u3[i]);
}
for(n=0;n<tpoints;n++){
for(i=(0);i<(xpoints-1);i++){
umedio1[i]=0.5*(u1[i+1]+u1[i])-(dt/(2*dx))*(f1[i+1]-f1[i]);
umedio2[i]=0.5*(u2[i+1]+u2[i])-(dt/(2*dx))*(f2[i+1]-f2[i]);
umedio3[i]=0.5*(u3[i+1]+u3[i])-(dt/(2*dx))*(f3[i+1]-f3[i]);
fmedio1[i]=func1(umedio1[i],umedio2[i],umedio3[i]);
fmedio2[i]=func2(umedio1[i],umedio2[i],umedio3[i]);
fmedio3[i]=func3(umedio1[i],umedio2[i],umedio3[i]);
}
for(i=(1);i<(xpoints-1);i++){
ufuturo1[i]=u1[i]-(dt/dx)*(fmedio1[i-1]-fmedio1[i]);
ufuturo2[i]=u2[i]-(dt/dx)*(fmedio2[i-1]-fmedio2[i]);
ufuturo3[i]=u3[i]-(dt/dx)*(fmedio3[i-1]-fmedio3[i]);
}
ufuturo1[0]=uinicial1[0];
ufuturo2[0]=uinicial2[0];
ufuturo3[0]=uinicial3[0];
ufuturo1[(xpoints-1)]=uinicial1[(xpoints-1)];
ufuturo2[xpoints-1]=uinicial2[xpoints-1];
ufuturo3[xpoints-1]=uinicial3[xpoints-1];
for(i=(0);i<(xpoints);i++){
u1[i]=ufuturo1[i];
u2[i]=ufuturo2[i];
u3[i]=ufuturo3[i];
}
}

double r,v,p,posicion;
//Archivo 
FILE *in;
    char filename[100000];
    sprintf(filename, "estado_%f.dat", tmax);
    in = fopen(filename,"w");
for(i=(0);i<(xpoints);i++){
posicion=xmin+dx*i; 
r=u1[i];
v=u2[i]/r;
p=(gamma-1)*(u3[i]-u2[i]*u2[i]/(2.0*u1[i]));
fprintf(in,"%f %f %f %f\n",posicion,v,p,r);
}
 
return 0;

}
