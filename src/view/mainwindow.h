#ifndef SMART_CALC_SRC_VIEW_MAINWINDOW
#define SMART_CALC_SRC_VIEW_MAINWINDOW

#include <QMainWindow>
#include <QTableWidget>
#include <list>
#include <string>
#include <vector>

#include "../controller/controller.h"
#include "drawgraph.h"

namespace Ui {

class MainWindow;

}  // namespace Ui

namespace calc {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr, calc::Controller *controller = nullptr);
  ~MainWindow();
  void MakeStr();
  void CalcResult();
  void ClearElement();
  void ClearAllElements();
  void ClearGraphItems();
  void ButtonsConnect();
  void MakeGraph();
  void AddIntoAddList();
  void DeleteFromAddList();
  void AddIntoSubList();
  void DeleteFromSubList();
  void SetRowColAddList(int r, int c);
  void SetRowColSubList(int r, int c);
  void CalcCredit();
  void CalcDeposit();
  void ViewResultForCredit();
  void ViewResultForDeposit();

 private:
  void ClearAddSubTable(std::list<QTableWidgetItem *> ptr_date,
                        std::list<QTableWidgetItem *> ptr_amount);
  void ClearResTable(std::vector<QTableWidgetItem *> ptr);

  calc::Controller *controller_;
  Ui::MainWindow *ui;
  std::string str_;
  DrawGraph *ptr_to_graph_;
  int row_add_list_;
  int column_add_list_;
  int row_sub_list_;
  int column_sub_list_;
  std::list<QTableWidgetItem *> ptr_item_date_add_;
  std::list<QTableWidgetItem *> ptr_item_amount_add_;
  std::list<QTableWidgetItem *> ptr_item_date_sub_;
  std::list<QTableWidgetItem *> ptr_item_amount_sub_;
  std::vector<QTableWidgetItem *> ptr_res_deposit_;
  std::vector<QTableWidgetItem *> ptr_res_credit_;
};

}  // namespace calc

#endif  // SMART_CALC_SRC_VIEW_MAINWINDOW
