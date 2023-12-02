#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  // Проверка на некорректные размеры матрицы
  if (rows <= 0 || columns <= 0) {
    return EXIT_INCORR_MATRIX;  // Ошибка, некорректная матрица
  }

  result->matrix = (double **)malloc(rows * sizeof(double *));
  if (result->matrix == NULL) {
    return EXIT_CALC_ERROR;  // Ошибка выделения памяти для указателей на строки
                             // матрицы
  }

  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)malloc(columns * sizeof(double));
    if (result->matrix[i] == NULL) {
      // Если произошла ошибка выделения памяти, освобождаем уже выделенную
      // память
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      return EXIT_CALC_ERROR;  // Ошибка выделения памяти для элементов матрицы
    }
  }
  result->rows = rows;
  result->columns = columns;

  return EXIT_OK;  // OK
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  // Проверка на совпадение размеров матриц
  if (A->rows != B->rows || A->columns != B->columns || A->matrix == NULL ||
      B->matrix == NULL) {
    result = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON) {
          result = FAILURE;
          break;
        }
      }
    }
  }
  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = EXIT_OK;
  if (A->rows != B->rows || A->columns != B->columns) {
    res = EXIT_CALC_ERROR;  // Ошибка вычисления (несовпадающие размеры матриц)
  } else {
    int create_result = s21_create_matrix(A->rows, A->columns, result);
    if (create_result != EXIT_OK) {
      res = create_result;  // Возвращаем код ошибки создания матрицы
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = EXIT_OK;
  if (A->rows != B->rows || A->columns != B->columns) {
    res = EXIT_CALC_ERROR;  // Ошибка вычисления (несовпадающие размеры матриц)
  } else {
    int create_result = s21_create_matrix(A->rows, A->columns, result);
    if (create_result != EXIT_OK) {
      res = create_result;  // Возвращаем код ошибки создания матрицы
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = EXIT_OK;
  if (A->matrix == NULL) {
    res = EXIT_INCORR_MATRIX;  // Ошибка вычисления (некорректная матрица)
  } else {
    int create_result = s21_create_matrix(A->rows, A->columns, result);
    if (create_result != EXIT_OK) {
      res = create_result;  // Возвращаем код ошибки создания матрицы
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = number * A->matrix[i][j];
        }
      }
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = EXIT_OK;
  if (A->columns != B->rows) {
    res = EXIT_CALC_ERROR;  // Ошибка вычисления (несовпадающие размеры матриц)
  } else {
    int create_result = s21_create_matrix(A->rows, B->columns, result);
    if (create_result != EXIT_OK) {
      res = create_result;  // Возвращаем код ошибки создания матрицы
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = 0.0;
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = EXIT_OK;
  if (A->matrix == NULL) {
    res = EXIT_INCORR_MATRIX;  // Ошибка вычисления (некорректная матрица)
  } else {
    int create_result = s21_create_matrix(A->columns, A->rows, result);
    if (create_result != EXIT_OK) {
      res = create_result;  // Возвращаем код ошибки создания матрицы
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  }
  return res;
}

int calculate_minor(matrix_t *A, int x, int y, matrix_t *minor) {
  int status = EXIT_OK;

  if (A->rows > 1 && A->columns > 1 && x < A->rows && y < A->columns) {
    s21_create_matrix(A->rows - 1, A->columns - 1, minor);
    int i_skip = 0;

    for (int i = 0; i < A->rows; ++i) {
      if (i == x) {
        i_skip = 1;
      } else {
        int j_skip = 0;

        for (int j = 0; j < A->columns; ++j) {
          if (j == y) {
            j_skip = 1;
          } else {
            minor->matrix[i - i_skip][j - j_skip] = A->matrix[i][j];
          }
        }
      }
    }
  } else {
    status = EXIT_CALC_ERROR;
  }

  return status;
}

double calculate_determinant(matrix_t *A) {
  double result = 0;

  if (A->rows != 1) {
    for (int i = 0; i < A->rows; ++i) {
      matrix_t minor;
      calculate_minor(A, 0, i, &minor);

      result +=
          A->matrix[0][i] * calculate_determinant(&minor) * (i % 2 ? -1 : 1);

      s21_remove_matrix(&minor);
    }
  } else {
    result = A->matrix[0][0];
  }

  return result;
}

int s21_determinant(matrix_t *A, double *result) {
  int status = EXIT_OK;

  if (A->rows == A->columns) {
    *result = calculate_determinant(A);
  } else {
    status = EXIT_CALC_ERROR;
  }

  return status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = EXIT_OK;
  if (A->matrix == NULL || A->rows != A->columns) {
    status = EXIT_CALC_ERROR;
  } else {
    int n = A->rows;
    int create_result = s21_create_matrix(n, n, result);
    if (create_result != EXIT_OK) return create_result;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        matrix_t minor;
        calculate_minor(A, i, j, &minor);

        double determinant_minor = calculate_determinant(&minor);
        result->matrix[i][j] = determinant_minor * ((i + j) % 2 == 0 ? 1 : -1);

        s21_remove_matrix(&minor);
      }
    }
  }
  return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = EXIT_OK;
  if (A->matrix == NULL) {
    status = EXIT_INCORR_MATRIX;
  } else if (A->columns == 1 && A->rows == 1) {
    status = EXIT_CALC_ERROR;
  } else {
    double determinant;
    s21_determinant(A, &determinant);

    if (A->rows != A->columns || determinant == 0) {
      status = EXIT_CALC_ERROR;
    } else {
      matrix_t M, T;
      s21_calc_complements(A, &M);
      s21_transpose(&M, &T);
      s21_mult_number(&T, 1 / determinant, result);

      s21_remove_matrix(&M);
      s21_remove_matrix(&T);
    }
  }
  return status;
}