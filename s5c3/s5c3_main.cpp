#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Matrix.h"

using namespace std;

int main()
{
  double get;

  Matrix T(5,6);
  Matrix G(3, 3);
  Matrix G_inv(3, 3);
  Matrix v(3, 1);

  ifstream input("matvec.dat");
  ofstream output("resultados.dat");
  
  srand(time(NULL));
  
  /*
  /* Definir os valores da matriz G - aleatório
  
  for (int i = 1; i <= G.nlin(); i++){
    for (int j = 1; j <= G.ncol(); j++){
      G.set(i, j, floor(((double) rand() / (double) RAND_MAX) * 10)); 
    }
    }*/
  
  
  for (int i = 1; i <= v.nlin(); i++){
    v.set(i, 1, floor(((double) rand() / (double) RAND_MAX) * 10));
  }

  for (int i = 1; i <= G.nlin(); i++){
    for (int j = 1; j <= G.ncol(); j++){
      input >> get;
      G.set(i, j, get);
    }
  }

  cout << "Matrix G:" << endl;
  cout << G;
  G_inv = G.inverse();
  cout << "Matrix G⁻¹:" << endl;
  cout << G_inv;
  output << G_inv;
  cout << "Vector v:" << endl;
  cout << v;

  cout << "Solve linear system represented by Gx = v" << endl;
  cout << "x: " << endl;;
  cout << solve(G, v);

  T.resize(3,3);
  T = 5;

  cout << "Matrix T (after resize to match G's dims):" << endl;
  cout << T;

  cout << "[G] + [T]:" << endl;
  cout << G+T;

  cout << "[G] x [v]: " << endl;
  cout << (G*v);

  cout << "[G] x [T]: " << endl;
  cout << G*T;

  cout << "T = G" << endl;
  T = G;
  cout << T;

  cout << "[G⁻¹] x [G] = Id" << endl;
  cout << (G*G_inv);

 
  return 0;
}
