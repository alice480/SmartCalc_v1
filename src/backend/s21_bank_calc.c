#include "s21_bank_calc.h"

double s21_annuity_loan(double credit_rate, double credit_amount,
                        int month_count) {
  double monthly_payment = 0;
  if (month_count && credit_rate) {
    double monthly_rate = credit_rate / (12 * 100);
    double multiplier = pow((1 + monthly_rate), month_count);
    double coefficient = (monthly_rate * multiplier) / (multiplier - 1);
    monthly_payment = credit_amount * coefficient;
    monthly_payment = round(monthly_payment * 100) / 100;
  }
  return monthly_payment;
}

double s21_differentiated_loan(double debt, double credit_rate) {
  double monthly_rate = credit_rate / (12 * 100);
  double percentages = debt * monthly_rate;
  percentages = round(percentages * 100) / 100;
  return percentages;
}

double s21_deposit_calc(double interest_rate, double deposit_amount) {
  double monthly_rate = interest_rate / (12 * 100);
  double percentages = deposit_amount * monthly_rate;
  percentages = round(percentages * 100) / 100;
  return percentages;
}