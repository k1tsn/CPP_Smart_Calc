#include "mainwindow.h"

#include <QDate>
#include <QPushButton>
#include <QString>
#include <QTableWidgetItem>
#include <locale>
#include <string>
#include <vector>

#include "ui_mainwindow.h"

namespace calc {

MainWindow::MainWindow(QWidget *parent, calc::Controller *controller)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setlocale(LC_ALL, "C");
  ui->setupUi(this);
  controller_ = controller;
  ButtonsConnect();
  QDate date = QDate::currentDate();
  ui->credit_date->setDate(date);
  ui->date_deposit->setDate(date);
  ui->deposit_date_start->setDate(date);

  ui->deposit_date_start->setDisplayFormat("dd.MM.yyyy");
  ui->credit_date->setDisplayFormat("dd.MM.yyyy");
  ui->date_deposit->setDisplayFormat("dd.MM.yyyy");
  ptr_to_graph_ = new DrawGraph(ui->graph);
}

MainWindow::~MainWindow() {
  ClearAddSubTable(ptr_item_date_add_, ptr_item_amount_add_);
  ClearAddSubTable(ptr_item_date_sub_, ptr_item_amount_sub_);
  ClearResTable(ptr_res_deposit_);
  ClearResTable(ptr_res_credit_);
  delete ptr_to_graph_;
  delete ui;
}

void MainWindow::ClearAddSubTable(std::list<QTableWidgetItem *> ptr_date,
                                  std::list<QTableWidgetItem *> ptr_amount) {
  if (ptr_date.size() > 0) {
    std::list<QTableWidgetItem *>::iterator iter_date = ptr_date.begin();
    std::list<QTableWidgetItem *>::iterator iter_amount = ptr_amount.begin();
    for (; iter_date != ptr_date.end(); ++iter_date, ++iter_amount) {
      delete *iter_date;
      delete *iter_amount;
    }
  }
}

void MainWindow::ClearResTable(std::vector<QTableWidgetItem *> ptr) {
  if (ptr.size() > 0) {
    for (size_t i = 0; i < ptr.size(); ++i) {
      delete ptr[i];
    }
  }
}

void MainWindow::MakeStr() {
  if (((QPushButton *)sender())->text() == "x^y")
    ui->result->insert("^");
  else
    ui->result->insert(((QPushButton *)sender())->text());
}

void MainWindow::CalcResult() {
  str_.clear();
  ui->tab_mistakes_lebel->clear();
  QString res_str = ui->result->displayText();
  QString x_str = ui->tab_num_x->displayText();
  str_ = res_str.toStdString();
  std::string x = x_str.toStdString();
  int8_t err = controller_->SetXForCalc(x);
  std::string error_name;
  if (err != 0) {
    error_name = (controller_->GetErrorName(err));
    ui->tab_mistakes_lebel->setText(QString::fromStdString(error_name));
    return;
  }
  err = controller_->SetExprForCalc(str_);
  if (err != 0) {
    error_name = (controller_->GetErrorName(err));
    ui->tab_mistakes_lebel->setText(QString::fromStdString(error_name));
    return;
  }
  double res;
  err = controller_->GetResultFromClac(res);
  if (err != 0) {
    error_name = (controller_->GetErrorName(err));
    ui->tab_mistakes_lebel->setText(QString::fromStdString(error_name));
    return;
  }
  ui->result->setText(QString::number(res, 'g', 10));
  ui->tab_prev_expr->setText(res_str);
}

void MainWindow::ClearElement() { ui->result->backspace(); }

void MainWindow::ClearAllElements() {
  ui->result->clear();
  ui->tab_num_x->clear();
  ui->tab_mistakes_lebel->clear();
  ui->tab_prev_expr->clear();
}

void MainWindow::ClearGraphItems() {
  ui->graph_min_x->clear();
  ui->graph_max_x->clear();
  ui->graph_min_y->clear();
  ui->graph_max_y->clear();
  ui->graph_step_x->clear();
  ui->graph_step_y->clear();
  ui->graph_inp_formuls->clear();
}

