#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

class Matrix{
  size_t n, m;
  double **mat;
 public:
  explicit Matrix(size_t ncol, size_t nlin); /* Construtor por defeito */
  Matrix(const Matrix& M); /* Construtor por cópia */
  ~Matrix(); /* Destrutor */

  /* Funções que atuam sobre matrizes */
  
  void set(unsigned i, unsigned j, double a);  // definir o valor da casa ij da matriz para a
  size_t ncol() const;                         // output do numero de colunas, n
  size_t nlin() const;                         // output do numero de linhas, m
  void resize(unsigned new_n, unsigned new_m); // redimensionalizar a matriz
  Matrix inverse();

  /* Operadores */

  Matrix& operator=(const Matrix& M);
  Matrix& operator=(double a);
  Matrix operator+(const Matrix& M);
  Matrix operator*(const Matrix& M);
  double operator()(unsigned i, unsigned j) const; // output do valor da casa ij
  double& operator()(unsigned i, unsigned j);      // igual

  friend ostream& operator<<(ostream& out, const Matrix & r); // operador para a leitura
  friend Matrix solve(Matrix& A, const Matrix& b);
};

#endif
