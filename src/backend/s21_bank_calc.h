#ifndef SRC_BACKEND_S21_BANK_CALC_H_
#define SRC_BACKEND_S21_BANK_CALC_H_

#include <math.h>
#include <stdio.h>

double s21_annuity_loan(double credit_rate, double credit_amount,
                        int month_count);
double s21_differentiated_loan(double debt, double credit_rate);

double s21_deposit_calc(double interest_rate, double deposit_amount);

#endif // SRC_BACKEND_S21_BANK_CALC_H_