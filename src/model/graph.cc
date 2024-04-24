#include "graph.h"

#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

namespace calc {

int8_t Graph::SetExpression(std::string& expr) {
  return expression_.CheckAndConvertStr(expr);
}

int8_t Graph::SetRangeX(const std::string& min_x, const std::string& max_x) {
  if (min_x.empty() || max_x.empty()) return ErrorGraph::kRangeIncorrect;
  if (CheckValue(min_x) != 0 || CheckValue(max_x) != 0)
    return ErrorGraph::kRangeIncorrect;
  min_x_ = std::stod(min_x);
  max_x_ = std::stod(max_x);

  if (min_x_ >= max_x_ || fabs(min_x_) != fabs(max_x_))
    return ErrorGraph::kRangeIncorrect;

  return ErrorGraph::kOk;
}

int8_t Graph::SetRangeY(const std::string& min_y, const std::string& max_y) {
  if (min_y.empty() || max_y.empty()) return ErrorGraph::kRangeIncorrect;
  if (CheckValue(min_y) != 0 || CheckValue(max_y) != 0)
    return ErrorGraph::kRangeIncorrect;
  min_y_ = std::stod(min_y);
  max_y_ = std::stod(max_y);

  if (min_y_ >= max_y_ || fabs(min_y_) != fabs(max_y_))
    return ErrorGraph::kRangeIncorrect;

  return ErrorGraph::kOk;
}

int8_t Graph::CheckValue(const std::string& str) const {
  for (size_t i = 0; i < str.length(); ++i) {
    if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '+' ||
          str[i] == '-')) {
      return ErrorGraph::kRangeIncorrect;
    }
  }
  return ErrorGraph::kOk;
}

void Graph::SetHight(int hight) { hight_ = hight; }

void Graph::SetWeight(int weight) { weight_ = weight; }

void Graph::SetSizePix(int pix) { size_pix_ = pix; }

void Graph::SetDivStep(int div_step) { div_step_ = div_step; }

double Graph::FindStepX() const { return fabs(min_x_ / size_pix_ * 2); }

double Graph::FindStepPixX() const { return weight_ / fabs(max_x_) / 2; }

double Graph::FindStepPixY() const { return hight_ / fabs(max_y_) / 2; }

double Graph::GetStepX() const { return div_step_ / FindStepPixX(); }

double Graph::GetStepY() const { return div_step_ / FindStepPixY(); }

void Graph::CalcGraph(std::vector<double>& x, std::vector<double>& y) {
  x.reserve(size_pix_ + 1);
  y.reserve(size_pix_ + 1);

  double step = FindStepX();
  double step_pix_x = FindStepPixX();
  double step_pix_y = FindStepPixY();

  for (size_t i = 0; i < size_pix_ + 1; ++i) {
    double res;
    std::string min_x = std::to_string(min_x_);
    expression_.SetX(min_x);
    expression_.CalcResult(res);
    x.push_back(min_x_ * step_pix_x);
    y.push_back(res * step_pix_y * -1);
    min_x_ += step;
  }
}

}  // namespace calc
