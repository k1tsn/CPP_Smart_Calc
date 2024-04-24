#include "controller.h"

#include <string>
#include <utility>
#include <vector>

namespace calc {

Controller::Controller(Model* model) : model_(model) {}

Controller::~Controller() {}

int8_t Controller::SetExprForCalc(std::string& expr) {
  return model_->SetExpressionForCalc(expr);
}

int8_t Controller::SetXForCalc(std::string& x) {
  return model_->SetXForCalc(x);
}

int8_t Controller::GetResultFromClac(double& res) {
  return model_->GetResultFromCalc(res);
}

std::string Controller::GetErrorName(int8_t err) {
  return model_->GetErrorName(err);
}

int8_t Controller::SetExprForGraph(std::string& expr) {
  return model_->SetExprForGraph(expr);
}

int8_t Controller::SetRangeXForGraph(const std::string& min_x,
                                     const std::string& max_x) {
  return model_->SetRangeXForGraph(min_x, max_x);
}

int8_t Controller::SetRangeYForGraph(const std::string& min_y,
                                     const std::string& max_y) {
  return model_->SetRangeYForGraph(min_y, max_y);
}

void Controller::SetDivStep(int div_step) { model_->SetDivStep(div_step); }

void Controller::SetSizePix(int pix) { model_->SetSizePix(pix); }

double Controller::GetStepX() { return model_->GetStepX(); }

double Controller::GetStepY() { return model_->GetStepY(); }

void Controller::SetHightForGraph(int hight) {
  model_->SetHightForGraph(hight);
}

void Controller::SetWeightForGraph(int weight) {
  model_->SetWeightForGraph(weight);
}

void Controller::GetResultFromGraph(std::vector<double>& x,
                                    std::vector<double>& y) {
  model_->GetResultFromGraph(x, y);
}

int8_t Controller::SetValueForCredit(CreditSettings& settings) {
  return model_->SetValueForCredit(settings);
}

void Controller::GetResultFromCredit(double& overpayment, double& total_payout,
                                     std::vector<CreditResult>& credit_result) {
  model_->GetResultFromCredit(overpayment, total_payout, credit_result);
}

int8_t Controller::SetAddForDeposit(std::string& date, std::string& amount) {
  return model_->SetAddForDeposit(date, amount);
}

int8_t Controller::SetSubForDeposit(std::string& date, std::string& amount) {
  return model_->SetSubForDeposit(date, amount);
}

int8_t Controller::SetValForDeposit(DepositSettings& settings) {
  return model_->SetValueForDeposit(settings);
}

void Controller::GetResultFromDeposit(double& tax_amount, double& rate,
                                      double& amount_end,
                                      std::vector<DepositResult>& res) {
  model_->GetResultFromDeposit(tax_amount, rate, amount_end, res);
}

}  // namespace calc
