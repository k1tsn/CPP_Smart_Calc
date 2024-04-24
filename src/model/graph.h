#ifndef SMART_CALC_SRC_MODEL_GRAPH
#define SMART_CALC_SRC_MODEL_GRAPH

#include <cstdint>
#include <string>
#include <vector>

#include "calculation.h"

namespace calc {

enum ErrorGraph {
  kOk,
  kRangeIncorrect,
  kIncorrectExpression,
};

class Graph {
 public:
  Graph() {}
  ~Graph() {}
  int8_t SetRangeX(const std::string& min_x, const std::string& max_x);
  int8_t SetRangeY(const std::string& min_y, const std::string& max_y);
  void SetHight(int hight);
  void SetWeight(int weight);

  /// @brief Sets the pixel size of the canvas on which the graph is displayed
  /// @param pix Number of pixels
  void SetSizePix(int pix);

  /// @brief Sets the grid step
  /// @param div_step Grid step
  void SetDivStep(int div_step);

  double GetStepX() const;
  double GetStepY() const;

  /// @brief Calculates x and y
  /// @param x Vector with x
  /// @param y Vector with y
  void CalcGraph(std::vector<double>& x, std::vector<double>& y);

  /// @brief Sets the expression for plotting
  /// @param expr Expression
  /// @return Returns an error code if the expression is invalid
  int8_t SetExpression(std::string& expr);

 private:
  double FindStepX() const;

  /// @brief Finds the value by which x is multiplied to display to scale
  /// @return Step pix for x
  double FindStepPixX() const;

  /// @brief Finds the value by which y is multiplied to display to scale
  /// @return Step pix for y
  double FindStepPixY() const;

  int8_t CheckValue(const std::string& str) const;

  double min_x_;
  double max_x_;
  double min_y_;
  double max_y_;
  int hight_;
  int weight_;
  int div_step_;
  size_t size_pix_;
  Calculation expression_;
};

}  // namespace calc

#endif  // SMART_CALC_SRC_MODEL_GRAPH
