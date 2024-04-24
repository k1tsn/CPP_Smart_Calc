#ifndef SMART_CALC_SRC_MODEL_CREDIT
#define SMART_CALC_SRC_MODEL_CREDIT

#include <string>
#include <vector>

#include "date.h"

namespace calc {

/// @brief Structure of input data for a loan
struct CreditSettings {
  std::string amount_;
  std::string term_;
  std::string rate_;
  std::string type_;
  std::string month_or_year_;
  std::string date_;
};

/// @brief Output structure for credit. Used for table
struct CreditResult {
  std::string out_date_;
  double monthly_payment_;
  double total_pay_;
  double rate_payment_;
  double balance_owed_;
};

class Credit {
  enum CreditError {
    kOk,
    kIncorrectVal,
  };

  enum CreditType {
    kAnnuity,
    kDifferentiated,
  };

 public:
  Credit() {}
  ~Credit() {}

  /// @brief Receives input data
  /// @param settings Structure of input data
  /// @return Returns an error code if the data is incorrect
  int8_t SetValForCredit(CreditSettings& settings);

  void CalcCredit(double& overpayment, double& total_payout,
                  std::vector<CreditResult>& credit_result);

 private:
  int8_t CheckValue(const std::string& str) const;
  double amount_;
  int term_;
  double rate_;
  CreditType type_;
  Date date_;

  CreditResult result_;
};

}  // namespace calc

#endif  // SMART_CALC_SRC_MODEL_CREDIT