void MainWindow::MakeGraph() {
  std::string min_x = (ui->graph_min_x->text()).toStdString();
  std::string max_x = (ui->graph_max_x->text()).toStdString();
  std::string min_y = (ui->graph_min_y->text()).toStdString();
  std::string max_y = (ui->graph_max_y->text()).toStdString();
  int8_t err = controller_->SetRangeXForGraph(min_x, max_x);
  if (err != 0) return;
  err = controller_->SetRangeYForGraph(min_y, max_y);
  if (err != 0) return;
  controller_->SetSizePix(ptr_to_graph_->GetSizePix());
  controller_->SetDivStep(ptr_to_graph_->GetDivStep());

  int hight = ptr_to_graph_->GetHight();
  int weight = ptr_to_graph_->GetWeight();
  controller_->SetHightForGraph(hight);
  controller_->SetWeightForGraph(weight);

  std::string expr = (ui->graph_inp_formuls->text()).toStdString();
  controller_->SetExprForGraph(expr);

  std::vector<double> x;
  std::vector<double> y;
  controller_->GetResultFromGraph(x, y);
  ptr_to_graph_->SetXYPoints(x, y);
  ptr_to_graph_->repaint();

  double step_x = controller_->GetStepX();
  double step_y = controller_->GetStepY();

  ui->graph_step_x->setText(QString::number(step_x, 'f', 4));
  ui->graph_step_y->setText(QString::number(step_y, 'f', 4));
}

void MainWindow::CalcCredit() {
  ClearResTable(ptr_res_credit_);
  ptr_res_credit_.clear();
  calc::CreditSettings settings;
  settings.amount_ = (ui->credit_amount->text()).toStdString();
  settings.term_ = (ui->credit_term->text()).toStdString();
  settings.rate_ = (ui->credit_rate->text()).toStdString();
  settings.type_ = (ui->credit_method->currentText()).toStdString();
  settings.month_or_year_ =
      (ui->credit_month_year->currentText()).toStdString();
  settings.date_ = (ui->credit_date->text()).toStdString();

  int8_t err = controller_->SetValueForCredit(settings);

  if (err == 0)
    ViewResultForCredit();
  else
    ClearResTable(ptr_res_credit_);
}

void MainWindow::ViewResultForCredit() {
  double overpayment;
  double total_payout;
  std::vector<calc::CreditResult> res;

  controller_->GetResultFromCredit(overpayment, total_payout, res);

  ui->credit_overpay->setText(QString::number(overpayment, 'f', 2));
  ui->credit_total_pay->setText(QString::number(total_payout, 'f', 2));
  ui->credit_result->setRowCount(res.size());
  ui->credit_result->setColumnCount(5);
  QStringList vertical_headers = {"Дата", "Ежемесячный платеж",
                                  "Платеж по осн. долгу", "Платеж по процентам",
                                  "Остаток долга"};
  ui->credit_result->setHorizontalHeaderLabels(vertical_headers);

  std::vector<calc::CreditResult>::iterator iter = res.begin();
  for (size_t i = 0; i < res.size(); ++i, ++iter) {
    QTableWidgetItem *item_data = ui->credit_result->item(i, 0);
    item_data = new QTableWidgetItem(QString::fromStdString(iter->out_date_));
    ui->credit_result->setItem(i, 0, item_data);
    ptr_res_credit_.push_back(item_data);

    QTableWidgetItem *item_monthly_payment = ui->credit_result->item(i, 1);
    item_monthly_payment =
        new QTableWidgetItem(QString::number(iter->monthly_payment_, 'f', 2));
    ui->credit_result->setItem(i, 1, item_monthly_payment);
    ptr_res_credit_.push_back(item_monthly_payment);

    QTableWidgetItem *item_total_pay = ui->credit_result->item(i, 2);
    item_total_pay =
        new QTableWidgetItem(QString::number(iter->total_pay_, 'f', 2));
    ui->credit_result->setItem(i, 2, item_total_pay);
    ptr_res_credit_.push_back(item_total_pay);

    QTableWidgetItem *item_rate = ui->credit_result->item(i, 3);
    item_rate =
        new QTableWidgetItem(QString::number(iter->rate_payment_, 'f', 2));
    ui->credit_result->setItem(i, 3, item_rate);
    ptr_res_credit_.push_back(item_rate);

    QTableWidgetItem *item_balance_owed = ui->credit_result->item(i, 4);
    item_balance_owed =
        new QTableWidgetItem(QString::number(iter->balance_owed_, 'f', 2));
    ui->credit_result->setItem(i, 4, item_balance_owed);
    ptr_res_credit_.push_back(item_balance_owed);
  }
}

