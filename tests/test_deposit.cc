#include <gtest/gtest.h>

#include <cmath>
#include <initializer_list>
#include <string>
#include <vector>

#include "../src/model/deposit.h"

TEST(Deposit, Without_add_sub_1) {
  calc::Deposit d;
  std::initializer_list<std::string> val = {"150000",     "6",  "дней",
                                            "14.01.2024", "11", "Раз в день"};
  std::initializer_list<std::string>::iterator iter = val.begin();
  calc::DepositSettings set;
  set.amount_ = *iter;
  set.term_ = *++iter;
  set.day_month_year_ = *++iter;
  set.date_ = *++iter;
  set.rate_ = *++iter;
  set.is_capital_ = false;
  set.capitalization_ = *++iter;
  d.SetValToDeposit(set);
  double tax = 0;
  double rate_end = 0;
  double amount_end;
  std::vector<calc::DepositResult> res;
  d.CalcDeposit(tax, rate_end, amount_end, res);
  EXPECT_FLOAT_EQ(round(tax * 10) / 10, 0);
  EXPECT_FLOAT_EQ(round(rate_end * 100) / 100, 270.49);
  EXPECT_FLOAT_EQ(round(amount_end * 100) / 100, 150270.48);
}

TEST(Deposit, Without_add_sub_2) {
  calc::Deposit d;
  std::initializer_list<std::string> val = {"1500000",    "6",  "месяцев",
                                            "14.01.2024", "11", "Раз в неделю"};
  std::initializer_list<std::string>::iterator iter = val.begin();
  calc::DepositSettings set;
  set.amount_ = *iter;
  set.term_ = *++iter;
  set.day_month_year_ = *++iter;
  set.date_ = *++iter;
  set.rate_ = *++iter;
  set.is_capital_ = false;
  set.capitalization_ = *++iter;
  d.SetValToDeposit(set);
  double tax = 0;
  double rate_end = 0;
  double amount_end;
  std::vector<calc::DepositResult> res;
  d.CalcDeposit(tax, rate_end, amount_end, res);
  EXPECT_FLOAT_EQ(round(tax * 10) / 10, 0);
  EXPECT_FLOAT_EQ(round(rate_end * 100) / 100, 82049.18);
  EXPECT_FLOAT_EQ(round(amount_end * 100) / 100, 1582049.18);
}

TEST(Deposit, Without_add_sub_3) {
  calc::Deposit d;
  std::initializer_list<std::string> val = {"1500000",    "13", "месяцев",
                                            "14.01.2024", "11", "Раз в месяц"};
  std::initializer_list<std::string>::iterator iter = val.begin();
  calc::DepositSettings set;
  set.amount_ = *iter;
  set.term_ = *++iter;
  set.day_month_year_ = *++iter;
  set.date_ = *++iter;
  set.rate_ = *++iter;
  set.is_capital_ = false;
  set.capitalization_ = *++iter;
  d.SetValToDeposit(set);
  double tax = 0;
  double rate_end = 0;
  double amount_end;
  std::vector<calc::DepositResult> res;
  d.CalcDeposit(tax, rate_end, amount_end, res);
  EXPECT_FLOAT_EQ(round(tax * 10) / 10, 0);
  EXPECT_FLOAT_EQ(round(rate_end * 100) / 100, 179030.99);
  EXPECT_FLOAT_EQ(round(amount_end * 100) / 100, 1679030.99);
}

TEST(Deposit, Without_add_sub_4) {
  calc::Deposit d;
  std::initializer_list<std::string> val = {
      "15000000", "2", "лет", "14.01.2024", "11", "Раз в квартал"};
  std::initializer_list<std::string>::iterator iter = val.begin();
  calc::DepositSettings set;
  set.amount_ = *iter;
  set.term_ = *++iter;
  set.day_month_year_ = *++iter;
  set.date_ = *++iter;
  set.rate_ = *++iter;
  set.is_capital_ = false;
  set.capitalization_ = *++iter;
  d.SetValToDeposit(set);
  double tax = 0;
  double rate_end = 0;
  double amount_end;
  std::vector<calc::DepositResult> res;
  d.CalcDeposit(tax, rate_end, amount_end, res);
  // EXPECT_FLOAT_EQ(round(tax * 10) / 10, 366622.48);
  EXPECT_FLOAT_EQ(round(rate_end * 100) / 100, 3300172.92);
  EXPECT_FLOAT_EQ(round(amount_end * 100) / 100, 18300172.92);
}

