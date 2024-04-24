#ifndef SMART_CALC_SRC_MODEL_CALCULATION
#define SMART_CALC_SRC_MODEL_CALCULATION

#include <list>
#include <string>

#include "token.h"

namespace calc {

/// @brief Сlass storing references to binary functions
class OperatorBin {
 public:
  OperatorBin() {}
  OperatorBin(int key, std::string name, double (*func_ptr)(double, double))
      : key_(key), name_(name), func_ptr_(func_ptr) {}
  ~OperatorBin() {}
  int key_;
  std::string name_;
  double (*func_ptr_)(double, double);
};

/// @brief Сlass storing references to unary functions
class OperatorUn {
 public:
  OperatorUn() {}
  OperatorUn(int key, std::string name, double (*func_ptr)(double))
      : key_(key), name_(name), func_ptr_(func_ptr) {}
  ~OperatorUn() {}
  int key_;
  std::string name_;
  double (*func_ptr_)(double);
};

class Calculation {
 public:
  Calculation() {}
  ~Calculation() {}

  /// @brief Computes the result of an expression in reverse Polish notation
  /// @param res The result is written to the res variable
  /// @return Returns the error code
  int8_t CalcResult(double& res);

  /// @brief Checks an expression and converts it to reverse Polish notation
  /// @param input_str Input expression in infix notation
  /// @return Returns the error code
  int8_t CheckAndConvertStr(std::string& input_str);

  std::string GetErrorName(int8_t err);
  int8_t SetX(std::string& x);

 private:
  PolishNotation token_;
  std::list<OperatorBin> list_bin_opr_;
  std::list<OperatorUn> list_un_opr_;
  std::string x_;
};

}  // namespace calc

#endif  // SMART_CALC_SRC_MODEL_CALCULATION
