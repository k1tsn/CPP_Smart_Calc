#include "model.h"

namespace calc {

Model::Model() {
  calc_ = new Calculation();
  graph_ = new Graph();
  credit_ = new Credit();
  deposit_ = new Deposit();
}

Model::~Model() {
  delete calc_;
  delete graph_;
  delete credit_;
  delete deposit_;
}

int8_t Model::SetExpressionForCalc(std::string& expr) {
  return calc_->CheckAndConvertStr(expr);
}

int8_t Model::SetXForCalc(std::string& x) { return calc_->SetX(x); }

int8_t Model::GetResultFromCalc(double& res) { return calc_->CalcResult(res); }

std::string Model::GetErrorName(int8_t err) { return calc_->GetErrorName(err); }

int8_t Model::SetExprForGraph(std::string& expr) {
  return graph_->SetExpression(expr);
}

int8_t Model::SetRangeXForGraph(const std::string& min_x,
                                const std::string& max_x) {
  return graph_->SetRangeX(min_x, max_x);
}

int8_t Model::SetRangeYForGraph(const std::string& min_y,
                                const std::string& max_y) {
  return graph_->SetRangeY(min_y, max_y);
}

void Model::SetDivStep(int div_step) { graph_->SetDivStep(div_step); }

void Model::SetSizePix(int pix) { graph_->SetSizePix(pix); }

double Model::GetStepX() { return graph_->GetStepX(); }

double Model::GetStepY() { return graph_->GetStepY(); }

void Model::SetHightForGraph(int hight) { graph_->SetHight(hight); }

void Model::SetWeightForGraph(int weight) { graph_->SetWeight(weight); }

void Model::GetResultFromGraph(std::vector<double>& x, std::vector<double>& y) {
  graph_->CalcGraph(x, y);
}

int8_t Model::SetValueForCredit(CreditSettings& settings) {
  return credit_->SetValForCredit(settings);
}

void Model::GetResultFromCredit(double& overpayment, double& total_payout,
                                std::vector<CreditResult>& credit_result) {
  credit_->CalcCredit(overpayment, total_payout, credit_result);
}

int8_t Model::SetAddForDeposit(std::string& date, std::string& amount) {
  return deposit_->AddInInputList(date, amount);
}

int8_t Model::SetSubForDeposit(std::string& date, std::string& amount) {
  return deposit_->AddInOutList(date, amount);
}

int8_t Model::SetValueForDeposit(DepositSettings& settings) {
  return deposit_->SetValToDeposit(settings);
}

void Model::GetResultFromDeposit(double& tax_amount, double& rate,
                                 double& amount_end,
                                 std::vector<DepositResult>& res) {
  deposit_->CalcDeposit(tax_amount, rate, amount_end, res);
}

}  // namespace calc