void MainWindow::AddIntoAddList() {
  if (ui->amount_add_sub->text().isEmpty()) return;

  int row = ui->list_add->rowCount();
  if (row == 0) {
    ui->list_add->setRowCount(1);
    ui->list_add->setColumnCount(2);
  } else
    ui->list_add->insertRow(row);

  QTableWidgetItem *item_date = ui->list_add->item(row, 0);
  item_date = new QTableWidgetItem();
  ui->list_add->setItem(row, 0, item_date);
  item_date->setText(ui->date_deposit->text());
  ptr_item_date_add_.push_back(item_date);

  QTableWidgetItem *item_amount = ui->list_add->item(row, 1);
  item_amount = new QTableWidgetItem();
  ui->list_add->setItem(row, 1, item_amount);
  item_amount->setText(ui->amount_add_sub->text());
  ptr_item_amount_add_.push_back(item_amount);

  row_add_list_ = row;
}

void MainWindow::DeleteFromAddList() {
  if (ui->list_add->rowCount() == 0) return;
  ui->list_add->removeRow(row_add_list_);

  std::list<QTableWidgetItem *>::iterator iter_d = ptr_item_date_add_.begin();
  std::list<QTableWidgetItem *>::iterator iter_a = ptr_item_amount_add_.begin();

  for (int i = 0; i < row_add_list_; ++i) {
    ++iter_d;
    ++iter_a;
  }

  ptr_item_date_add_.erase(iter_d);
  ptr_item_amount_add_.erase(iter_a);

  row_add_list_ = ui->list_add->rowCount() - 1;
}

void MainWindow::AddIntoSubList() {
  if (ui->amount_add_sub->text().isEmpty()) return;

  int row = ui->list_sub->rowCount();
  if (row == 0) {
    ui->list_sub->setRowCount(1);
    ui->list_sub->setColumnCount(2);
  } else
    ui->list_sub->insertRow(row);

  QTableWidgetItem *item_date = ui->list_sub->item(row, 0);
  item_date = new QTableWidgetItem();
  ui->list_sub->setItem(row, 0, item_date);
  item_date->setText(ui->date_deposit->text());
  ptr_item_date_sub_.push_back(item_date);

  QTableWidgetItem *item_amount = ui->list_sub->item(row, 1);
  item_amount = new QTableWidgetItem();
  ui->list_sub->setItem(row, 1, item_amount);
  item_amount->setText(ui->amount_add_sub->text());
  ptr_item_amount_sub_.push_back(item_amount);

  row_sub_list_ = row;
}

void MainWindow::DeleteFromSubList() {
  if (ui->list_sub->rowCount() == 0) return;
  ui->list_sub->removeRow(row_sub_list_);

  std::list<QTableWidgetItem *>::iterator iter_d = ptr_item_date_sub_.begin();
  std::list<QTableWidgetItem *>::iterator iter_a = ptr_item_amount_sub_.begin();

  for (int i = 0; i < row_sub_list_; ++i) {
    ++iter_d;
    ++iter_a;
  }

  ptr_item_date_sub_.erase(iter_d);
  ptr_item_amount_sub_.erase(iter_a);

  row_sub_list_ = ui->list_sub->rowCount() - 1;
}

void MainWindow::SetRowColAddList(int r, int c) {
  row_add_list_ = r;
  column_add_list_ = c;
}
void MainWindow::SetRowColSubList(int r, int c) {
  row_sub_list_ = r;
  column_sub_list_ = c;
}

void MainWindow::CalcDeposit() {
  ClearResTable(ptr_res_deposit_);
  ptr_res_deposit_.clear();

  for (int i = 0, j = 0; i < ui->list_add->rowCount(); ++i) {
    std::string date = (ui->list_add->item(i, j)->text()).toStdString();
    std::string amount = (ui->list_add->item(i, j + 1)->text()).toStdString();
    controller_->SetAddForDeposit(date, amount);
  }

  for (int i = 0, j = 0; i < ui->list_sub->rowCount(); ++i) {
    std::string date = (ui->list_sub->item(i, j)->text()).toStdString();
    std::string amount = (ui->list_sub->item(i, j + 1)->text()).toStdString();
    controller_->SetSubForDeposit(date, amount);
  }

  calc::DepositSettings settings;
  settings.is_capital_ = false;
  if (ui->deposit_is_capital->isChecked() == true) settings.is_capital_ = true;
  settings.amount_ = (ui->amount_deposit->text()).toStdString();
  settings.term_ = (ui->deposit_term->text()).toStdString();
  settings.rate_ = (ui->deposit_interest_rate->text()).toStdString();
  settings.day_month_year_ = (ui->d_m_y_term->currentText()).toStdString();
  settings.date_ = (ui->deposit_date_start->text()).toStdString();
  settings.capitalization_ = (ui->deposit_capital->currentText()).toStdString();

  int err = controller_->SetValForDeposit(settings);
  if (err == 0)
    ViewResultForDeposit();
  else
    ClearResTable(ptr_res_deposit_);
}