TEST(Deposit, Without_add_sub_5) {
  calc::Deposit d;
  std::initializer_list<std::string> val = {"15000000",   "2",  "лет",
                                            "14.01.2024", "11", "Раз в год"};
  std::initializer_list<std::string>::iterator iter = val.begin();
  calc::DepositSettings set;
  set.amount_ = *iter;
  set.term_ = *++iter;
  set.day_month_year_ = *++iter;
  set.date_ = *++iter;
  set.rate_ = *++iter;
  set.is_capital_ = true;
  set.capitalization_ = *++iter;
  d.SetValToDeposit(set);
  double tax = 0;
  double rate_end = 0;
  double amount_end;
  std::vector<calc::DepositResult> res;
  d.CalcDeposit(tax, rate_end, amount_end, res);
  // EXPECT_FLOAT_EQ(round(tax * 10) / 10, 366622.48);
  EXPECT_FLOAT_EQ(round(rate_end * 100) / 100, 3482242.5);
  EXPECT_FLOAT_EQ(round(amount_end * 100) / 100, 18482242);
}

TEST(Deposit, Without_add_sub_6) {
  calc::Deposit d;
  std::initializer_list<std::string> val = {"150000",     "6",  "дней",
                                            "19.01.2024", "11", "Раз в день"};
  std::initializer_list<std::string>::iterator iter = val.begin();
  calc::DepositSettings set;
  set.amount_ = *iter;
  set.term_ = *++iter;
  set.day_month_year_ = *++iter;
  set.date_ = *++iter;
  set.rate_ = *++iter;
  set.is_capital_ = true;
  set.capitalization_ = *++iter;
  d.SetValToDeposit(set);
  double tax = 0;
  double rate_end = 0;
  double amount_end;
  std::vector<calc::DepositResult> res;
  d.CalcDeposit(tax, rate_end, amount_end, res);
  EXPECT_FLOAT_EQ(round(tax * 10) / 10, 0);
  EXPECT_FLOAT_EQ(round(rate_end * 100) / 100, 270.7);
  EXPECT_FLOAT_EQ(round(amount_end * 100) / 100, 150270.7);
}

TEST(Deposit, With_add_sub_1) {
  calc::Deposit d;
  std::initializer_list<std::string> val = {"1500000",    "6",  "месяцев",
                                            "14.01.2024", "11", "Раз в месяц"};
  std::initializer_list<std::string>::iterator iter = val.begin();
  calc::DepositSettings set;
  set.amount_ = *iter;
  set.term_ = *++iter;
  set.day_month_year_ = *++iter;
  set.date_ = *++iter;
  set.rate_ = *++iter;
  set.is_capital_ = true;
  set.capitalization_ = *++iter;
  d.SetValToDeposit(set);

  std::string dt = "16.01.2024";
  std::string a = "5000";
  d.AddInInputList(dt, a);

  dt = "25.04.2024";
  a = "15000";
  d.AddInInputList(dt, a);

  dt = "29.05.2024";
  a = "6000";
  d.AddInOutList(dt, a);

  double tax = 0;
  double rate_end = 0;
  double amount_end;
  std::vector<calc::DepositResult> res;
  d.CalcDeposit(tax, rate_end, amount_end, res);
  EXPECT_FLOAT_EQ(round(tax * 10) / 10, 0);
  EXPECT_FLOAT_EQ(round(rate_end * 100) / 100, 84498.8);
  EXPECT_FLOAT_EQ(round(amount_end * 100) / 100, 1598498.8);
}

TEST(Deposit, With_add_sub_2) {
  calc::Deposit d;
  std::initializer_list<std::string> val = {
      "1500000", "14", "месяцев", "19.01.2024", "8", "Раз в полгода"};
  std::initializer_list<std::string>::iterator iter = val.begin();
  calc::DepositSettings set;
  set.amount_ = *iter;
  set.term_ = *++iter;
  set.day_month_year_ = *++iter;
  set.date_ = *++iter;
  set.rate_ = *++iter;
  set.is_capital_ = true;
  set.capitalization_ = *++iter;
  d.SetValToDeposit(set);

  std::string dt = "20.02.2024";
  std::string a = "5000";
  d.AddInInputList(dt, a);

  dt = "29.05.2024";
  a = "6000";
  d.AddInOutList(dt, a);

  double tax = 0;
  double rate_end = 0;
  double amount_end;
  std::vector<calc::DepositResult> res;
  d.CalcDeposit(tax, rate_end, amount_end, res);
  EXPECT_FLOAT_EQ(round(tax * 10) / 10, 0);
  EXPECT_FLOAT_EQ(round(rate_end * 100) / 100, 143446.56);
  EXPECT_FLOAT_EQ(round(amount_end * 100) / 100, 1642446.56);
}
