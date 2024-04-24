#include "drawgraph.h"

#include <QPainter>
#include <cmath>
#include <vector>

#include "ui_drawgraph.h"

namespace calc {

DrawGraph::DrawGraph(QWidget *parent) : QWidget(parent), ui(new Ui::DrawGraph) {
  ui->setupUi(this);
}

DrawGraph::~DrawGraph() { delete ui; }

void DrawGraph::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter;
  painter.begin(this);
  PaintBackground(&painter);
  PaintGridGraphics(&painter);
  PaintAxis(&painter);

  if (x_.size() > 0) {
    QPen pen_dot(QColor(12, 30, 162));
    pen_dot.setWidth(2);
    QBrush brush_dot(QColor(12, 30, 162), Qt::SolidPattern);
    painter.setBrush(brush_dot);
    painter.setPen(pen_dot);

    for (size_t i = 0; i < x_.size() - 1; i += 1) {
      if (y_[i] > hight_rect_ / 2 || y_[i] < hight_rect_ / -2) continue;
      if (y_[i + 1] > hight_rect_ / 2 || y_[i + 1] < hight_rect_ / -2) continue;
      if (std::isnan(y_[i]) || std::isnan(y_[i + 1])) continue;
      if (std::isinf(y_[i]) || std::isinf(y_[i + 1])) continue;
      painter.drawLine(QPointF(x_[i], y_[i]), QPointF(x_[i + 1], y_[i + 1]));
    }
  }

  painter.end();
}

void DrawGraph::PaintBackground(QPainter *painter) {
  painter->eraseRect(pos_x_, pos_y_, weight_rect_, hight_rect_);
  QBrush brush(QColor(255, 255, 255), Qt::SolidPattern);
  painter->setBrush(brush);

  QPen pen_rect(QColor(55, 55, 55));
  pen_rect.setWidth(5);
  painter->setPen(pen_rect);
  painter->drawRect(pos_x_, pos_y_, weight_rect_, hight_rect_);
  painter->translate(weight_rect_ / 2, hight_rect_ / 2);
}

void DrawGraph::PaintGridGraphics(QPainter *painter) {
  int count_division = weight_rect_ / division_step_;
  int div_step_start = 0;
  QPen pen(QColor(200, 200, 204));
  painter->setPen(pen);

  for (int i = 0; i < count_division - 1; i++) {
    div_step_start += division_step_;
    painter->drawLine(-weight_rect_ / 2 + 4, -hight_rect_ / 2 + div_step_start,
                      weight_rect_ / 2 - 4, -hight_rect_ / 2 + div_step_start);
    painter->drawLine(-weight_rect_ / 2 + div_step_start, -hight_rect_ / 2 + 4,
                      -weight_rect_ / 2 + div_step_start, hight_rect_ / 2 - 4);
  }
}

void DrawGraph::PaintAxis(QPainter *painter) {
  int count_division = weight_rect_ / division_step_;
  int div_step_start = 0;

  QPen pen_lines(QColor(55, 55, 55));
  pen_lines.setWidth(1);
  painter->setPen(pen_lines);

  painter->drawLine(-weight_rect_ / 2, 0, weight_rect_ / 2, 0);
  painter->drawLine(0, -hight_rect_ / 2, 0, hight_rect_ / 2);

  for (int i = 0; i < count_division; i++) {
    div_step_start += division_step_;
    painter->drawLine(-weight_rect_ / 2 + div_step_start, -3,
                      -weight_rect_ / 2 + div_step_start, 3);
    painter->drawLine(-3, -hight_rect_ / 2 + div_step_start, 3,
                      -hight_rect_ / 2 + div_step_start);
  }
}

void DrawGraph::SetXYPoints(std::vector<double> &x, std::vector<double> &y) {
  x_.clear();
  y_.clear();
  x_.swap(x);
  y_.swap(y);
  x.clear();
  y.clear();
}

int DrawGraph::GetWeight() { return weight_rect_; }

int DrawGraph::GetHight() { return hight_rect_; }

int DrawGraph::GetSizePix() { return size_pix_; }

int DrawGraph::GetDivStep() { return division_step_; }

}  // namespace calc
