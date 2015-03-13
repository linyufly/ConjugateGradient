// Author: Mingcheng Chen (linyufly@gmail.com)

#include "math.h"

#include "sparse_matrix.h"

#include <algorithm>

namespace {

// Multiply A^tA with b.
void multiply_ata_b(
    const SparseMatrix &a_trans, const SparseMatrix &a,
    const double *b, double *c) {
  double *temp = new double[a.get_num_rows()];

  a.multiply_column(b, temp);
  a_trans.multiply_column(temp, c);

  delete [] temp;
}

double inner_product(const double *a, const double *b, int n) {
  double result = 0.0;
  for (int c = 0; c < n; c++) {
    result += a[c] * b[c];
  }
  return result;
}

void add(const double *a, const double *b, double beta, int n, double *c) {
  for (int i = 0; i < n; i++) {
    c[i] = a[i] - b[i] * beta;
  }
}

}

static void Math::conjugate_gradient(
    const SparseMatrix &a, const double *b, int num_iterations, double *x) {
  SparseMatrix a_trans = a.transpose();

  double *a_trans_b = new double[a_trans.get_num_rows()];
  a_trans.multiply_column(b, a_trans_b);

  // Solve a_trans * a * x = a_trans_b.
  double *r = new double[a_trans.get_num_rows()];
  double *p = new double[a_trans.get_num_rows()];

  double *temp = new double[a_trans.get_num_rows()];

  // temp = A'A * x
  multiply_ata_b(a_trans, a, x, temp);

  // r = A'b - temp
  add(a_trans_b, temp, -1.0, a_trans.get_num_rows(), r);

  // p = r
  std::copy(r, r + a_trans.get_num_rows(), p); 

  // rs_old = r' * r
  double rs_old = inner_product(r, r, a_trans.get_num_rows());

  for (int iteration = 0; iteration < num_iterations; iteration++) {
    // temp = A'A * p
    multiply_ata_b(a_trans, a, p, temp);

    // alpha = rs_old / (p' * temp)
    double alpha = rs_old / inner_product(p, temp, a_trans.get_num_rows());

    // x = x + alpha * p
    add(
  }

  delete [] r;
  delete [] p;
  delete [] temp;
  delete [] a_trans_b;
}

