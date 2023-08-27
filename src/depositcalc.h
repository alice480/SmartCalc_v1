#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include "bank_calc.h"
#include "mainwindow.h"
#include <QMainWindow>

extern "C" {
#include "./backend/s21_bank_calc.h"
}

namespace Ui {
class DepositCalc;
}

class DepositCalc : public QMainWindow {
  Q_OBJECT

public:
  explicit DepositCalc(QWidget *parent = nullptr);
  bool capitalization = false;
  int term_numerical_equivalent(QString term_name);
  double amount_changing(QDate start_date, QDate finish_date);
  ~DepositCalc();

private slots:
  void on_actionSmartCalc_triggered();

  void on_actionCreditCalc_triggered();

  void on_radioButton_clicked();

  void on_radioButton_2_clicked();

  void on_pushButton_clear_clicked();

  void fill_tableWidget();

  void on_pushButton_count_clicked();

private:
  Ui::DepositCalc *ui;
};

#endif // DEPOSITCALC_H
