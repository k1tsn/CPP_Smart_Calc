#include "deposit.h"

#include <cmath>
#include <stdexcept>

namespace calc {

int8_t Deposit::SetValToDeposit(DepositSettings& settings) {
  if (CheckValue(settings.amount_) != 0 || CheckValue(settings.term_) != 0 ||
      CheckValue(settings.rate_) != 0)
    return DepostError::kError;
  deposit_amount_ = std::stod(settings.amount_);
  deposit_term_ = std::stoi(settings.term_);
  interest_rate_ = std::stod(settings.rate_);

  date_start_.SetDate(settings.date_);

  day_month_year_ = DepositRate::kRateDay;
  if (settings.day_month_year_ == "месяцев")
    day_month_year_ = DepositRate::kRateMonth;
  else if (settings.day_month_year_ == "лет")
    day_month_year_ = DepositRate::kRateYear;

  is_capital_ = settings.is_capital_;
  SetCapitalization(settings.capitalization_);
  tax_amount_ = 1000000 * tax_rate_ / 100;
  dep_res_.Clear();

  return DepostError::kOK;
}

int8_t Deposit::CheckValue(const std::string& str) const {
  for (size_t i = 0; i < str.length(); ++i) {
    if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '.')) {
      return DepostError::kError;
    }
  }
  return DepostError::kOK;
}

void Deposit::SetCapitalization(std::string& capitalization) {
  if (capitalization == "Раз в день")
    capitalization_ = Capitalization::kEveryDay;
  else if (capitalization == "Раз в неделю")
    capitalization_ = Capitalization::kEveryWeek;
  else if (capitalization == "Раз в месяц")
    capitalization_ = Capitalization::kEveryMonth;
  else if (capitalization == "Раз в квартал")
    capitalization_ = Capitalization::kOnceAQuarter;
  else if (capitalization == "Раз в полгода")
    capitalization_ = Capitalization::kSemiannually;
  else
    capitalization_ = Capitalization::kOnceAYear;
}

void DepositResult::Clear() {
  rate_payment_ = 0;
  balance_changing_ = 0;
  balance_ = 0;
}

void Deposit::AddInInpOutList(std::string& date, double amount) {
  Date inp_date(date);
  std::map<Date, double>::iterator iter = list_add_out_.find(inp_date);
  if (iter == list_add_out_.end())
    list_add_out_.insert({inp_date, amount});
  else
    iter->second += amount;
}

int8_t Deposit::AddInInputList(std::string& date, std::string& str_amount) {
  double amount;
  try {
    amount = std::stod(str_amount);
  } catch (...) {
    return DepostError::kError;
  }
  AddInInpOutList(date, amount);
  return DepostError::kOK;
}

int8_t Deposit::AddInOutList(std::string& date, std::string& str_amount) {
  double amount;
  try {
    amount = std::stod(str_amount);
  } catch (...) {
    return DepostError::kError;
  }
  AddInInpOutList(date, -amount);
  return DepostError::kOK;
}

