#include "depositcalc.h"
#include "ui_depositcalc.h"

DepositCalc::DepositCalc(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::DepositCalc) {
  ui->setupUi(this);
  connect(ui->pushButton_top, SIGNAL(clicked()), this,
          SLOT(fill_tableWidget()));
  connect(ui->pushButton_withdraw, SIGNAL(clicked()), this,
          SLOT(fill_tableWidget()));
  ui->comboBox_capital->setDisabled(true);
  ui->comboBox_payment->setDisabled(true);
}

DepositCalc::~DepositCalc() { delete ui; }

void DepositCalc::on_actionSmartCalc_triggered() {
  MainWindow *new_window = new MainWindow();
  new_window->show();
  this->close();
}

void DepositCalc::on_actionCreditCalc_triggered() {
  BankCalc *new_window = new BankCalc();
  new_window->show();
  this->close();
}

void DepositCalc::on_radioButton_clicked() {
  ui->comboBox_capital->setDisabled(false);
  ui->comboBox_payment->setDisabled(true);
  capitalization = true;
}

void DepositCalc::on_radioButton_2_clicked() {
  ui->comboBox_capital->setDisabled(true);
  ui->comboBox_payment->setDisabled(false);
  capitalization = false;
}

void DepositCalc::on_pushButton_clear_clicked() {
  ui->tableWidget_2->setRowCount(0);
}

void DepositCalc::fill_tableWidget() {
  QPushButton *button = (QPushButton *)sender();
  int row_count = ui->tableWidget_2->rowCount();
  QDate pw_date = ui->dateEdit_payment_withdrawal->date();

  if (row_count) {
    QString last_str = ui->tableWidget_2->item(row_count - 1, 0)->text();
    QDate last_date = QDate::fromString(last_str, "dd.MM.yyyy");
    if (last_date <= pw_date) {
      ui->tableWidget_2->insertRow(row_count);
      ui->tableWidget_2->setItem(
          row_count, 0, new QTableWidgetItem(pw_date.toString("dd.MM.yyyy")));
      ui->tableWidget_2->setItem(row_count, 1,
                                 new QTableWidgetItem(QString::number(
                                     ui->doubleSpinBox_pw_amount->value())));
      ui->tableWidget_2->setItem(row_count, 2,
                                 new QTableWidgetItem(button->text()));
    }
  } else {
    QDate start_date = ui->dateEdit_start->date();
    if (start_date <= pw_date) {
      ui->tableWidget_2->insertRow(row_count);
      ui->tableWidget_2->setItem(
          row_count, 0, new QTableWidgetItem(pw_date.toString("dd.MM.yyyy")));
      ui->tableWidget_2->setItem(row_count, 1,
                                 new QTableWidgetItem(QString::number(
                                     ui->doubleSpinBox_pw_amount->value())));
      ui->tableWidget_2->setItem(row_count, 2,
                                 new QTableWidgetItem(button->text()));
    }
  }
}

void DepositCalc::on_pushButton_count_clicked() {
  ui->tableWidget->setRowCount(0);

  double deposit_amount = ui->doubleSpinBox_deposit_amount->value();
  double initial_amount = deposit_amount;

  double rate = ui->doubleSpinBox_rate->value();

  QDate start_date = ui->dateEdit_start->date();
  QStringList term = ui->comboBox_term->currentText().split(u' ');
  double month_count;
  if (term[1].contains("месяц")) {
    month_count = term[0].toDouble();
  } else {
    month_count = term[0].toDouble() * 12;
  }

  QString period;
  // getting the number of months after which interest is accrued or withdrawn
  if (capitalization)
    period = ui->comboBox_capital->currentText();
  else
    period = ui->comboBox_payment->currentText();
  int period_between_percent_changes = term_numerical_equivalent(period);

  double percentages = 0;
  double accumulated_interest = 0;

  for (int i = 1; i <= month_count; i++) {
    // deposits and withdrawals per month are counted
    double pw_changes =
        amount_changing(start_date.addMonths(i - 1), start_date.addMonths(i));
    deposit_amount += pw_changes;

    setlocale(LC_NUMERIC, "C");
    percentages += s21_deposit_calc(rate, deposit_amount);

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    int row_index = ui->tableWidget->rowCount() - 1;

    // the month corresponds to the payment or capitalization
    if (!(i % period_between_percent_changes)) {
      if (capitalization) {
        // the interest received is added to the original amount
        deposit_amount += percentages;
        ui->tableWidget->setItem(
            row_index, 1, new QTableWidgetItem(QString::number(0, 'g', 8)));
      } else {
        // interest is paid
        accumulated_interest += percentages;
        ui->tableWidget->setItem(
            row_index, 1,
            new QTableWidgetItem(QString::number(percentages, 'g', 8)));
      }
      percentages = 0;
    } else
      ui->tableWidget->setItem(
          row_index, 1, new QTableWidgetItem(QString::number(0, 'g', 8)));

    QDate replenishment_date = start_date.addMonths(i);
    ui->tableWidget->setItem(
        row_index, 0,
        new QTableWidgetItem(replenishment_date.toString("dd.MM.yyyy")));
    ui->tableWidget->setItem(
        row_index, 2,
        new QTableWidgetItem(QString::number(deposit_amount, 'g', 8)));
  }
  ui->textEdit_deposit->setText(QString::number(deposit_amount, 'g', 8));

  double profit = deposit_amount + accumulated_interest - initial_amount;
  ui->textEdit_percentages->setText(QString::number(profit, 'g', 8));

  double tax = ui->doubleSpinBox_tax->value();
  double profit_after_deduction = profit * tax / 100;
  ui->textEdit_tax->setText(QString::number(profit_after_deduction, 'g', 8));
}

int DepositCalc::term_numerical_equivalent(QString term_name) {
  int period_between_accruals;
  if (term_name.contains("Ежемесячно"))
    period_between_accruals = 1;
  else if (term_name.contains("Ежеквартально"))
    period_between_accruals = 3;
  else
    period_between_accruals = 12;
  return period_between_accruals;
}

double DepositCalc::amount_changing(QDate start_date, QDate finish_date) {
  double amount = 0;
  for (int i = 0; i < ui->tableWidget_2->rowCount(); i++) {
    QString str_date = ui->tableWidget_2->item(i, 0)->text();
    QDate row_date = QDate::fromString(str_date, "dd.MM.yyyy");
    if (start_date <= row_date && row_date <= finish_date) {
      double row_amount = ui->tableWidget_2->item(i, 1)->text().toDouble();
      if (ui->tableWidget_2->item(i, 2)->text().contains("Пополнение"))
        amount += row_amount;
      else
        amount -= row_amount;
    }
  }
  return amount;
}
