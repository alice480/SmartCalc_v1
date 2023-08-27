#include "../s21_test.h"

START_TEST(function_sin) {
  char expression[] = "sin(1)";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq_tol(sin(1), result, ACCURACY);
}
END_TEST

START_TEST(function_cos) {
  char expression[] = "cos(1)";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq_tol(cos(1), result, ACCURACY);
}
END_TEST

START_TEST(function_asin) {
  char expression[] = "asin(0.5)";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq_tol(asin(0.5), result, ACCURACY);
}
END_TEST

START_TEST(function_acos) {
  char expression[] = "acos(1)";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq_tol(acos(1), result, ACCURACY);
}
END_TEST

START_TEST(function_tan) {
  char expression[] = "tan(1)";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq_tol(tan(1), result, ACCURACY);
}
END_TEST

START_TEST(function_atan) {
  char expression[] = "atan(1)";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq_tol(atan(1), result, ACCURACY);
}
END_TEST

START_TEST(function_sqrt) {
  char expression[] = "sqrt(4)";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq_tol(sqrt(4), result, ACCURACY);
}
END_TEST

START_TEST(function_log) {
  char expression[] = "log(2)";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq_tol(log10(2), result, ACCURACY);
}
END_TEST

START_TEST(function_ln) {
  char expression[] = "ln(2)";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq_tol(log(2), result, ACCURACY);
}
END_TEST

START_TEST(function_unary_minus) {
  char expression1[] = "3+(-2)";
  double result;
  s21_calculation(expression1, &result);
  ck_assert_float_eq(1, result);
  char expression2[] = "3--2";
  s21_calculation(expression2, &result);
  ck_assert_float_eq(5, result);
}
END_TEST

START_TEST(function_unary_plus) {
  char expression1[] = "3-(+2)";
  double result;
  s21_calculation(expression1, &result);
  ck_assert_float_eq(1, result);
  char expression2[] = "3++2";
  s21_calculation(expression2, &result);
  ck_assert_float_eq(5, result);
}
END_TEST

START_TEST(some_functions) {
  char expression[] = "sin(asin(sqrt(ln(log(228.11)))))";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq_tol(sin(asin(sqrt(log(log10(228.11))))), result, ACCURACY);
}
END_TEST

Suite *test_s21_unary(void) {
  Suite *s = suite_create("\033[45m-=S21_SMART_CALC=-\033[0m");
  TCase *tc = tcase_create("test_unary");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, function_sin);
  tcase_add_test(tc, function_cos);
  tcase_add_test(tc, function_asin);
  tcase_add_test(tc, function_acos);
  tcase_add_test(tc, function_tan);
  tcase_add_test(tc, function_atan);
  tcase_add_test(tc, function_sqrt);
  tcase_add_test(tc, function_log);
  tcase_add_test(tc, function_ln);
  tcase_add_test(tc, function_unary_minus);
  tcase_add_test(tc, function_unary_plus);
  tcase_add_test(tc, some_functions);
  suite_add_tcase(s, tc);
  return s;
}
