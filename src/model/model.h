#ifndef SMART_CALC_SRC_MODEL_MODEL
#define SMART_CALC_SRC_MODEL_MODEL

#include <string>

#include "calculation.h"
#include "credit.h"
#include "deposit.h"
#include "graph.h"

namespace calc {

class Model {
 public:
  Model();
  ~Model();

  // for calc
  int8_t SetExpressionForCalc(std::string& expr);
  int8_t SetXForCalc(std::string& x);
  int8_t GetResultFromCalc(double& res);
  std::string GetErrorName(int8_t err);

  // for graph
  int8_t SetExprForGraph(std::string& expr);
  int8_t SetRangeXForGraph(const std::string& min_x, const std::string& max_x);
  int8_t SetRangeYForGraph(const std::string& min_y, const std::string& max_y);
  void SetDivStep(int div_step);
  void SetSizePix(int pix);
  void SetHightForGraph(int hight);
  void SetWeightForGraph(int weight);
  void GetResultFromGraph(std::vector<double>& x, std::vector<double>& y);
  double GetStepX();
  double GetStepY();

  // for credit
  int8_t SetValueForCredit(CreditSettings& settings);
  void GetResultFromCredit(double& overpayment, double& total_payout,
                           std::vector<CreditResult>& credit_result);

  // for deposit
  int8_t SetAddForDeposit(std::string& date, std::string& amount);
  int8_t SetSubForDeposit(std::string& date, std::string& amount);
  int8_t SetValueForDeposit(DepositSettings& settings);
  void GetResultFromDeposit(double& tax_amount, double& rate,
                            double& amount_end,
                            std::vector<DepositResult>& res);

 private:
  Calculation* calc_;
  Graph* graph_;
  Credit* credit_;
  Deposit* deposit_;
};

}  // namespace calc

#endif  // SMART_CALC_SRC_MODEL_MODEL
