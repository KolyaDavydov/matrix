#include "s21_matrix.h"

/**
 * @brief создание матрицы
 *
 * @param rows количство строк матрицы
 *
 * @param columns количество столбцов матрицы
 *
 * @param result указатель на начало матрицы
 *
 * @returns ошибка: 0 - ОК,
 * ERR_INCORECT_MATRIX (1) - неккоректная матрица,
 * ERR_CALC (2) - ошибка вычисления
 */
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = OK;
  s21_matrix_init_zero(result);
  if (rows <= 0 || columns <= 0) {
    error = ERR_INCORECT_MATRIX;
  } else {
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      result->rows = rows;
      result->columns = columns;

      for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          error = ERR_INCORECT_MATRIX;
          break;
        }
      }
    } else {
      error = ERR_INCORECT_MATRIX;
    }
  }
  return error;
}

/**
 * @brief удаление матрици, освобождение памяти
 *
 * @param A указатель на начало матрицы
 *
 */
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->columns = 0;
  A->columns = 0;
}

/**
 * @brief сравнение двух матриц с точностью до 7 знака после запятой
 *
 * @param A указатель на первую матрицу
 *
 * @param B указатель на вторую матрицу
 *
 * @returns
 * SUCCESS (1) - матрицы одинаковы,
 * FAILURE (0) - матрицы различны
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int success = SUCCESS;

  if (A->columns == B->columns && A->rows == B->rows) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
          success = FAILURE;
          break;
        }
      }
    }
  } else {
    success = FAILURE;
  }
  return success;
}

/**
 * @brief сложение двух матриц с одинаковым количеством строк и столбцов
 *
 * @param A указатель на первую матрицу
 *
 * @param B указатель на вторую матрицу
 *
 * @param result указатель на матрицу - результат сложения
 *
 * @returns ошибка: 0 - ОК,
 * ERR_INCORECT_MATRIX (1) - неккоректная матрица,
 * ERR_CALC (2) - ошибка вычисления
 */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  s21_matrix_init_zero(result);

  if (s21_matrix_check(A) && s21_matrix_check(B)) {
    if (A->columns == B->columns && A->rows == B->rows) {
      error = s21_create_matrix(A->rows, A->columns, result);
      if (error == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      } else {
        error = ERR_INCORECT_MATRIX;
      }
    } else {
      error = ERR_CALC;
    }
  } else {
    error = ERR_INCORECT_MATRIX;
  }
  return error;
}

/**
 * @brief разность двух матриц с одинаковым количеством строк и столбцов
 *
 * @param A указатель на первую матрицу
 *
 * @param B указатель на вторую матрицу
 *
 * @param result указатель на матрицу - результат вычитания
 *
 * @returns ошибка: 0 - ОК,
 * ERR_INCORECT_MATRIX (1) - неккоректная матрица,
 * ERR_CALC (2) - ошибка вычисления
 */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  s21_matrix_init_zero(result);

  if (s21_matrix_check(A) && s21_matrix_check(B)) {
    if (A->columns == B->columns && A->rows == B->rows) {
      error = s21_create_matrix(A->rows, A->columns, result);
      if (error == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      } else {
        error = ERR_INCORECT_MATRIX;
      }
    } else {
      error = ERR_CALC;
    }
  } else {
    error = ERR_INCORECT_MATRIX;
  }
  return error;
}

/**
 * @brief умножение матрицы на число
 *
 * @param A указатель на матрицу
 *
 * @param number число на которую умножаем матрицу
 *
 * @param result указатель на матрицу - результат умножение матрицы на число
 *
 * @returns ошибка: 0 - ОК,
 * ERR_INCORECT_MATRIX (1) - неккоректная матрица,
 * ERR_CALC (2) - ошибка вычисления
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = OK;
  s21_matrix_init_zero(result);

  if (s21_matrix_check(A)) {
    int rows = A->rows;
    int columns = A->columns;
    error = s21_create_matrix(rows, columns, result);
    if (error == 0) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    } else {
      error = ERR_INCORECT_MATRIX;
    }
  } else {
    error = ERR_INCORECT_MATRIX;
  }
  return error;
}

/**
 * @brief произведение двух матриц с одинаковым количеством строк и столбцов
 *
 * @param A указатель на первую матрицу
 *
 * @param B указатель на вторую матрицу
 *
 * @param result указатель на матрицу - результат произведения
 *
 * @returns ошибка: 0 - ОК,
 * ERR_INCORECT_MATRIX (1) - неккоректная матрица,
 * ERR_CALC (2) - ошибка вычисления
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  s21_matrix_init_zero(result);

  if (s21_matrix_check(A) && s21_matrix_check(B)) {
    if (A->columns == B->rows) {
      int rows = A->rows;
      int columns = B->columns;
      if (s21_create_matrix(rows, columns, result) == 0) {
        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < columns; j++) {
            double sum = 0;
            for (int k = 0; k < A->columns; k++) {
              sum += A->matrix[i][k] * B->matrix[k][j];
            }
            result->matrix[i][j] = sum;
          }
        }
      } else {
        error = ERR_INCORECT_MATRIX;
      }
    } else {
      error = ERR_CALC;
    }
  } else {
    error = ERR_INCORECT_MATRIX;
  }
  return error;
}

/**
 * @brief транспонирование матрицы (замена строк матрицы столбцами с сохранением
 * их номеров)
 *
 * @param A указатель на матрицу
 *
 * @param result указатель на матрицу - результат транспонирования
 *
 * @returns ошибка: 0 - ОК,
 * ERR_INCORECT_MATRIX (1) - неккоректная матрица,
 */