void MainWindow::ViewResultForDeposit() {
  double tax;
  double rate_pay;
  double amount_end;
  std::vector<calc::DepositResult> res;
  controller_->GetResultFromDeposit(tax, rate_pay, amount_end, res);

  ui->deposit_res_tax->setText(QString::number(tax, 'f', 2));
  ui->deposit_res_rate->setText(QString::number(rate_pay, 'f', 2));
  ui->deposit_res_amount->setText(QString::number(amount_end, 'f', 2));

  ui->deposit_result->setRowCount(res.size());
  ui->deposit_result->setColumnCount(4);
  QStringList vertical_headers = {"Дата", "Начисленные проценты", "Изменения",
                                  "Баланс"};
  ui->deposit_result->setHorizontalHeaderLabels(vertical_headers);

  std::vector<calc::DepositResult>::iterator iter = res.begin();
  for (size_t i = 0; i < res.size(); ++i, ++iter) {
    QTableWidgetItem *item_data = ui->deposit_result->item(i, 0);
    item_data = new QTableWidgetItem(QString::fromStdString(iter->out_date_));
    ui->deposit_result->setItem(i, 0, item_data);
    ptr_res_deposit_.push_back(item_data);

    QTableWidgetItem *item_rate = ui->deposit_result->item(i, 1);
    item_rate =
        new QTableWidgetItem(QString::number(iter->rate_payment_, 'f', 2));
    ui->deposit_result->setItem(i, 1, item_rate);
    ptr_res_deposit_.push_back(item_rate);

    QTableWidgetItem *item_balance_change = ui->deposit_result->item(i, 2);
    item_balance_change =
        new QTableWidgetItem(QString::number(iter->balance_changing_, 'f', 2));
    ui->deposit_result->setItem(i, 2, item_balance_change);
    ptr_res_deposit_.push_back(item_balance_change);

    QTableWidgetItem *item_balance_ = ui->deposit_result->item(i, 3);
    item_balance_ =
        new QTableWidgetItem(QString::number(iter->balance_, 'f', 2));
    ui->deposit_result->setItem(i, 3, item_balance_);
    ptr_res_deposit_.push_back(item_balance_);
  }
}

void MainWindow::ButtonsConnect() {
  connect(ui->pb0, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb1, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb2, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb3, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb4, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb5, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb6, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb7, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb8, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb9, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb_x, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb_div, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb_mul, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb_minus, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb_plus, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pb_dot, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->cos, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->sin, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->tan, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->sqrt, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->asin, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->acos, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->atan, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->ln, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->log, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->pow, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->l_bracket, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->r_bracket, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->exp, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->mod, &QPushButton::clicked, this, &MainWindow::MakeStr);
  connect(ui->AC, &QPushButton::clicked, this, &MainWindow::ClearAllElements);
  connect(ui->pb_ce, &QPushButton::clicked, this, &MainWindow::ClearElement);
  connect(ui->pb_result, &QPushButton::clicked, this, &MainWindow::CalcResult);
  connect(ui->make_graph, &QPushButton::clicked, this, &MainWindow::MakeGraph);
  connect(ui->graph_clear, &QPushButton::clicked, this,
          &MainWindow::ClearGraphItems);
  connect(ui->add_into_add, &QPushButton::clicked, this,
          &MainWindow::AddIntoAddList);
  connect(ui->delete_from_add, &QPushButton::clicked, this,
          &MainWindow::DeleteFromAddList);
  connect(ui->add_into_sub, &QPushButton::clicked, this,
          &MainWindow::AddIntoSubList);
  connect(ui->delete_from_sub, &QPushButton::clicked, this,
          &MainWindow::DeleteFromSubList);
  connect(ui->list_add, &QTableWidget::cellClicked, this,
          &MainWindow::SetRowColAddList);
  connect(ui->list_sub, &QTableWidget::cellClicked, this,
          &MainWindow::SetRowColSubList);
  connect(ui->calc_deposit, &QPushButton::clicked, this,
          &MainWindow::CalcDeposit);
  connect(ui->calc_credit, &QPushButton::clicked, this,
          &MainWindow::CalcCredit);
}

}  // namespace calc
