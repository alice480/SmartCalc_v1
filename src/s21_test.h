#ifndef SRC_S21_TEST_H
#define SRC_S21_TEST_H

#define ACCURACY 1e-6

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "./backend/s21_bank_calc.h"
#include "./backend/s21_smart_calc.h"

Suite *test_s21_unary(void);
Suite *test_s21_binary(void);
Suite *test_s21_credit(void);

#endif // SRC_S21_TEST_H