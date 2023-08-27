#include "../s21_test.h"

START_TEST(annuity_loan_test) {
  double result1 = s21_annuity_loan(12, 100000, 24);
  ck_assert_float_eq(result1, 4707.35);
  double result2 = s21_annuity_loan(18, 20000, 6);
  ck_assert_float_eq(result2, 3510.50);
}
END_TEST

START_TEST(annuity_rate_eq_0) {
  double result = s21_annuity_loan(0, 100000, 24);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(annuity_month_count_eq_0) {
  double result = s21_annuity_loan(5, 100000, 0);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(differentiated_loan_test) {
  double result1 = s21_differentiated_loan(50000, 30);
  ck_assert_float_eq(result1, 1250.00);
  double result2 = s21_differentiated_loan(6875, 7);
  ck_assert_float_eq(result2, 40.10);
}
END_TEST

START_TEST(differentiated_debt_eq_0) {
  double result = s21_differentiated_loan(0, 10);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(differentiated_rate_eq_0) {
  double result = s21_differentiated_loan(100000, 0);
  ck_assert_float_eq(result, 0);
}

START_TEST(deposit_test) {
  double result1 = s21_deposit_calc(45000, 8);
  ck_assert_float_eq(result1, 300.00);
  double result2 = s21_deposit_calc(100, 65);
  ck_assert_float_eq(result2, 5.42);
}
END_TEST

START_TEST(deposit_rate_eq_0) {
  double result = s21_deposit_calc(0, 100000);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(deposit_amount_eq_0) {
  double result = s21_deposit_calc(2400, 0);
  ck_assert_float_eq(result, 0);
}

Suite *test_s21_credit(void) {
  Suite *s = suite_create("\033[45m-=S21_SMART_CALC=-\033[0m");
  TCase *tc = tcase_create("test_credit");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, annuity_loan_test);
  tcase_add_test(tc, annuity_rate_eq_0);
  tcase_add_test(tc, annuity_month_count_eq_0);
  tcase_add_test(tc, differentiated_loan_test);
  tcase_add_test(tc, differentiated_rate_eq_0);
  tcase_add_test(tc, differentiated_debt_eq_0);
  tcase_add_test(tc, deposit_test);
  tcase_add_test(tc, deposit_rate_eq_0);
  tcase_add_test(tc, deposit_amount_eq_0);
  suite_add_tcase(s, tc);
  return s;
}