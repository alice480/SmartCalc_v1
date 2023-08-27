#ifndef BANKCALC_H
#define BANKCALC_H

#include "mainwindow.h"
#include <QMainWindow>

extern "C" {
#include "./backend/s21_bank_calc.h"
}

namespace Ui {
class BankCalc;
}

class BankCalc : public QMainWindow {
  Q_OBJECT

public:
  explicit BankCalc(QWidget *parent = nullptr);
  ~BankCalc();

private slots:
  void on_actionSmartCalc_triggered();

  void on_pushButton_clicked();

  void on_actionDepositCalc_triggered();

private:
  Ui::BankCalc *ui;
};

#endif // BANKCALC_H
