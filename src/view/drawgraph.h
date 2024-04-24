#ifndef SMART_CALC_SRC_VIEW_DRAWGRAPH
#define SMART_CALC_SRC_VIEW_DRAWGRAPH

#include <QPaintEvent>
#include <QWidget>
#include <string>
#include <vector>

namespace Ui {
class DrawGraph;
}

namespace calc {
class DrawGraph : public QWidget {
  Q_OBJECT

 public:
  explicit DrawGraph(QWidget *parent);
  ~DrawGraph();
  void paintEvent(QPaintEvent *event) override;
  void PaintBackground(QPainter *painter);
  void PaintGridGraphics(QPainter *painter);
  void PaintAxis(QPainter *painter);
  int GetWeight();
  int GetHight();
  int GetSizePix();
  int GetDivStep();
  void SetXYPoints(std::vector<double> &x, std::vector<double> &y);

 private:
  Ui::DrawGraph *ui;
  const int pos_x_ = 0;
  const int pos_y_ = 0;
  const int weight_rect_ = 420;
  const int hight_rect_ = 420;
  const int division_step_ = 10;
  const int size_pix_ = weight_rect_ * hight_rect_;
  std::vector<double> x_;
  std::vector<double> y_;
};
}  // namespace calc

#endif  // SMART_CALC_SRC_VIEW_DRAWGRAPH
