#include "bankcalc.h"
#include "ui_bankcalc.h"

BankCalc::BankCalc(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::BankCalc) {
  ui->setupUi(this);
}

BankCalc::~BankCalc() { delete ui; }

void BankCalc::on_actionSmartCalc_triggered() {
  MainWindow *new_window = new MainWindow();
  new_window->show();
  this->close();
}

void BankCalc::on_pushButton_clicked() {
  ui->tableWidget_annuity->setRowCount(0);

  double credit_rate = ui->doubleSpinBox_credit_rate->value();
  double credit_amount = ui->doubleSpinBox_credit_amount->value();
  QStringList term = ui->comboBox_term->currentText().split(u' ');
  double month_count;
  if (term[1].contains("месяц")) {
    month_count = term[0].toDouble();
  } else {
    month_count = term[0].toDouble() * 12;
  }
  QString type = ui->comboBox_type->currentText();
  double total_payment = 0;
  if (type.contains("Аннуитетный")) {
    setlocale(LC_NUMERIC, "C");
    double monthly_payment =
        s21_annuity_loan(credit_rate, credit_amount, month_count);
    for (int i = 1; i <= month_count; i++) {
      ui->tableWidget_annuity->insertRow(ui->tableWidget_annuity->rowCount());
      int row_index = ui->tableWidget_annuity->rowCount() - 1;
      ui->tableWidget_annuity->setItem(
          row_index, 0, new QTableWidgetItem(QString::number(i)));
      ui->tableWidget_annuity->setItem(
          row_index, 1, new QTableWidgetItem(QString::number(monthly_payment)));
    }
    total_payment = monthly_payment * month_count;
  } else {
    setlocale(LC_NUMERIC, "C");
    double debt_body_repayment = credit_amount / month_count;
    for (int i = 0; i < month_count; i++) {
      double remaining_debt = credit_amount - (debt_body_repayment * i);
      double percentages = s21_differentiated_loan(remaining_debt, credit_rate);
      double monthly_payment = debt_body_repayment + percentages;
      total_payment += monthly_payment;

      ui->tableWidget_annuity->insertRow(ui->tableWidget_annuity->rowCount());
      int row_index = ui->tableWidget_annuity->rowCount() - 1;
      ui->tableWidget_annuity->setItem(
          row_index, 0, new QTableWidgetItem(QString::number(i + 1)));
      ui->tableWidget_annuity->setItem(
          row_index, 1, new QTableWidgetItem(QString::number(monthly_payment)));
    }
  }
  double overpayment = total_payment - credit_amount;
  ui->textEdit_total->setText(QString::number(total_payment, 'g', 7));
  ui->textEdit_overpayment->setText(QString::number(overpayment, 'g', 7));
}

void BankCalc::on_actionDepositCalc_triggered() {
  DepositCalc *new_window = new DepositCalc();
  new_window->show();
  this->close();
}
