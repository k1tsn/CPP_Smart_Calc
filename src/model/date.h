#ifndef SMART_CALC_SRC_MODEL_DATE
#define SMART_CALC_SRC_MODEL_DATE

#include <string>

namespace calc {

/// @brief Class for working with dates
class Date {
 public:
  Date();
  Date(std::string& date);
  Date(const Date& other);
  ~Date();
  void SetDate(std::string& date);
  int8_t GetDay() const { return day_; }
  int8_t GetMonth() const { return month_; }
  int GetYear() const { return year_; }
  int8_t GetDayInMonth() const;
  void AddMonthToDate(int count);
  void AddDayToDate(int count);
  int16_t GetDayInYear() const;
  int8_t operator++();
  bool operator==(const Date& other) const;
  bool operator!=(const Date& other) const;
  bool operator<(const Date& other) const;
  Date& operator=(std::string& date);
  std::string DateToString() const;
  bool isEndYear() const;

 private:
  bool IsNum(char s) const;
  int8_t day_;
  int8_t month_;
  int16_t year_;
};

}  // namespace calc

#endif  // SMART_CALC_SRC_MODEL_DATE