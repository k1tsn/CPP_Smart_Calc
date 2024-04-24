#include <gtest/gtest.h>

#include <cmath>
#include <initializer_list>
#include <string>

#include "../src/model/credit.h"

TEST(Credit, Ann_1) {
  std::initializer_list<std::string> val = {
      "120000", "6", "8.5", "Аннуитетный", "мес.", "13.01.2024"};
  std::initializer_list<std::string>::iterator iter = val.begin();
  calc::CreditSettings set;
  set.amount_ = *iter;
  set.term_ = *++iter;
  set.rate_ = *++iter;
  set.type_ = *++iter;
  set.month_or_year_ = *++iter;
  set.date_ = *++iter;
  calc::Credit credit;
  credit.SetValForCredit(set);
  double overpay = 0;
  double total_pay = 0;
  std::vector<calc::CreditResult> res;
  credit.CalcCredit(overpay, total_pay, res);
  EXPECT_FLOAT_EQ(round(overpay * 10) / 10, 2992.5);
  EXPECT_FLOAT_EQ(round(total_pay * 10) / 10, 122992.5);
  EXPECT_FLOAT_EQ(round(res.back().monthly_payment_ * 100) / 100, 20498.75);
}

TEST(Credit, Ann_2) {
  std::initializer_list<std::string> val = {
      "120000", "13", "8.5", "Аннуитетный", "мес.", "13.01.2024"};
  std::initializer_list<std::string>::iterator iter = val.begin();
  calc::CreditSettings set;
  set.amount_ = *iter;
  set.term_ = *++iter;
  set.rate_ = *++iter;
  set.type_ = *++iter;
  set.month_or_year_ = *++iter;
  set.date_ = *++iter;
  calc::Credit credit;
  credit.SetValForCredit(set);
  double overpay = 0;
  double total_pay = 0;
  std::vector<calc::CreditResult> res;
  credit.CalcCredit(overpay, total_pay, res);
  EXPECT_FLOAT_EQ(round(overpay * 100) / 100, 6033.98);
  EXPECT_FLOAT_EQ(round(total_pay * 100) / 100, 126033.96);
  EXPECT_FLOAT_EQ(round(res.back().monthly_payment_ * 100) / 100, 9694.92);
}

TEST(Credit, Ann_3) {
  std::initializer_list<std::string> val = {
      "1500000", "3", "12.5", "Аннуитетный", "год(а)", "14.01.2024"};
  std::initializer_list<std::string>::iterator iter = val.begin();
  calc::CreditSettings set;
  set.amount_ = *iter;
  set.term_ = *++iter;
  set.rate_ = *++iter;
  set.type_ = *++iter;
  set.month_or_year_ = *++iter;
  set.date_ = *++iter;
  calc::Credit credit;
  credit.SetValForCredit(set);
  double overpay = 0;
  double total_pay = 0;
  std::vector<calc::CreditResult> res;
  credit.CalcCredit(overpay, total_pay, res);
  EXPECT_FLOAT_EQ(round(overpay * 100) / 100, 306495.84);
  EXPECT_FLOAT_EQ(round(total_pay * 100) / 100, 1806495.84);
  EXPECT_FLOAT_EQ(round(res.back().monthly_payment_ * 100) / 100, 50180.44);
}

TEST(Credit, Dif_1) {
  std::initializer_list<std::string> val = {
      "165000", "6", "16.5", "Дифференцированный", "мес.", "14.01.2024"};
  std::initializer_list<std::string>::iterator iter = val.begin();
  calc::CreditSettings set;
  set.amount_ = *iter;
  set.term_ = *++iter;
  set.rate_ = *++iter;
  set.type_ = *++iter;
  set.month_or_year_ = *++iter;
  set.date_ = *++iter;
  calc::Credit credit;
  credit.SetValForCredit(set);
  double overpay = 0;
  double total_pay = 0;
  std::vector<calc::CreditResult> res;
  credit.CalcCredit(overpay, total_pay, res);
  EXPECT_FLOAT_EQ(round(overpay * 10) / 10, 7940.60);
  EXPECT_FLOAT_EQ(round(total_pay * 10) / 10, 172940.62);
  EXPECT_FLOAT_EQ(round(res.front().monthly_payment_ * 100) / 100, 29768.75);
  EXPECT_FLOAT_EQ(round(res.back().monthly_payment_ * 100) / 100, 27878.13);
}

TEST(Credit, Dif_2) {
  std::initializer_list<std::string> val = {
      "120000", "13", "8.5", "Дифференцированный", "мес.", "14.01.2024"};
  std::initializer_list<std::string>::iterator iter = val.begin();
  calc::CreditSettings set;
  set.amount_ = *iter;
  set.term_ = *++iter;
  set.rate_ = *++iter;
  set.type_ = *++iter;
  set.month_or_year_ = *++iter;
  set.date_ = *++iter;
  calc::Credit credit;
  credit.SetValForCredit(set);
  double overpay = 0;
  double total_pay = 0;
  std::vector<calc::CreditResult> res;
  credit.CalcCredit(overpay, total_pay, res);
  EXPECT_FLOAT_EQ(round(overpay * 100) / 100, 5950.00);
  EXPECT_FLOAT_EQ(round(total_pay * 100) / 100, 125950.00);
  EXPECT_FLOAT_EQ(round(res.front().monthly_payment_ * 100) / 100, 10080.77);
  EXPECT_FLOAT_EQ(round(res.back().monthly_payment_ * 100) / 100, 9296.15);
}

TEST(Credit, Dif_3) {
  std::initializer_list<std::string> val = {
      "1500000", "3", "12.5", "Дифференцированный", "год(а)", "14.01.2024"};
  std::initializer_list<std::string>::iterator iter = val.begin();
  calc::CreditSettings set;
  set.amount_ = *iter;
  set.term_ = *++iter;
  set.rate_ = *++iter;
  set.type_ = *++iter;
  set.month_or_year_ = *++iter;
  set.date_ = *++iter;
  calc::Credit credit;
  credit.SetValForCredit(set);
  double overpay = 0;
  double total_pay = 0;
  std::vector<calc::CreditResult> res;
  credit.CalcCredit(overpay, total_pay, res);
  EXPECT_FLOAT_EQ(round(overpay * 100) / 100, 289062.50);
  EXPECT_FLOAT_EQ(round(total_pay * 100) / 100, 1789062.50);
  EXPECT_FLOAT_EQ(round(res.front().monthly_payment_ * 100) / 100, 57291.67);
  EXPECT_FLOAT_EQ(round(res.back().monthly_payment_ * 100) / 100, 42100.69);
}
