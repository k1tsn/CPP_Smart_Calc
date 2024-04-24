#include "date.h"

#include <string>

namespace calc {
Date::Date() {}

Date::Date(std::string& date) { SetDate(date); }

Date::Date(const Date& other) {
  day_ = other.day_;
  month_ = other.month_;
  year_ = other.year_;
}

Date::~Date() {}

Date& Date::operator=(std::string& date) {
  SetDate(date);
  return *this;
}

void Date::SetDate(std::string& date) {
  std::string day;
  std::string month;
  std::string year;
  size_t i = 0;
  while (IsNum(date[i])) {
    day.push_back(date[i]);
    ++i;
  }
  ++i;
  while (IsNum(date[i])) {
    month.push_back(date[i]);
    ++i;
  }
  ++i;
  while (IsNum(date[i])) {
    year.push_back(date[i]);
    ++i;
  }
  day_ = std::stoi(day);
  month_ = std::stoi(month);
  year_ = std::stoi(year);
}

bool Date::IsNum(char s) const { return s >= '0' && s <= '9'; }

int8_t Date::GetDayInMonth() const {
  int8_t number_of_days = 30;
  if (month_ == 2) {
    if (GetDayInYear() == 366)
      return 29;
    else
      return 28;
  }
  if (month_ >= 1 && month_ < 8) {
    if (month_ % 2 != 0) return 31;
  }
  if (month_ >= 8 && month_ % 2 == 0) {
    return 31;
  }
  return number_of_days;
}

void Date::AddMonthToDate(int count) {
  month_ += count;
  while (month_ > 12) {
    month_ -= 12;
    ++year_;
  }
}

void Date::AddDayToDate(int count) {
  while (count > GetDayInYear()) {
    count -= GetDayInYear();
    ++year_;
  }
  day_ += count;
  while (day_ > GetDayInMonth()) {
    day_ -= GetDayInMonth();
    ++month_;
    if (month_ > 12) {
      month_ = 1;
      ++year_;
    }
  }
}

int16_t Date::GetDayInYear() const {
  int16_t count = 365;
  if ((year_ % 4 == 0 && year_ % 100 != 0) || (year_ % 400 == 0)) {
    ++count;
  }
  return count;
}

int8_t Date::operator++() {
  ++day_;
  if (day_ > GetDayInMonth()) {
    day_ = 1;
    ++month_;
  }
  if (month_ > 12) {
    month_ = 1;
    ++year_;
  }
  return day_;
}

bool Date::operator==(const Date& other) const {
  return day_ == other.day_ && month_ == other.month_ && year_ == other.year_;
}

bool Date::operator!=(const Date& other) const {
  return day_ != other.day_ || month_ != other.month_ || year_ != other.year_;
}

std::string Date::DateToString() const {
  std::string result;

  if (day_ < 10) result.push_back('0');
  std::string tmp_res = std::to_string(day_);
  result.insert(result.size(), tmp_res);
  result.push_back('.');

  if (month_ < 10) result.push_back('0');
  tmp_res = std::to_string(month_);
  result.insert(result.size(), tmp_res);
  result.push_back('.');

  tmp_res = std::to_string(year_);
  result.insert(result.size(), tmp_res);

  return result;
}

bool Date::operator<(const Date& other) const {
  if (GetYear() < other.GetYear()) {
    return true;
  } else if (GetYear() == other.GetYear()) {
    if (GetMonth() < other.GetMonth())
      return true;
    else if (GetMonth() == other.GetMonth()) {
      if (GetDay() < other.GetDay()) return true;
    }
  }
  return false;
}

bool Date::isEndYear() const { return day_ == 31 && month_ == 12; }

}  // namespace calc
