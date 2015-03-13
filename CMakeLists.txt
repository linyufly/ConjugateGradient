cmake_minimum_required(VERSION 2.8)

project(ConjugateGradient)

add_executable(SparseMatrixTest sparse_matrix_test.cc
                                sparse_matrix.cc)

add_executable(MathTest math_test.cc
                        math.cc
                        sparse_matrix.cc)
