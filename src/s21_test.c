#include "s21_test.h"

int main(void) {
  int failed = 0;

  Suite *s21_calc_test[] = {
          test_s21_unary(),
          test_s21_binary(),
          test_s21_credit(),
          NULL};


  for (int i = 0; s21_calc_test[i] != NULL; i++) {  // (&& failed == 0)
    SRunner *runner = srunner_create(s21_calc_test[i]);

    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);

    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
