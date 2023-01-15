#include <check.h>
#include <math.h>
#include <stdio.h>

#include "s21_matrix.h"

// <=== TEST CASES: s21_create_matrix ===>

START_TEST(tc_create_matrix_1) {
    matrix_t m;
    int result = s21_create_matrix(5, 7, &m);

    ck_assert_int_eq(m.columns, 7);
    ck_assert_int_eq(m.rows, 5);
    ck_assert_int_eq(result, 0);
    
    s21_remove_matrix(&m);
}
END_TEST

START_TEST(tc_create_matrix_2) {
    matrix_t m;
    int result = s21_create_matrix(1, 1, &m);

    ck_assert_int_eq(m.columns, 1);
    ck_assert_int_eq(m.rows, 1);
    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&m);
}
END_TEST

START_TEST(tc_create_matrix_3) {
    matrix_t m;
    int result = s21_create_matrix(100, 100, &m);

    ck_assert_int_eq(m.columns, 100);
    ck_assert_int_eq(m.rows, 100);
    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&m);
}
END_TEST

START_TEST(tc_create_matrix_4) {
    matrix_t m;
    int result = s21_create_matrix(0, 10, &m);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(tc_create_matrix_5) {
    matrix_t m;
    int result = s21_create_matrix(2, 0, &m);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(tc_create_matrix_6) {
    matrix_t m;
    int result = s21_create_matrix(-1, 0, &m);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(tc_create_matrix_7) {
    matrix_t m;
    int result = s21_create_matrix(0, 0, &m);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(tc_create_matrix_8) {
    matrix_t m;
    int result = s21_create_matrix(-10, -10, &m);
    ck_assert_int_eq(result, 1);
}
END_TEST

// <=== TEST CASES: s21_eq_matrix ===>

START_TEST(tc_eq_matrix_1) {
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
    ck_assert_double_eq(a.matrix[0][0], b.matrix[0][0]);
    ck_assert_double_eq(a.matrix[0][1], b.matrix[0][1]);
    ck_assert_double_eq(a.matrix[1][0], b.matrix[1][0]);
    ck_assert_double_eq(a.matrix[0][1], b.matrix[0][1]);
    ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
    s21_remove_matrix(&a);
    s21_remove_matrix(&b);
}
END_TEST

START_TEST(tc_eq_matrix_2) {
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

    ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
    s21_remove_matrix(&a);
    s21_remove_matrix(&b);
}
END_TEST

START_TEST(tc_eq_matrix_3) {
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

    ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
    s21_remove_matrix(&a);
    s21_remove_matrix(&b);
}
END_TEST

// <=== TEST CASES: s21_sum_matrix ===>

START_TEST(tc_sum_matrix_1) {
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
      ck_assert_int_eq(result.matrix[i][j],
                       matrix2.matrix[i][j] + matrix1.matrix[i][j]);
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(tc_sum_matrix_2) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  s21_create_matrix(3, 3, &result);
  int ret = s21_sum_matrix(&matrix1, &matrix2, &result);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(tc_sum_matrix_3) {
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
    ck_assert_double_eq(a.matrix[0][0] + b.matrix[0][0], c.matrix[0][0]);
    ck_assert_double_eq(a.matrix[0][1] + b.matrix[0][1], c.matrix[0][1]);
    ck_assert_double_eq(a.matrix[1][0] + b.matrix[1][0], c.matrix[1][0]);
    ck_assert_double_eq(a.matrix[1][1] + b.matrix[1][1], c.matrix[1][1]);
    s21_remove_matrix(&a);
    s21_remove_matrix(&b);
    s21_remove_matrix(&c);
}
END_TEST

START_TEST(tc_sum_matrix_4) {
  matrix_t matrix1, matrix2, result;
  matrix1.matrix = NULL;
  // s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  s21_create_matrix(3, 3, &result);
  int ret = s21_sum_matrix(&matrix1, &matrix2, &result);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

// START_TEST(tc_sum_matrix_5) {
//   matrix_t matrix1, matrix2, result;
//   s21_create_matrix(-1, 3, &matrix1);
//   s21_create_matrix(-1, 3, &matrix2);
//   int ret = s21_sum_matrix(&matrix1, &matrix2, &result);
//   ck_assert_int_eq(ret, 2);
// }
// END_TEST

// <=== TEST CASES: s21_sub_matrix ===>

START_TEST(tc_sub_matrix_1) {
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
      ck_assert_double_eq_tol(result.matrix[i][j],
                              matrix2.matrix[i][j] - matrix1.matrix[i][j],
                              1e-6);
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(tc_sub_matrix_2) {
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
    ck_assert_double_eq(a.matrix[0][0] - b.matrix[0][0], c.matrix[0][0]);
    ck_assert_double_eq(a.matrix[0][1] - b.matrix[0][1], c.matrix[0][1]);
    ck_assert_double_eq(a.matrix[1][0] - b.matrix[1][0], c.matrix[1][0]);
    ck_assert_double_eq(a.matrix[1][1] - b.matrix[1][1], c.matrix[1][1]);
    s21_remove_matrix(&a);
    s21_remove_matrix(&b);
    s21_remove_matrix(&c);
}
END_TEST

START_TEST(tc_sub_matrix_3) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  s21_create_matrix(3, 3, &result);
  int ret = s21_sub_matrix(&matrix1, &matrix2, &result);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(tc_sub_matrix_4) {
  matrix_t matrix1, matrix2, result;
  matrix1.matrix = NULL;
  // s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(3, 3, &matrix2);
  s21_create_matrix(3, 3, &result);
  int ret = s21_sub_matrix(&matrix1, &matrix2, &result);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(tc_sub_matrix_5) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(-1, 3, &matrix1);
  s21_create_matrix(-1, 3, &matrix2);
  int ret = s21_sub_matrix(&matrix1, &matrix2, &result);
  ck_assert_int_eq(ret, 2);
}
END_TEST

// <=== TEST CASES: s21_mult_number ===>

START_TEST(tc_mult_number_1) {
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
      ck_assert_double_eq_tol(result.matrix[i][j], matrix1.matrix[i][j] * 2,
                              1e-6);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tc_mult_number_2) {
  matrix_t matrix1, result;
  s21_create_matrix(-1, 3, &matrix1);

  int ret = s21_mult_number(&matrix1, 2, &result);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(tc_mult_number_3) {
  matrix_t matrix1, result;
  matrix1.matrix = NULL;
  int ret = s21_mult_number(&matrix1, 2, &result);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix1);
}
END_TEST

// <=== TEST CASES: s21_mult_mutrix ===>

START_TEST(tc_mult_matrix_1) {
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
      
      ck_assert_double_eq_tol(result.matrix[i][j], calculated_mat.matrix[i][j],
                              1e-01);
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&calculated_mat);
}
END_TEST

START_TEST(tc_mult_matrix_2) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(4, 3, &matrix2);
  s21_create_matrix(3, 3, &result);
  int ret = s21_mult_matrix(&matrix1, &matrix2, &result);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(tc_mult_matrix_3) {
  matrix_t matrix1, matrix2, result;
  matrix1.matrix = NULL;
  s21_create_matrix(3, 3, &matrix2);
  s21_create_matrix(3, 3, &result);
  int ret = s21_mult_matrix(&matrix1, &matrix2, &result);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(tc_mult_matrix_4) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(-1, 3, &matrix1);
  s21_create_matrix(-1, 3, &matrix2);
  int ret = s21_mult_matrix(&matrix1, &matrix2, &result);
  ck_assert_int_eq(ret, 2);
}
END_TEST

// <=== TEST CASES: s21_transpose ===>

START_TEST(tc_transpose_1) {
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
      ck_assert_double_eq_tol(result.matrix[i][j], matrix2.matrix[i][j], 1e-6);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(tc_transpose_2) {
  matrix_t matrix1, result;
  matrix1.matrix = NULL;

  int ret = s21_transpose(&matrix1, &result);
  ck_assert_int_eq(ret, 1);

}
END_TEST

START_TEST(tc_transpose_3) {
  matrix_t matrix1, result;
  s21_create_matrix(-1, 3, &matrix1);
  int ret = s21_transpose(&matrix1, &result);
  ck_assert_int_eq(ret, 1);
}
END_TEST

// <=== TEST CASES: s21_calc_complements ===>

START_TEST(tc_calc_complements_1) {
  matrix_t matrix1, result;
  s21_create_matrix(3, 2, &matrix1);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  int ret = s21_calc_complements(&matrix1, &result);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&matrix1);

  s21_create_matrix(3, 3, &matrix1);
  k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  ret = s21_calc_complements(&matrix1, &result);
  ck_assert_int_eq(ret, 0);
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
  ret = s21_calc_complements(&matrix1, &result);
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
      ck_assert_double_eq(result.matrix[i][j], expected.matrix[i][j]);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(tc_calc_complements_2) {
  matrix_t matrix1, result;
  matrix1.matrix = NULL;

  int ret = s21_calc_complements(&matrix1, &result);
  ck_assert_int_eq(ret, 1);

}
END_TEST

START_TEST(tc_calc_complements_3) {
  matrix_t matrix1, result;
  s21_create_matrix(-1, 3, &matrix1);
  int ret = s21_calc_complements(&matrix1, &result);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(tc_calc_complements_4) {
  matrix_t matrix1, result;
  s21_create_matrix(1, 1, &matrix1);
  matrix1.matrix[0][0] = 13;

  int ret = s21_calc_complements(&matrix1, &result);
  ck_assert_int_eq(ret, 0);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq(result.matrix[0][0], 13);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}
END_TEST

// <=== TEST CASES: s21_determinant ===>

START_TEST(tc_determinant_1) {
  matrix_t matrix1;
  s21_create_matrix(3, 2, &matrix1);
  int k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  double res;
  int ret = s21_determinant(&matrix1, &res);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&matrix1);

  s21_create_matrix(3, 3, &matrix1);
  k = 0;
  for (int i = 0; i < matrix1.rows; i++) {
    for (int j = 0; j < matrix1.columns; j++) {
      matrix1.matrix[i][j] = k++;
    }
  }
  ret = s21_determinant(&matrix1, &res);
  ck_assert_int_eq(ret, 0);
  ck_assert_double_eq(res, 0);
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

  ret = s21_determinant(&matrix1, &res);
  ck_assert_int_eq(ret, 0);
  ck_assert_double_eq(res, 324);
  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(tc_determinant_2) {
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

  int res = s21_determinant(&A, &determinant_result);

  double determinant_orig = -253234.0;

  ck_assert_double_eq(determinant_result, determinant_orig);
  ck_assert_int_eq(res, OK);


  s21_remove_matrix(&A);
}
END_TEST

START_TEST(tc_determinant_3) {
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

  int res = s21_determinant(&A, &determinant_result);

  double determinant_orig = 262542193.0;

  ck_assert_double_eq(determinant_result, determinant_orig);
  ck_assert_int_eq(res, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(tc_determinant_4) {
  matrix_t matrix1;
  double result;
  matrix1.matrix = NULL;

  int ret = s21_determinant(&matrix1, &result);
  ck_assert_int_eq(ret, 1);

}
END_TEST

// <=== TEST CASES: s21_inverse_matrix ===>

START_TEST(tc_inverse_matrix_1) {
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
      ck_assert_double_eq(expected_result.matrix[i][j],
                          actual_result.matrix[i][j]);
    }
  }
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(tc_inverse_matrix_2) {
  matrix_t matrix1, result;
  s21_create_matrix(2, 3, &matrix1);

  int ret = s21_inverse_matrix(&matrix1, &result);
  ck_assert_int_eq(ret, 2);
  // s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);

}
END_TEST

START_TEST(tc_inverse_matrix_3) {
  matrix_t matrix1, result;
  matrix1.matrix = NULL;
  s21_create_matrix(3, 3, &result);
  int ret = s21_inverse_matrix(&matrix1, &result);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix1);

}
END_TEST

START_TEST(tc_inverse_matrix_4) {
  matrix_t matrix1, result;
  s21_create_matrix(-1, 3, &matrix1);

  int ret = s21_inverse_matrix(&matrix1, &result);
  ck_assert_int_eq(ret, 2);
}
END_TEST

START_TEST(tc_inverse_matrix_5) {
  matrix_t src;
  s21_create_matrix(2, 2, &src);
  src.matrix[0][0] = 2.0;
  src.matrix[0][1] = 3.0;
  src.matrix[1][0] = -5.0;
  src.matrix[1][1] = -7.5;
  matrix_t inv;
  int status = s21_inverse_matrix(&src, &inv);
  ck_assert_int_eq(status, ERR_CALC);
  s21_remove_matrix(&src);
}
END_TEST

Suite *ts_create_matrix() {
  Suite *suite = suite_create("ts_create_matrix");
  TCase *test_case = tcase_create("tc_create_matrix");

  tcase_add_test(test_case, tc_create_matrix_1);
  tcase_add_test(test_case, tc_create_matrix_2);
  tcase_add_test(test_case, tc_create_matrix_3);
  tcase_add_test(test_case, tc_create_matrix_4);
  tcase_add_test(test_case, tc_create_matrix_5);
  tcase_add_test(test_case, tc_create_matrix_6);
  tcase_add_test(test_case, tc_create_matrix_7);
  tcase_add_test(test_case, tc_create_matrix_8);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_eq_matrix() {
  Suite *suite = suite_create("ts_eq_matrix");
  TCase *test_case = tcase_create("tc_eq_matrix");

  tcase_add_test(test_case, tc_eq_matrix_1);
  tcase_add_test(test_case, tc_eq_matrix_2);
  tcase_add_test(test_case, tc_eq_matrix_3);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_sum_matrix() {
  Suite *suite = suite_create("ts_sum_matrix");
  TCase *test_case = tcase_create("tc_sum_matrix");

  tcase_add_test(test_case, tc_sum_matrix_1);
  tcase_add_test(test_case, tc_sum_matrix_2);
  tcase_add_test(test_case, tc_sum_matrix_3);
  tcase_add_test(test_case, tc_sum_matrix_4);
  // tcase_add_test(test_case, tc_sum_matrix_5);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_sub_matrix() {
  Suite *suite = suite_create("ts_sub_matrix");
  TCase *test_case = tcase_create("tc_sub_matrix");

  tcase_add_test(test_case, tc_sub_matrix_1);
  tcase_add_test(test_case, tc_sub_matrix_2);
  tcase_add_test(test_case, tc_sub_matrix_3);
  tcase_add_test(test_case, tc_sub_matrix_4);
  tcase_add_test(test_case, tc_sub_matrix_5);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_mult_number() {
  Suite *suite = suite_create("ts_mult_number");
  TCase *test_case = tcase_create("tc_mult_number");

  tcase_add_test(test_case, tc_mult_number_1);
  tcase_add_test(test_case, tc_mult_number_2);
  tcase_add_test(test_case, tc_mult_number_3);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_mult_matrix() {
  Suite *suite = suite_create("ts_mult_matrix");
  TCase *test_case = tcase_create("tc_mult_matrix");

  tcase_add_test(test_case, tc_mult_matrix_1);
  tcase_add_test(test_case, tc_mult_matrix_2);
  tcase_add_test(test_case, tc_mult_matrix_3);
  tcase_add_test(test_case, tc_mult_matrix_4);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_transpose() {
  Suite *suite = suite_create("ts_transpose");
  TCase *test_case = tcase_create("tc_transpose");

  tcase_add_test(test_case, tc_transpose_1);
  tcase_add_test(test_case, tc_transpose_2);
  tcase_add_test(test_case, tc_transpose_3);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_calc_complements() {
  Suite *suite = suite_create("ts_calc_complements");
  TCase *test_case = tcase_create("tc_calc_complements");

  tcase_add_test(test_case, tc_calc_complements_1);
  tcase_add_test(test_case, tc_calc_complements_2);
  tcase_add_test(test_case, tc_calc_complements_3);
  tcase_add_test(test_case, tc_calc_complements_4);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_determinant() {
  Suite *suite = suite_create("ts_determinant");
  TCase *test_case = tcase_create("tc_determinant");

  tcase_add_test(test_case, tc_determinant_1);
  tcase_add_test(test_case, tc_determinant_2);
  tcase_add_test(test_case, tc_determinant_3);
  tcase_add_test(test_case, tc_determinant_4);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_inverse_matrix() {
  Suite *suite = suite_create("ts_inverse_matrix");
  TCase *test_case = tcase_create("tc_inverse_matrix");

  tcase_add_test(test_case, tc_inverse_matrix_1);
  tcase_add_test(test_case, tc_inverse_matrix_2);
  tcase_add_test(test_case, tc_inverse_matrix_3);
  tcase_add_test(test_case, tc_inverse_matrix_4);
  tcase_add_test(test_case, tc_inverse_matrix_5);

  suite_add_tcase(suite, test_case);

  return suite;
}

int main(void) {
  Suite *test_suites[] = {ts_create_matrix(),
                          ts_eq_matrix(),
                          ts_sum_matrix(),
                          ts_sub_matrix(),
                          ts_mult_number(),
                          ts_mult_matrix(),
                          ts_transpose(),
                          ts_calc_complements(),
                          ts_determinant(),
                          ts_inverse_matrix(),
                          NULL};
  int failed = 0;

  for (Suite **s = test_suites; *s != NULL; s++) {
    SRunner *runner = srunner_create(*s);
    srunner_run_all(runner, CK_NORMAL);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return failed;
}