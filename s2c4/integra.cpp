#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "s2_header.h"

using namespace std;


double integra_rect(double a, double b, int N, double (*f)(double x))
{
  double dx = (double)((b - a)/N);
  double x1, x2, x_med, sum;
  
  sum = 0;
  x1 = a;
  
  for (int i = 0; i < N; i++)
    {
      x2 = x1 + dx;
      x_med = (x1 + x2)/2;
      sum += ((*f)(x_med)) * dx;
      x1 = x2;
    }

  return sum;
}

double integra_trap(double a, double b, int N, double (*f)(double x))
{
   double dx = (double)((b - a)/N);
   double x1, x2, sum;

   sum = 0;
   x1 = a;
    
  for (int i = 0; i < N; i++)
    {
      x2 = x1 + dx;
      sum += (((*f)(x1) + (*f)(x2))/2) * dx;
      x1 = x2;
    }

  return sum;
}

double integra_simp(double a, double b, int N, double (*f)(double x))
{
  double h, sum;
  double x_med;
  double x1, x2;
  
  /*if (N % 2 != 0)
    {
      cout << "Erro no Método de Simpson. N deve ser par!" << endl;
      exit(EXIT_FAILURE);
      }*/

  h = (double)((b - a)/N);
  x_med = a + (h/2.);
  sum = 0;
  x1 = a;
  x2 = a + h;

  for (int i = 1; i <= N; i++)
    {
      sum += ((*f)(x1) + 4 * (*f)(x_med) + (*f)(x2));
      x1 += h;
      x_med = x1 + (h/2.);
      x2 += h;
    }

  return ((sum * h) / 6.);
  

}

double *markov(double (*pdf)(double x), double a, int n_conf, int m, double r)
{
  double *confs;
  double x;

  int i = 0, count = 0;
  double q0, q1;
  int last_q;
  
  double rand_step;
  double p_ratio;

  double al;

  srand(time(NULL));

  /**/

  confs = new double[n_conf];

  /**/

  /* Iniciar Markov */
  q0 = (((double)(rand())/(double)(RAND_MAX))) * (2 * a) - a;

  //cout << " Valor inicial (q0): " << q0  << endl;

  for (int j = 0; j < n_conf; j++)
    {
      while (i < m)
	{
	  rand_step =  (((double)(rand())/(double)(RAND_MAX))) * (2 * r) - r;

	  q1 = q0 + rand_step;
  
	  al = ((double)rand()/(double)(RAND_MAX));
	  p_ratio =  (((*pdf)(q1)) / ((*pdf)(q0)));

	  if (p_ratio > al)
	    {
	      q0 = q1;
	      count++;    
	    }
	  i++;
	}
      /*cout << " AL: " << al << endl; DEBUG
	cout << " Rand_step: " << rand_step << endl;*/
      cout << " Taxa de aceitação: " << (double)(count)/(double)(m) << endl;
      x = q0;
      confs[j] = x;
      i = 0;
      count = 0;
    }

  return confs;
}

double integra_montecarlo(double *confs, int n, double (*f)(double x))
{
  double sum = 0;
  
  for (int i = 0; i < n; i++)
    {
      sum += (*f)(confs[i]);
    }
  return sum / n;
}



