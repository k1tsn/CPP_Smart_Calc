#include "calculation.h"

#include <cmath>
#include <list>
#include <string>

namespace calc {

static double sum(double a, double b) { return a + b; }

static double sub(double a, double b) { return a - b; }

static double mul(double a, double b) { return a * b; }

static double div(double a, double b) { return a / b; }

static double sub_un(double a) { return -a; }

static double s21_pow(double a, double b) {
  if (a == 0 && b == 0) return NAN;
  return std::pow(a, b);
}

int8_t Calculation::CheckAndConvertStr(std::string& input_str) {
  int8_t error = token_.FromStrToToken(input_str);
  if (error == ErrorCode::kOK) {
    error = token_.ConvertToPolishNotation();
    if (error != ErrorCode::kOK) return error;
  } else
    return error;
  list_bin_opr_ = {OperatorBin(TokenKey::kItsOperatorSumSub, "+", sum),
                   OperatorBin(TokenKey::kItsOperatorSumSub, "-", sub),
                   OperatorBin(TokenKey::kItsOperatorMulDiv, "*", mul),
                   OperatorBin(TokenKey::kItsOperatorMulDiv, "/", div),
                   OperatorBin(TokenKey::kItsOperatorPow, "^", s21_pow),
                   OperatorBin(TokenKey::kItsOperatorMulDiv, "%", fmod)};
  list_un_opr_ = {OperatorUn(TokenKey::kItsFunc, "sin", sin),
                  OperatorUn(TokenKey::kItsFunc, "cos", cos),
                  OperatorUn(TokenKey::kItsFunc, "tan", tan),
                  OperatorUn(TokenKey::kItsFunc, "acos", acos),
                  OperatorUn(TokenKey::kItsFunc, "asin", asin),
                  OperatorUn(TokenKey::kItsFunc, "atan", atan),
                  OperatorUn(TokenKey::kItsFunc, "sqrt", sqrt),
                  OperatorUn(TokenKey::kItsFunc, "ln", log),
                  OperatorUn(TokenKey::kItsFunc, "log", log10),
                  OperatorUn(TokenKey::kItsFunc, "exp", exp),
                  OperatorUn(TokenKey::kItsOperatorSumSub, "~", sub_un)};
  return ErrorCode::kOK;
}

int8_t Calculation::CalcResult(double& res) {
  std::list<Token> out_str;
  token_.GetOutStr(out_str);
  std::list<double> stack_num;
  for (auto iter = out_str.begin(); iter != out_str.end(); ++iter) {
    if ((*iter).key_ == TokenKey::kItsNum) {
      try {
        if ((*iter).value_ == "x") {
          (*iter).value_ = x_;
          stack_num.push_back(std::stod((*iter).value_));
          (*iter).value_ = "x";
        } else
          stack_num.push_back(std::stod((*iter).value_));
      } catch (...) {
        return ErrorCode::kUndefinedToken;
      }
    } else if ((*iter).key_ >= 1 && (*iter).key_ <= 3 &&
               (*iter).value_ != "~") {
      if (stack_num.size() < 2) return ErrorCode::kMissNum;
      double num2 = stack_num.back();
      stack_num.pop_back();
      double num1 = stack_num.back();
      for (auto iter_list = list_bin_opr_.begin();
           iter_list != list_bin_opr_.end(); ++iter_list) {
        if ((*iter_list).name_ == (*iter).value_) {
          stack_num.back() = (*iter_list).func_ptr_(num1, num2);
          break;
        }
      }
    } else {
      double num = stack_num.back();
      for (auto iter_list = list_un_opr_.begin();
           iter_list != list_un_opr_.end(); ++iter_list) {
        if ((*iter_list).name_ == (*iter).value_) {
          stack_num.back() = (*iter_list).func_ptr_(num);
          break;
        }
      }
    }
  }
  res = stack_num.back();
  if (std::isnan(res) || std::isinf(res)) return ErrorCode::kIncorrectExpr;
  return ErrorCode::kOK;
}

int8_t Calculation::SetX(std::string& x) {
  for (size_t i = 0; i < x.length(); ++i) {
    if (!((x[i] >= '0' && x[i] <= '9') || x[i] == '.' || x[i] == '-' ||
          x[i] == '+')) {
      return ErrorCode::kUndefinedToken;
    }
  }
  x_.swap(x);
  return ErrorCode::kOK;
}

std::string Calculation::GetErrorName(int8_t err) {
  return token_.GetErrorName(err);
}

}  // namespace calc
