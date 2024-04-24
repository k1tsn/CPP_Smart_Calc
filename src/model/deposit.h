#ifndef SMART_CALC_SRC_MODEL_DEPOSIT
#define SMART_CALC_SRC_MODEL_DEPOSIT

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "date.h"

namespace calc {

/// @brief Structure of input data for a deposit
struct DepositSettings {
  std::string amount_;
  std::string term_;
  std::string day_month_year_;
  std::string date_;
  std::string rate_;
  bool is_capital_;
  std::string capitalization_;
};

/// @brief Structure of the output data for the deposit. Used for table
class DepositResult {
 public:
  void Clear();
  std::string out_date_;
  double rate_payment_;
  double balance_changing_;
  double balance_;
};

class Deposit {
 public:
  enum Capitalization : int8_t {
    kEveryDay,
    kEveryWeek,
    kEveryMonth,
    kOnceAQuarter,
    kSemiannually,
    kOnceAYear,
  };

  enum DepostError : int8_t {
    kOK,
    kError,
  };

  enum DepositRate : int8_t {
    kRateDay,
    kRateMonth,
    kRateYear,
  };

  Deposit() {}
  ~Deposit() {}
  int8_t SetValToDeposit(DepositSettings& settings);

  /// @brief Adds values to the replenishment sheet
  /// @param date
  /// @param amount
  /// @return Returns an error code if the data is incorrect
  int8_t AddInInputList(std::string& date, std::string& amount);

  /// @brief Adds values to the withdrawal sheet
  /// @param date
  /// @param amount
  /// @return Returns an error code if the data is incorrect
  int8_t AddInOutList(std::string& date, std::string& amount);

  /// @brief Calc deposit
  /// @param tax_amount Tax at the end of the term
  /// @param rate Interest charges
  /// @param amount_end Total payment at the end of the term
  /// @param res Vector of output values. Used for table
  void CalcDeposit(double& tax_amount, double& rate, double& amount_end,
                   std::vector<DepositResult>& res);

 private:
  int8_t CheckValue(const std::string& str) const;
  void SetCapitalization(std::string& capitalization);
  void AddInInpOutList(std::string& date, double amount);

  /// @brief Calculates the expiration date
  /// @return Expiration date
  Date FindTerm();

  /// @brief Calculates values and enters them into a vector of output values
  /// for daily payout/daily capitalization
  /// @param accumulation Accumulation of interest per day
  /// @param res Vector of output values
  void CalcEveryDay(double& accumulation, std::vector<DepositResult>& res);

  /// @brief Calculates values and enters them into a vector of output values
  /// for other payout/other capitalization
  /// @param accumulation Accumulation of interest per day
  /// @param res Vector of output values
  void CalcEveryOther(double& accumulation, std::vector<DepositResult>& res);

  /// @brief If the list of deposits/withdrawals is not empty, calculates along
  /// with it
  /// @param res Vector of output values
  /// @param iter Iterator for the map of deposits/withdrawals
  /// @param amount_end Total payment at the end of the term
  void CalcWithAddSub(std::vector<DepositResult>& res,
                      std::map<Date, double>::iterator& iter,
                      double& amount_end);

  /// @brief Calculates tax rate
  /// @param rate_on_year Savings for the year or end of term
  /// @return Tax rate
  double CalcTax(double& rate_on_year);

  Date date_start_;
  std::map<Date, double> list_add_out_;

  double deposit_amount_;  // сумма вклада
  int deposit_term_;       // срок размещения
  int8_t day_month_year_;  // срок размещения в днях, месяцах или годах
  double interest_rate_;  // процентная ставка
  bool is_capital_;       // требуется ли капитализация
  uint8_t capitalization_;  // периодичность выплат или капитализация

  const double tax_rate_ = 16;
  double tax_amount_;

  DepositResult dep_res_;
};

}  // namespace calc

#endif  // SMART_CALC_SRC_MODEL_DEPOSIT
