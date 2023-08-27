#include "../s21_test.h"

START_TEST(operator_plus) {
  char expression[] = "12.1+4.23";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq((12.1 + 4.23), result);
}
END_TEST

START_TEST(operator_minus) {
  char expression[] = "-17.6+18.923";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq((-17.6 + 18.923), result);
}
END_TEST

START_TEST(operator_mult) {
  char expression[] = "36.6*31";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq((36.6 * 31), result);
}
END_TEST

START_TEST(operator_div) {
  char expression[] = "17.5/8.3";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq((17.5/8.3), result);
}
END_TEST

START_TEST(operator_div_nan) {
  char expression[] = "5.1/0";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_nan(result);
}
END_TEST

START_TEST(operator_pow) {
  char expression[] = "12.3^4";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq(pow(12.3, 4), result);
}
END_TEST

START_TEST(operator_mod) {
  char expression[] = "15mod8";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq(fmod(15, 8), result);
}
END_TEST

START_TEST(operator_some_operators) {
  char expression[] = "(11.754-15.8163*2.9)/3.1";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq(((11.754-15.8163*2.9)/3.1), result);
}
END_TEST

START_TEST(operator_mod_with_operators) {
  char expression[] = "6.4*5mod(2+1.4)*3";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq(fmod(6.4*5, 3.4) * 3, result);
}
END_TEST

START_TEST(peek_last_opeartor_from_stack) {
  char expression[] = "3*sin(1+2.1)+4";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq(3*sin(1+2.1)+4, result);
}
END_TEST

START_TEST(error_expression) {
  char expression[] = ")";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq(0, result);
}
END_TEST

START_TEST(error_expression_with_x) {
  char expression[] = "2(3)";
  double result;
  s21_calculation(expression, &result);
  ck_assert_float_eq(0, result);
}
END_TEST

Suite *test_s21_binary(void) {
  Suite *s = suite_create("\033[45m-=S21_SMART_CALC=-\033[0m");
  TCase *tc = tcase_create("test_binary");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, operator_plus);
  tcase_add_test(tc, operator_minus);
  tcase_add_test(tc, operator_mult);
  tcase_add_test(tc, operator_div);
  tcase_add_test(tc, operator_div_nan);
  tcase_add_test(tc, operator_pow);
  tcase_add_test(tc, operator_mod);
  tcase_add_test(tc, operator_mod_with_operators);
  tcase_add_test(tc, operator_some_operators);
  tcase_add_test(tc, peek_last_opeartor_from_stack);
  tcase_add_test(tc, error_expression);
  tcase_add_test(tc, error_expression_with_x);
  suite_add_tcase(s, tc);
  return s;
}