int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;
  s21_matrix_init_zero(result);

  if (s21_matrix_check(A)) {
    int rows = A->columns;
    int columns = A->rows;
    if (s21_create_matrix(rows, columns, result) == 0) {
      for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    } else {
      error = ERR_INCORECT_MATRIX;
    }
  } else {
    error = ERR_INCORECT_MATRIX;
  }
  return error;
}

/**
 * @brief построение матрицы алгебраических дополнений
 *
 * @param A указатель исходную матрицу
 *
 * @param result указатель на матрицу алгебраических дополнений
 *
 * @returns ошибка: 0 - ОК,
 * ERR_INCORECT_MATRIX (1) - неккоректная матрица,
 * ERR_CALC (2) - ошибка вычисления
 */
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;
  s21_matrix_init_zero(result);

  if (s21_matrix_check(A)) {
    if (A->columns == A->rows) {
      error = s21_create_matrix(A->rows, A->columns, result);
      if (A->columns == 1) {
        result->matrix[0][0] = A->matrix[0][0];
      } else {
        if (error == OK) {
          for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
              matrix_t tmp = {NULL, 0, 0};
              s21_create_minor_matrix_for_element(i, j, A, &tmp);
              result->matrix[i][j] =
                  s12_minor_calculation(&tmp) * pow(-1, i + j);
              s21_remove_matrix(&tmp);
            }
          }
        }
      }
    } else {
      error = ERR_CALC;
    }
  } else {
    error = ERR_INCORECT_MATRIX;
  }
  return error;
}

/**
 * @brief нахождение определителя матрицы (только для квадратной может быть)
 *
 * @param A указатель на исходную матрицу
 *
 * @param result указатель на переменную для занеения определителя
 *
 * @returns ошибка: 0 - ОК,
 * ERR_INCORECT_MATRIX (1) - неккоректная матрица,
 * ERR_CALC (2) - ошибка вычисления
 */
int s21_determinant(matrix_t *A, double *result) {
  int error = OK;

  if (s21_matrix_check(A)) {
    if (A->columns == A->rows) {
      *result = s12_minor_calculation(A);
    } else {
      error = ERR_CALC;
    }
  } else {
    error = ERR_INCORECT_MATRIX;
  }
  return error;
}

/**
 * @brief нахождение обратной (только для квадратной может быть)
 *
 * @param A указатель на исходную матрицу
 *
 * @param result указатель на обратную матрицу
 *
 * @returns ошибка: 0 - ОК,
 * ERR_INCORECT_MATRIX (1) - неккоректная матрица,
 * ERR_CALC (2) - ошибка вычисления
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = OK;
  s21_matrix_init_zero(result);

  if (s21_matrix_check(A)) {
    if (A->rows == A->columns) {
      double determinant = 0;
      error = s21_determinant(A, &determinant);

      if (determinant != 0) {
        if (error == 0) {
          matrix_t tmp_comp = {NULL, 0, 0};
          matrix_t tmp_trans = {NULL, 0, 0};
          error = s21_calc_complements(A, &tmp_comp);
          error = s21_transpose(&tmp_comp, &tmp_trans);
          error = s21_mult_number(&tmp_trans, 1 / determinant, result);
          s21_remove_matrix(&tmp_comp);
          s21_remove_matrix(&tmp_trans);
        }
      } else {
        error = ERR_CALC;
      }

    } else {
      error = ERR_CALC;
    }
  } else {
    error = ERR_INCORECT_MATRIX;
  }
  return error;
}

/**
 * @brief создание матрицы для определения минора элемента матрицы *А
 *
 * @param num_row номер строки в которой находится элемент матрицы *А
 *
 * @param num_column номер колонны в которой находится элемент матрицы *А
 *
 * @param A указатель на начало матрицы для которой находим миноры элементов
 *
 * @param result указатель на матрицу для дальнейшего определения миноров
 */
void s21_create_minor_matrix_for_element(int num_row, int num_column,
                                         matrix_t *A, matrix_t *result) {
  int error = OK;
  if (s21_matrix_check(A)) {
    error = s21_create_matrix(A->rows - 1, A->columns - 1, result);
    int result_row = 0;
    int result_column = 0;
    if (error == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (i != num_row && j != num_column) {
            result->matrix[result_row][result_column++] = A->matrix[i][j];
            if (result_column == result->columns)
              result_row++, result_column = 0;
          }
        }
      }
    }
  }
}

/**
 * @brief проверка матрицы на адекватность
 *
 * @param A указатель на матрицу
 *
 * @returns минор
 */
double s12_minor_calculation(matrix_t *A) {
  double minor = 0;
  if (A->columns == A->rows) {
    if (A->rows == 1) {
      minor = A->matrix[0][0];
    } else if (A->rows == 2) {
      minor =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      for (int i = 0; i < A->columns; ++i) {
        matrix_t tmp = {NULL, 0, 0};
        s21_create_minor_matrix_for_element(0, i, A, &tmp);
        minor += A->matrix[0][i] * s12_minor_calculation(&tmp) * pow(-1, i);
        s21_remove_matrix(&tmp);
      }
    }
  }
  return minor;
}

/**
 * @brief определение минора матрицы *А
 *
 * @param A указатель на начало матрицы для которой находим минор
 *
 * @returns
 * SUCCESS (1) - матрица адекватная,
 * FAILURE (0) - матрица неадекватная
 */
int s21_matrix_check(matrix_t *A) {
  int error = FAILURE;
  if (A->matrix != NULL && A->columns >= 1 && A->rows >= 1 && A != NULL)
    error = SUCCESS;
  return error;
}

/**
 * @brief инициализация "нулевой матрицы"
 *
 * @param A указатель на матрицу
 */
void s21_matrix_init_zero(matrix_t *A) {
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}