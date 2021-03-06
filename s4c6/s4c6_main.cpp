#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "s4c6_header.h"

#define GNUPLOT "gnuplot gnuplot_surface.plt"

using namespace std;

int main ()
{
  //Space Potencial(40);
  /* Definir as fronteiras */
  int N, npos;
  double a1, a2, b1, b2, c1, c2;
  double Ux_a1, Ux_a2, Uy_b1, Uy_b2, Uz_c1, Uz_c2;
  int it = 0, i = 1, j = 1, k = 1;
  double tol = 10;

  ofstream output3D("Poisson_3d_charge.dat");
  ofstream output2D ("Poisson_2d_charge.dat"); 


  cout << "*** Bem-vindo ao calculador de potenciais ***" << endl;
  cout << "Indique o número correspondente ao número de dimensões onde pretende aplicar a Eq. de Poisson \n\n   2) 2D \n   3) 3D \n" << endl;
  cin >> N;

  cout << "Qual a dimensão do espaço?" << endl;
  cin >> npos;

  Space Potencial(npos, N);

  /* 2D */

  cout << "Especifique as posições dos vértices diagonais do N-cubo: \n   2D) (a1, b1) + (a2, b2)\n   3D) (a1, b1, c1) + (a2, b2, c2):" << endl;
  cin >> a1;
  cin >> b1;
  cin >> a2;
  cin >> b2;
  
  if (N == 3){
    cin >> c1;
    cin >> c2;
  }

  if (N == 2)
    {

      if ((a2 < a1) || (b2 < b1))
	{
	  cout << "Região não aceitável. a2 > a1 e b2 > b1." << endl;
	  return 1;
	}

      cout << "Especifique o potencial na fronteira (Ux_a1, Ux_a2, Uy_b1, Uy_b2): " << endl;
      cin >> Ux_a1;
      cin >> Ux_a2;
      cin >> Uy_b1;
      cin >> Uy_b2;

      Potencial.setup(Ux_a1, Ux_a2, Uy_b1, Uy_b2, 0, 0);
      Potencial.equi_referencial(a1, a2, b1, b2, 0, 0);

      while (tol > 1e-8)
	{
	  for (i = 1; i < (Potencial.size() - 1); i++)
	    {
	      for (j = 1; j < (Potencial.size() - 1); j++) // calcular o novo campo
		{
		  Potencial.U2[i][j] = Potencial.poisson_2d(Potencial.U2[i-1][j], Potencial.U2[i+1][j], Potencial.U2[i][j-1], Potencial.U2[i][j+1], a1, b1, i, j);
		  tol = abs(Potencial.U2[i][j] - Potencial.V2[i][j]);
		  Potencial.V2[i][j] = Potencial.U2[i][j];
		}
	    }
      
	  i = 1;
	  j = 1;
	  it++; 
	}

      Potencial.print(a1, b1, 0, output2D);
      cout << "Obteve-se a melhor solução para a eq. de Poisson (2D) após " << it << " iteradas." << endl;
    }

  /* 3D */
  else if (N == 3)
    {
      if ((a2 < a1) || (b2 < b1) || (c2 < c1))
	{
	  cout << "Região não aceitável. a2 > a1, b2 > b1 ou c2 > c1." << endl;
	  return 1;
	}

      cout << "Especifique o potencial na fronteira (Ux_a1, Ux_a2, Uy_b1, Uy_b2, Uz_c1, Uz_c2): " << endl;
      cin >> Ux_a1;
      cin >> Ux_a2;
      cin >> Uy_b1;
      cin >> Uy_b2;
      cin >> Uz_c1;
      cin >> Uz_c2;

      Potencial.setup(Ux_a1, Ux_a2, Uy_b1, Uy_b2, Uz_c1, Uz_c2);
      Potencial.equi_referencial(a1, a2, b1, b2, c1, c2);

      while (tol > 1e-8)
	{
	  for (k = 1; k < (Potencial.size() - 1); k++)
	    {
	      for (i = 1; i < (Potencial.size() - 1); i++)
		{
		  for (j = 1; j < (Potencial.size() - 1); j++) // calcular o novo campo
		    {
		      Potencial.U3[i][j][k] = Potencial.poisson_3d(Potencial.U3[i-1][j][k], Potencial.U3[i+1][j][k], Potencial.U3[i][j-1][k], Potencial.U3[i][j+1][k], Potencial.U3[i][j][k-1], Potencial.U3[i][j][k+1], a1, b1, c1, i, j, k);
		      tol = abs(Potencial.U3[i][j][k] - Potencial.V3[i][j][k]);
		      Potencial.V3[i][j][k] = Potencial.U3[i][j][k];
		    }
		}
	    }
	  i = 1;
	  j = 1;
	  k = 1;
	  it++; 
	}
      
      Potencial.print(a1, b1, c1, output3D);
      cout << "Obteve-se a melhor solução para a eq. de Poisson (3D) após " << it << " iteradas." << endl;
      
    }

  else {
    cout << "Resposta Inválida! Tente de novo..." << endl;
    return 1;
  }

  output2D.close();
  output3D.close();
  //system(GNUPLOT);

  return 0;
}
