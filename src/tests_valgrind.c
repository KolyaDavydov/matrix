
#include <math.h>
#include <stdio.h>

#include "s21_matrix.h"

// <=== TEST CASES: s21_create_matrix ===>

void tc_create_matrix_1() {
  matrix_t m;
  s21_create_matrix(5, 7, &m);

  s21_remove_matrix(&m);
}

void tc_create_matrix_2() {
  matrix_t m;
  s21_create_matrix(1, 1, &m);

  s21_remove_matrix(&m);
}

void tc_create_matrix_3() {
  matrix_t m;
  s21_create_matrix(100, 100, &m);

  s21_remove_matrix(&m);
}

void tc_create_matrix_4() {
  matrix_t m;
  s21_create_matrix(0, 10, &m);
}

void tc_create_matrix_5() {
  matrix_t m;
  s21_create_matrix(2, 0, &m);
}

void tc_create_matrix_6() {
  matrix_t m;
  s21_create_matrix(-1, 0, &m);
}

void tc_create_matrix_7() {
  matrix_t m;
  s21_create_matrix(0, 0, &m);
}

void tc_create_matrix_8() {
  matrix_t m;
  s21_create_matrix(-10, -10, &m);
}

// <=== TEST CASES: s21_eq_matrix ===>

void tc_eq_matrix_1() {
  matrix_t a;
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 1234.1234567;
  a.matrix[0][1] = 1234.1234;
  a.matrix[1][0] = 1234.1234;
  a.matrix[1][1] = 1234.1234;
  matrix_t b;
  s21_create_matrix(2, 2, &b);
  b.matrix[0][0] = 1234.1234567;
  b.matrix[0][1] = 1234.1234;
  b.matrix[1][0] = 1234.1234;
  b.matrix[1][1] = 1234.1234;

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}

void tc_eq_matrix_2() {
  matrix_t a;
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 1234.1234567;
  a.matrix[0][1] = 1234.1234;
  a.matrix[1][0] = 1234.1234;
  a.matrix[1][1] = 1234.1234;
  matrix_t b;
  s21_create_matrix(1, 2, &b);
  b.matrix[0][0] = 1234.1234567;
  b.matrix[0][1] = 1234.1234;

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}

void tc_eq_matrix_3() {
  matrix_t a;
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 1234.1234567;
  a.matrix[0][1] = 1234.1234;
  a.matrix[1][0] = 1234.1234;
  a.matrix[1][1] = 1234.1234;
  matrix_t b;
  s21_create_matrix(2, 2, &b);
  b.matrix[0][0] = -1234.1234567;
  b.matrix[0][1] = 1234.1234;
  b.matrix[1][0] = 1234.1234;
  b.matrix[1][1] = 1234.1234;

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}

// <=== TEST CASES: s21_sum_matrix ===>

void tc_sum_matrix_1() {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  k = 0;
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] = k++;
    }
  }
  s21_sum_matrix(&matrix2, &matrix1, &result);
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

