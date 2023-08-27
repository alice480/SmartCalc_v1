#ifndef BANK_CALC_H
#define BANK_CALC_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget {
  Q_OBJECT

public:
  explicit Form(QWidget *parent = nullptr);
  ~Form();

private:
  Ui::Form *ui;
};

#endif // BANK_CALC_H
