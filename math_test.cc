// Author: Mingcheng Chen (linyufly@gmail.com)

#include "math.h"

#include "sparse_matrix.h"

#include <cstdio>

#include <vector>

void conjugate_gradient_test() {
  printf("conjugate_gradient_test {\n");

  SparseMatrix a(4, 2);
  a.set_element(0, 0, 1.0);
  a.set_element(0, 1, 2.0);

  a.set_element(1, 0, 2.0);
  a.set_element(1, 1, -3.0);

  a.set_element(2, 0, 4.0);
  a.set_element(2, 1, -1.0);

  a.set_element(3, 0, -5.0);
  a.set_element(3, 1, 2.0);

  // Suppose solution is (2, 3).
  std::vector<double> b(4);
  b[0] = 3.0;  // 8.0
  b[1] = 2.0;  // -5.0
  b[2] = -4.0;
  b[3] = 5.0;

  std::vector<double> x(2);
  x[0] = x[1] = 0.0;

  Math::conjugate_gradient(a, &b[0], 2, &x[0]);

  std::vector<double> c(4);
  a.multiply_column(&x[0], &c[0]);

  printf("x: %lf %lf\n", x[0], x[1]);

  for (int i = 0; i < 4; i++) {
    printf(" %lf(%lf)", c[i], b[i]);
  }
  printf("\n");

  printf("} conjugate_gradient_test\n");
}

int main() {
  conjugate_gradient_test();

  return 0;
}