void tc_sum_matrix_2() {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  // s21_create_matrix(3, 3, &result);
  s21_sum_matrix(&matrix1, &matrix2, &result);

  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

void tc_sum_matrix_3() {
  matrix_t a;
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 1.1;
  a.matrix[0][1] = 2.2;
  a.matrix[1][0] = 3.3;
  a.matrix[1][1] = 4.4;
  matrix_t b;
  s21_create_matrix(2, 2, &b);
  b.matrix[0][0] = 4.4;
  b.matrix[0][1] = 3.3;
  b.matrix[1][0] = 2.2;
  b.matrix[1][1] = 1.1;
  matrix_t c;
  s21_sum_matrix(&a, &b, &c);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
}

void tc_sum_matrix_4() {
  matrix_t matrix1, matrix2, result;
  matrix1.matrix = NULL;
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  s21_sum_matrix(&matrix1, &matrix2, &result);

  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

void tc_sum_matrix_5() {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(-1, 3, &matrix1);
  s21_create_matrix(-1, 3, &matrix2);
  s21_sum_matrix(&matrix1, &matrix2, &result);
}

// <=== TEST CASES: s21_sub_matrix ===>

void tc_sub_matrix_1() {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  k = 0;
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
      matrix2.matrix[i][j] = k++;
    }
  }
  s21_sub_matrix(&matrix2, &matrix1, &result);
  for (int i = 0; i < matrix2.rows; i++) {
    for (int j = 0; j < matrix2.columns; j++) {
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

void tc_sub_matrix_2() {
  matrix_t a;
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 1.1;
  a.matrix[0][1] = 2.2;
  a.matrix[1][0] = 3.3;
  a.matrix[1][1] = 4.4;
  matrix_t b;
  s21_create_matrix(2, 2, &b);
  b.matrix[0][0] = 4.4;
  b.matrix[0][1] = 3.3;
  b.matrix[1][0] = 2.2;
  b.matrix[1][1] = 1.1;
  matrix_t c;
  s21_sub_matrix(&a, &b, &c);

  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&c);
}

void tc_sub_matrix_3() {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  s21_sub_matrix(&matrix1, &matrix2, &result);

  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

void tc_sub_matrix_4() {
  matrix_t matrix1, matrix2, result;
  matrix1.matrix = NULL;
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  s21_sub_matrix(&matrix1, &matrix2, &result);

  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

void tc_sub_matrix_5() {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(-1, 3, &matrix1);
  s21_create_matrix(-1, 3, &matrix2);
  s21_sub_matrix(&matrix1, &matrix2, &result);
}

// <=== TEST CASES: s21_mult_number ===>

void tc_mult_number_1() {
  matrix_t matrix1, result;
  s21_create_matrix(3, 3, &matrix1);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }

  s21_mult_number(&matrix1, 2, &result);
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}

void tc_mult_number_2() {
  matrix_t matrix1, result;
  s21_create_matrix(-1, 3, &matrix1);

  s21_mult_number(&matrix1, 2, &result);
}

void tc_mult_number_3() {
  matrix_t matrix1, result;
  matrix1.matrix = NULL;
  s21_mult_number(&matrix1, 2, &result);

  s21_remove_matrix(&matrix1);
}

// <=== TEST CASES: s21_mult_mutrix ===>

void tc_mult_matrix_1() {
  matrix_t matrix1;
  matrix_t matrix2;

  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);

  matrix1.matrix[0][0] = 5.474748;
  matrix1.matrix[0][1] = -23.365346;
  matrix1.matrix[0][2] = 7.464645;
  matrix1.matrix[1][0] = 13.235363;
  matrix1.matrix[1][1] = -17.326774;
  matrix1.matrix[1][2] = -0.000034;
  matrix1.matrix[2][0] = -12.235567;
  matrix1.matrix[2][1] = 11.124526;
  matrix1.matrix[2][2] = 5.325634;

  matrix2.matrix[0][0] = 15.352534;
  matrix2.matrix[0][1] = 143.532636;
  matrix2.matrix[0][2] = 345.35356;
  matrix2.matrix[1][0] = 124.523552;
  matrix2.matrix[1][1] = -654.234562;
  matrix2.matrix[1][2] = 123.353578;
  matrix2.matrix[2][0] = -245.636465;
  matrix2.matrix[2][1] = 6324.235523;
  matrix2.matrix[2][2] = -2353.632542;
  matrix_t result;
  s21_mult_matrix(&matrix1, &matrix2, &result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  matrix_t calculated_mat;
  s21_create_matrix(3, 3, &calculated_mat);
  calculated_mat.matrix[0][0] = -4659.06324085756;
  calculated_mat.matrix[0][1] = 63280.3476665598;
  calculated_mat.matrix[0][2] = -18560.480561482;
  calculated_mat.matrix[1][0] = -1954.3776969092;
  calculated_mat.matrix[1][1] = 13235.232153486;
  calculated_mat.matrix[1][2] = 2433.63942021;
  calculated_mat.matrix[2][0] = -110.749147819;
  calculated_mat.matrix[2][1] = 24646.32859501;
  calculated_mat.matrix[2][2] = -15387.89622285;

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&calculated_mat);
}

void tc_mult_matrix_2() {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(4, 3, &matrix2);
  s21_mult_matrix(&matrix1, &matrix2, &result);

  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

void tc_mult_matrix_3() {
  matrix_t matrix1, matrix2, result;
  matrix1.matrix = NULL;
  s21_create_matrix(3, 3, &matrix2);
  s21_mult_matrix(&matrix1, &matrix2, &result);

  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}

void tc_mult_matrix_4() {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(-1, 3, &matrix1);
  s21_create_matrix(-1, 3, &matrix2);
  s21_mult_matrix(&matrix1, &matrix2, &result);
}

// <=== TEST CASES: s21_transpose ===>

void tc_transpose_1() {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  matrix2.matrix[0][0] = 0;
  matrix2.matrix[0][1] = 3;
  matrix2.matrix[0][2] = 6;
  matrix2.matrix[1][0] = 1;
  matrix2.matrix[1][1] = 4;
  matrix2.matrix[1][2] = 7;
  matrix2.matrix[2][0] = 2;
  matrix2.matrix[2][1] = 5;
  matrix2.matrix[2][2] = 8;
  s21_transpose(&matrix1, &result);
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}

void tc_transpose_2() {
  matrix_t matrix1, result;
  matrix1.matrix = NULL;

  s21_transpose(&matrix1, &result);
}

void tc_transpose_3() {
  matrix_t matrix1, result;
  s21_create_matrix(-1, 3, &matrix1);
  s21_transpose(&matrix1, &result);
}

// <=== TEST CASES: s21_calc_complements ===>

void tc_calc_complements_1() {
  matrix_t matrix1, result;
  s21_create_matrix(3, 2, &matrix1);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  s21_calc_complements(&matrix1, &result);

  s21_remove_matrix(&matrix1);

  s21_create_matrix(3, 3, &matrix1);
  k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  s21_calc_complements(&matrix1, &result);

  s21_remove_matrix(&matrix1);

  s21_remove_matrix(&result);
  s21_create_matrix(3, 3, &matrix1);
  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;

  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 2;

  matrix1.matrix[2][0] = 5;
  matrix1.matrix[2][1] = 2;
  matrix1.matrix[2][2] = 1;
  s21_calc_complements(&matrix1, &result);
  matrix_t expected;
  s21_create_matrix(3, 3, &expected);
  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;

  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;

  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}

void tc_calc_complements_2() {
  matrix_t matrix1, result;
  matrix1.matrix = NULL;

  s21_calc_complements(&matrix1, &result);
}

void tc_calc_complements_3() {
  matrix_t matrix1, result;
  s21_create_matrix(-1, 3, &matrix1);
  s21_calc_complements(&matrix1, &result);
}

void tc_calc_complements_4() {
  matrix_t matrix1, result;
  s21_create_matrix(1, 1, &matrix1);
  matrix1.matrix[0][0] = 13;

  s21_calc_complements(&matrix1, &result);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}

// <=== TEST CASES: s21_determinant ===>

void tc_determinant_1() {
  matrix_t matrix1;
  s21_create_matrix(3, 2, &matrix1);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  double res;
  s21_determinant(&matrix1, &res);

  s21_remove_matrix(&matrix1);

  s21_create_matrix(3, 3, &matrix1);
  k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  s21_determinant(&matrix1, &res);

  s21_remove_matrix(&matrix1);

  s21_create_matrix(3, 3, &matrix1);
  matrix1.matrix[0][0] = 0;
  matrix1.matrix[0][1] = 9;
  matrix1.matrix[0][2] = 5;

  matrix1.matrix[1][0] = 4;
  matrix1.matrix[1][1] = 3;
  matrix1.matrix[1][2] = -5;

  matrix1.matrix[2][0] = -1;
  matrix1.matrix[2][1] = 6;
  matrix1.matrix[2][2] = -4;

  s21_determinant(&matrix1, &res);

  s21_remove_matrix(&matrix1);
}

void tc_determinant_2() {
  matrix_t A;
  s21_create_matrix(4, 4, &A);

  double determinant_result;

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 10;
  A.matrix[0][2] = 9;
  A.matrix[0][3] = 5;

  A.matrix[1][0] = 10;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 3;
  A.matrix[1][3] = 8;

  A.matrix[2][0] = 23;
  A.matrix[2][1] = 100;
  A.matrix[2][2] = 7;
  A.matrix[2][3] = 1;

  A.matrix[3][0] = 45;
  A.matrix[3][1] = 12;
  A.matrix[3][2] = 9;
  A.matrix[3][3] = 2;

  s21_determinant(&A, &determinant_result);

  // double determinant_orig = -253234.0;

  s21_remove_matrix(&A);
}

void tc_determinant_3() {
  matrix_t A;
  s21_create_matrix(5, 5, &A);

  double determinant_result;

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 10;
  A.matrix[0][2] = 9;
  A.matrix[0][3] = 5;
  A.matrix[0][4] = 100;

  A.matrix[1][0] = 10;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 3;
  A.matrix[1][3] = 8;
  A.matrix[1][4] = 12;

  A.matrix[2][0] = 23;
  A.matrix[2][1] = 100;
  A.matrix[2][2] = 7;
  A.matrix[2][3] = 1;
  A.matrix[2][4] = 7;

  A.matrix[3][0] = 45;
  A.matrix[3][1] = 12;
  A.matrix[3][2] = 9;
  A.matrix[3][3] = 2;
  A.matrix[3][4] = 0;

  A.matrix[4][0] = 4;
  A.matrix[4][1] = 2;
  A.matrix[4][2] = 91;
  A.matrix[4][3] = 20;
  A.matrix[4][4] = 6;

  s21_determinant(&A, &determinant_result);

  // double determinant_orig = 262542193.0;

  s21_remove_matrix(&A);
}

void tc_determinant_4() {
  matrix_t matrix1;
  double result;
  matrix1.matrix = NULL;

  s21_determinant(&matrix1, &result);
}

// <=== TEST CASES: s21_inverse_matrix ===>

void tc_inverse_matrix_1() {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;

  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  matrix_t expected_result;
  s21_create_matrix(3, 3, &expected_result);

  expected_result.matrix[0][0] = 1;
  expected_result.matrix[0][1] = -1;
  expected_result.matrix[0][2] = 1;

  expected_result.matrix[1][0] = -38;
  expected_result.matrix[1][1] = 41;
  expected_result.matrix[1][2] = -34;

  expected_result.matrix[2][0] = 27;
  expected_result.matrix[2][1] = -29;
  expected_result.matrix[2][2] = 24;

  matrix_t actual_result;
  s21_inverse_matrix(&A, &actual_result);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
    }
  }
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
  s21_remove_matrix(&A);
}

void tc_inverse_matrix_2() {
  matrix_t matrix1, result;
  s21_create_matrix(2, 3, &matrix1);

  s21_inverse_matrix(&matrix1, &result);

  // s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
}

void tc_inverse_matrix_3() {
  matrix_t matrix1, result;
  matrix1.matrix = NULL;
  s21_inverse_matrix(&matrix1, &result);

  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
}

void tc_inverse_matrix_4() {
  matrix_t matrix1, result;
  s21_create_matrix(-1, 3, &matrix1);

  s21_inverse_matrix(&matrix1, &result);
}

void tc_inverse_matrix_5() {
  matrix_t src;
  s21_create_matrix(2, 2, &src);
  src.matrix[0][0] = 2.0;
  src.matrix[0][1] = 3.0;
  src.matrix[1][0] = -5.0;
  src.matrix[1][1] = -7.5;
  matrix_t inv;
  s21_inverse_matrix(&src, &inv);

  s21_remove_matrix(&src);
}

int main(void) {
  tc_create_matrix_1();
  tc_create_matrix_2();
  tc_create_matrix_3();
  tc_create_matrix_4();
  tc_create_matrix_5();
  tc_create_matrix_6();
  tc_create_matrix_7();
  tc_create_matrix_8();

  tc_eq_matrix_1();
  tc_eq_matrix_2();
  tc_eq_matrix_3();

  tc_sum_matrix_1();
  tc_sum_matrix_2();
  tc_sum_matrix_3();
  tc_sum_matrix_4();
  tc_sum_matrix_5();

  tc_sub_matrix_1();
  tc_sub_matrix_2();
  tc_sub_matrix_3();
  tc_sub_matrix_4();
  tc_sub_matrix_5();

  tc_mult_number_1();
  tc_mult_number_2();
  tc_mult_number_3();

  tc_mult_matrix_1();
  tc_mult_matrix_2();
  tc_mult_matrix_3();
  tc_mult_matrix_4();

  tc_transpose_1();
  tc_transpose_2();
  tc_transpose_3();

  tc_calc_complements_1();
  tc_calc_complements_2();
  tc_calc_complements_3();
  tc_calc_complements_4();

  tc_determinant_1();
  tc_determinant_2();
  tc_determinant_3();
  tc_determinant_4();

  tc_inverse_matrix_1();
  tc_inverse_matrix_2();
  tc_inverse_matrix_3();
  tc_inverse_matrix_4();
  tc_inverse_matrix_5();

  return 0;
}