void Deposit::CalcDeposit(double& tax_amount, double& rate, double& amount_end,
                          std::vector<DepositResult>& res) {
  Date term = FindTerm();
  int count_day = 1;
  int8_t start_day = date_start_.GetDay();
  int8_t start_month = date_start_.GetMonth();
  int8_t day_in_month = date_start_.GetDayInMonth();
  double accumulation = 0;
  std::map<Date, double>::iterator iter = list_add_out_.begin();
  ++date_start_;
  amount_end = deposit_amount_;
  tax_amount = 0;
  rate = 0;
  double rate_on_year = 0;
  dep_res_.balance_changing_ = 0;
  for (; date_start_ != term; ++count_day, ++date_start_) {
    dep_res_.rate_payment_ =
        deposit_amount_ * interest_rate_ / 100 / date_start_.GetDayInYear();
    accumulation += dep_res_.rate_payment_;
    rate += dep_res_.rate_payment_;
    rate_on_year += dep_res_.rate_payment_;
    if (capitalization_ == Capitalization::kEveryDay) {
      CalcEveryDay(accumulation, res);
    } else if (capitalization_ == Capitalization::kEveryWeek &&
               count_day == 7) {
      CalcEveryOther(accumulation, res);
      count_day = 0;
    } else if (capitalization_ == Capitalization::kEveryMonth &&
               count_day == day_in_month) {
      CalcEveryOther(accumulation, res);
      day_in_month = date_start_.GetDayInMonth();
      count_day = 0;
    } else if (capitalization_ == Capitalization::kOnceAQuarter) {
      int8_t count = date_start_.GetMonth() - start_month;
      if (date_start_.GetDay() == start_day && (count == 3 || count == -9)) {
        CalcEveryOther(accumulation, res);
        start_month = date_start_.GetMonth();
      }
    } else if (capitalization_ == Capitalization::kSemiannually) {
      int8_t count = date_start_.GetMonth() - start_month;
      if (date_start_.GetDay() == start_day && abs(count) == 6) {
        CalcEveryOther(accumulation, res);
        start_month = date_start_.GetMonth();
      }
    } else {
      if (count_day == date_start_.GetDayInYear()) {
        CalcEveryOther(accumulation, res);
        count_day = 0;
      }
    }
    CalcWithAddSub(res, iter, amount_end);
    if (date_start_.isEndYear()) tax_amount += CalcTax(rate_on_year);
  }
  amount_end += rate;
  tax_amount += CalcTax(rate_on_year);
  if (res.empty()) CalcEveryOther(accumulation, res);
  list_add_out_.clear();
}

void Deposit::CalcEveryDay(double& accumulation,
                           std::vector<DepositResult>& res) {
  if (is_capital_) {
    deposit_amount_ += accumulation;
    dep_res_.balance_changing_ = accumulation;
  }
  accumulation = 0;
  dep_res_.balance_ = deposit_amount_;
  dep_res_.out_date_ = date_start_.DateToString();
  res.push_back(dep_res_);
}

void Deposit::CalcEveryOther(double& accumulation,
                             std::vector<DepositResult>& res) {
  if (is_capital_) {
    deposit_amount_ += accumulation;
    dep_res_.balance_changing_ = accumulation;
  }
  dep_res_.rate_payment_ = accumulation;
  dep_res_.out_date_ = date_start_.DateToString();
  dep_res_.balance_ = deposit_amount_;
  res.push_back(dep_res_);
  accumulation = 0;
}

Date Deposit::FindTerm() {
  Date tmp = date_start_;
  if (day_month_year_ == DepositRate::kRateYear) {
    day_month_year_ = DepositRate::kRateMonth;
    deposit_term_ *= 12;
  }
  if (day_month_year_ == DepositRate::kRateMonth) {
    tmp.AddMonthToDate(deposit_term_);
  } else {
    tmp.AddDayToDate(deposit_term_);
  }
  tmp.AddDayToDate(1);
  return tmp;
}

double Deposit::CalcTax(double& rate_on_year) {
  double tax = 0;
  if (rate_on_year >= tax_amount_)
    tax = (rate_on_year - tax_amount_) * tax_rate_ / 100;
  rate_on_year = 0;
  return tax;
}

void Deposit::CalcWithAddSub(std::vector<DepositResult>& res,
                             std::map<Date, double>::iterator& iter,
                             double& amount_end) {
  if (list_add_out_.size() > 0 && iter->first == date_start_) {
    deposit_amount_ += iter->second;
    amount_end += iter->second;
    dep_res_.out_date_ = date_start_.DateToString();
    dep_res_.rate_payment_ = 0;
    dep_res_.balance_changing_ = iter->second;
    dep_res_.balance_ = deposit_amount_;
    res.push_back(dep_res_);
    ++iter;
    dep_res_.balance_changing_ = 0;
  }
}

}  // namespace calc
