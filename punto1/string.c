#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Funciones usadas
double *allocate_memory(double *x, double dx);
double *initial_wave(double *x);
FILE *createfile(double *y, double dens);

//Funcion main
int main(int argc, char **argv){
  
  double dens = atof(argv[1]);
  double dx = 101;
  double *x,*y;
  FILE *archivo;
  
  x = allocate_memory(x,dx);
  y = allocate_memory(y,dx);
  
  //devuelve la onda triangular inicial
  y = initial_wave(x);

  //Archivo con la evolucion de la onda
  archivo = createfile(y,dens);
  
  return 0;
}




//Asigna la memoria correspondiente
double *allocate_memory(double *x , double dx){
  x = malloc(sizeof(double)*dx);
}



//Crea la onda triangular inicial
double *initial_wave(double *x){
  double delX = 1;
  double dx=101;
  double lenght=100;
  double *y_u;
  int i;
  y_u = allocate_memory(x,dx);  
  for(i=0; i< dx ;i++){
    x[i]= i*delX;
    if(x[i]<(0.8*lenght)){
      y_u[i] = 1.25*(x[i]/lenght);
    }
    else{
      y_u[i] = 5- 5*(x[i]/lenght);
    }
  }
  return y_u;
}


//Crea el archivo con las filas y columnas de la evoulucion de la onda
FILE *createfile(double *y, double dens){
  FILE *nfile;
  char nameFile[100];
  int i,j;
  int k = 1;
  double dx = 101;
  double dt = 12000;
  double tension = 40;
  double max_rows = 120;
  double max_cols=101;
  int max = max_cols-1;
  double *y_pre,*y_next;
  double delX = 1;
  double delT= max_rows/ dt;
  double c = pow((tension/dens), 0.5);
  double r = c*(delT/delX);
  
  y_pre = allocate_memory(y_pre,dx);
  y_next = allocate_memory(y_next,dx); 

  sprintf( nameFile ,"string_%f.dat",dens);
  nfile = fopen( nameFile, "w");

  for(i=0;i<=max_cols; i++){
    if(i<=99){
      fprintf(nfile, "%f ", y[i]);
    }
    if(i==max_cols){
      fprintf(nfile, "%f \n", y[i]);
    }
  }
  
  for(i=1; i < (max_cols-1) ; i++ ){
    max = max_cols -1;   
    y_next[0]= y[0];
    y_next[max]= y[max];
    y_next[i]= y[i] +((r*r)/2.0)*(y[i+1]-2.0*y[i] + y[i]);
  }

  for(i=0;i<=max_cols; i++){
    if(i<=99){
      fprintf(nfile, "%f ", y_next[i]);
    }
    if(i==max_cols){
      fprintf(nfile, "%f \n", y_next[i]);
    }
  }

  

  for(j=2;j< dt;j++){
    for(i=0;i<max_cols;i++){
      y_pre[i]= y[i];
      y[i]= y_next[i];
    }
    
    for(i=1; i < (max_cols-1) ; i++ ){
      y_next[i] = (2.0*(1.0-r*r))*y[i]- y_pre[i] + (r*r)*(y[i+1]+y[i-1]);
    }
    if((j*delT==k)){
      for(i=0;i<=max_cols; i++){
	if(i<=99){
	  fprintf(nfile, "%f ", y[i]);
	}
	if(i==max_cols){
	  fprintf(nfile, "%f \n", y[i]);
	}
      }
      k=k+1;
    }
  }
  fclose(nfile);
}
