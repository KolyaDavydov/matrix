#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERR_INCORECT_MATRIX 1
#define ERR_CALC 2
#define SUCCESS 1
#define FAILURE 0

// #define s21_E 2.71828182845904523536

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// int s21_check_matrix(matrix_t *A);
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

void s21_create_minor_matrix_for_element(int num_row, int num_column,
                                         matrix_t *A, matrix_t *result);
double s12_minor_calculation(matrix_t *A);
int s21_matrix_check(matrix_t *A);
void s21_matrix_init_zero(matrix_t *A);

#endif // SRC_S21_MATRIX_H_
