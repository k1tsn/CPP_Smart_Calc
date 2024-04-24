#ifndef SMART_CALC_SRC_CONTROLLER_CONTROLLER
#define SMART_CALC_SRC_CONTROLLER_CONTROLLER

#include <string>
#include <vector>

#include "../model/model.h"

namespace calc {

class Controller {
 public:
  Controller() {}
  Controller(Model* model);
  ~Controller();

  // for calc:
  int8_t SetExprForCalc(std::string& expr);
  int8_t SetXForCalc(std::string& x);
  int8_t GetResultFromClac(double& res);
  std::string GetErrorName(int8_t err);

  // for graph
  int8_t SetExprForGraph(std::string& expr);
  int8_t SetRangeXForGraph(const std::string& min_x, const std::string& max_x);
  int8_t SetRangeYForGraph(const std::string& min_y, const std::string& max_y);
  void SetDivStep(int div_step);
  void SetSizePix(int pix);
  void SetHightForGraph(int hight);
  void SetWeightForGraph(int weight);
  double GetStepX();
  double GetStepY();
  void GetResultFromGraph(std::vector<double>& x, std::vector<double>& y);

  // for credit
  int8_t SetValueForCredit(CreditSettings& settings);
  void GetResultFromCredit(double& overpayment, double& total_payout,
                           std::vector<CreditResult>& credit_result);

  // for deposit
  int8_t SetAddForDeposit(std::string& date, std::string& amount);
  int8_t SetSubForDeposit(std::string& date, std::string& amount);
  int8_t SetValForDeposit(DepositSettings& settings);
  void GetResultFromDeposit(double& tax_amount, double& rate,
                            double& amount_end,
                            std::vector<DepositResult>& res);

 private:
  Model* model_;
};

}  // namespace calc

#endif  // SMART_CALC_SRC_CONTROLLER_CONTROLLER
