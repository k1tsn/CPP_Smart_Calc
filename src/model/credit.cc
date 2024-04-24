#include "credit.h"

#include <cmath>
#include <string>

namespace calc {

int8_t Credit::SetValForCredit(CreditSettings& settings) {
  if (CheckValue(settings.amount_) != 0 || CheckValue(settings.term_) != 0 ||
      CheckValue(settings.rate_))
    return CreditError::kIncorrectVal;
  amount_ = std::stod(settings.amount_);
  term_ = std::stoi(settings.term_);
  rate_ = std::stod(settings.rate_);

  if (settings.type_ == "Аннуитетный") {
    type_ = kAnnuity;
  } else {
    type_ = kDifferentiated;
  }

  if (settings.month_or_year_ == "год(а)") term_ *= 12;

  date_ = settings.date_;

  return CreditError::kOk;
}

int8_t Credit::CheckValue(const std::string& str) const {
  for (size_t i = 0; i < str.length(); ++i) {
    if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '.')) {
      return CreditError::kIncorrectVal;
    }
  }
  return CreditError::kOk;
}

void Credit::CalcCredit(double& overpayment, double& total_payout,
                        std::vector<CreditResult>& credit_result) {
  if (type_ == kAnnuity) {
    double share = rate_ / 100 / 12;
    result_.monthly_payment_ =
        amount_ * (share + share / (pow(1 + share, term_) - 1));
    for (int i = 0; i < term_; ++i) {
      result_.rate_payment_ = share * amount_;  // платеж по процентам
      result_.total_pay_ = result_.monthly_payment_ -
                           result_.rate_payment_;  // платеж по основному долгу
      overpayment += result_.rate_payment_;  // переплата
      amount_ -= result_.total_pay_;
      total_payout += result_.monthly_payment_;
      result_.balance_owed_ = amount_;
      result_.out_date_ = date_.DateToString();
      credit_result.push_back(result_);
      date_.AddMonthToDate(1);
    }
  } else {
    double share = rate_ / 100;
    result_.total_pay_ = amount_ / term_;  // платеж по основному долгу
    for (int i = 0; i < term_; ++i) {
      result_.rate_payment_ = amount_ * share / 12;  // платеж по процентам
      result_.monthly_payment_ = result_.total_pay_ + result_.rate_payment_;
      overpayment += result_.rate_payment_;  // переплата
      amount_ -= result_.total_pay_;
      total_payout += result_.monthly_payment_;
      result_.balance_owed_ = amount_;
      result_.out_date_ = date_.DateToString();
      credit_result.push_back(result_);
      date_.AddMonthToDate(1);
    }
  }
}

}  // namespace calc
