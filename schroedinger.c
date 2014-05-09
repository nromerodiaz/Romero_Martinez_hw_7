#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14159265359
#define FLOAT float

// Constantes usadas en el proceso

#define K  16*PI
#define SIGMA  0.05
FLOAT dx =  1/10000;
FLOAT dt =  0.2*(dx**2);
FLOAT alpha = dt/(2*(dx**2));

/* Funcion Potencial */

FLOAT V(FLOAT pos);

/* Funcion de copiado */

void copy(FLOAT* old, int n_points);

/* Funcion que aplica la condicion inicial */

void init_cond(FLOAT* pos, FLOAT* Re, FLOAT* Im, int x_points, FLOAT dx)

/* Funcion que genera los nuevos valores para las partes reales de la funcion */

void new_value(FLOAT* Re, FLOAT* Im, FLOAT* pos, int x_points);

/* ===========================================MAIN============================================ */

int main(int argc, char** argv){

  FLOAT min_x = 0.0;
  FLOAT max_x = 50.0;
  int x_points = (max_x-min_x)/dx;
  int t_points = 80/dt;
  int k = 0;
  FLOAT *Re;
  FLOAT *Im;
  FLOAT *pos;
  FLOAT *V;
  Re = malloc(sizeof(FLOAT)*x_points);
  Im = malloc(sizeof(FLOAT)*x_points);
  pos = malloc(sizeof(FLOAT)*x_points);
  V = malloc(sizeof(FLOAT)*x_points);

  /* Inicializacion de la posicion */

  int l = 1;
  pos[0] = 0;
  for(l=1;l<x_points;l++){
    pos[l] = pos[l-1]+dx;
  }

  /* Aplicamos la condicion inicial */

  void init_cond(pos, Re, Im, x_points, dx);

  /* Solucion */

  FILE *wave, *prob;

  int i = 1;
  int j = 1;

  FLOAT* RHO = malloc(sizeof(FLOAT)*t_points);

  FLOAT* tempRe = Re;
  FLOAT* tempIm = Im;

  FLOAT* nextRe = malloc(sizeof(FLOAT)*x_points);
  FLOAT* nextIm = malloc(sizeof(FLOAT)*x_points);


  tempRe[0] = 0;
  tempRe[x_points-1] = 0;
  tempIm[0] = 0;
  tempIm[x_points-1] = 0;
  nextRe[0] = 0;
  nextRe[x_points-1] = 0;

  wave = fopen("wave.dat", "w");
  prob = fopen("prob.dat", "w");

  for(k=0;k<t_points;k++){

    for (i=1;i<x_points-1; i++){

      nextRe[i] = tempRe[i] - 2*( alpha*(tempIm[i+1]-tempIm[i-1]) -2*(alpha + ( FLOAT V(pos[i]) *dt )*tempIm[i]) );

    }

    for(j=1;j<x_points-1;j++){

      nextIm[j] = tempIm[i] - 2*( alpha*(nextRe[i+1]-nextRe[i-1]) -2*(alpha + ( FLOAT V(pos[i]) *dt )*nextRe[i]) );

    }

    copy(tempRe, nextRe, x_points);
    copy(tempIm, nextIm, x_points);

    RHO[k] = (tempRe[k]*next[k])+pow(tempIm[k], 2);
    fprintf("%f, %f\ n", RHO[k], pos[k] );

  }

  return 0;

}

/* ============================================================================= */ 

/* Definicion del potencial */

FLOAT V(FLOAT pos){

  return 0.5*(pos**2);

}

/* Definicion de la funcion de copiado */

void copy(FLOAT *A1, FLOAT *A2, int x_points){

  int i = 0;
  for(i=0; i<n_points; i++){

    A1[i] = A2[i];
  }
}

/* Definicion de la condicion inicial */

void init_cond(FLOAT* pos, FLOAT* Re, FLOAT* Im, int x_points, FLOAT dx){

  FLOAT C = exp(-0.5* (((pos-5)/SIGMA)**2) );
  FLOAT steps = 0.0;
  int i = 0;
  for(i=0;i<x_points;i++){

    Re[i] = C * cos(K * PI * steps);
    Im[i] = C * sin(K * PI * steps);
    steps += dx;

  }

}
