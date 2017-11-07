#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

void numerov(double x0, double v, double s, double w, double tf)
{
  double x_n1, x_n, x_n0, t;
  int c=0;

  ofstream numerov("Numerov.dat");
  t=0;

  while(t < tf)
    {
      if(c==0)
	{
	  x_n1 = (x0*(1+(w*w*s*s)/3.)+s*v)/(1-(w*w/6.)*s*s);
	  x_n=x_n1;
	  x_n0=x0;
	  c++;
	}
  
  
      x_n1=(2*x_n*(1-(5/12.)*s*s*w*w)-x_n0*(1+(1/12.)*s*s*w*w))/(1+(1/12.)*s*s*w*w);
      t = t+s;
      x_n0=x_n;
      x_n=x_n1;
      
      numerov << t << " " << x_n1 << endl;	    
      c=1;
    }
  
  c=0; 

}

int main ()
{
  double x0, v, w, tf;
  double s = 0.1;
  
  cout << "\x1b[1;31m" << "*** Bem-vindo ao paraíso utilizador ***\n" << endl;

  cout << "\x1b[1;31m" << "Introduza w \x1b[37m" << endl;
  cin >> w;

  cout << "\x1b[1;31m" << "Introduza as condições iniciais (x0 e v0 por esta ordem)\x1b[37m" << endl;
  cin >> x0;
  cin >> v;

  cout << "\x1b[1;31m" << "Introduza o instante final da simulação \x1b[37m" << endl;
  cin >> tf;

  numerov(x0, v, s, w, tf);

  return 0;

}