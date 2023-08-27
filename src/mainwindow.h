#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>

#include "bankcalc.h"
#include "depositcalc.h"

extern "C" {
#include "./backend/s21_smart_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void get_button_value();

  void get_function_value();

  void on_pushButton_eq_clicked();

  void on_pushButton_truncate_clicked();

  void draw_graph(QString expression, bool with_variable);

  void on_actionBankCalc_triggered();

  void on_actionDepositCalc_triggered();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
