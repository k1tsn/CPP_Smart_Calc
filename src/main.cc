#include <QApplication>

#include "controller/controller.h"
#include "mainwindow.h"
#include "model/model.h"

int main(int argc, char *argv[]) {
  calc::Model model;
  calc::Controller controller(&model);
  QApplication a(argc, argv);
  calc::MainWindow w(nullptr, &controller);
  w.setWindowTitle("SmartCalc");
  w.resize(693, 646);
  w.setFixedSize(693, 646);
  w.show();
  return a.exec();
}
