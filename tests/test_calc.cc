#include <gtest/gtest.h>

#include <list>
#include <string>

#include "../src/model/calculation.h"
#include "../src/model/token.h"

class Calc : public testing::TestWithParam<std::pair<std::string, double>> {};

INSTANTIATE_TEST_SUITE_P(
    InputStr, Calc,
    testing::Values(
        std::pair<std::string, double>{"3.6.5 + (( 4-6 ))", -0.2},
        std::pair<std::string, double>{"-2(-1 + 6)", -10},
        std::pair<std::string, double>{" 5 - 10 ", -5},
        std::pair<std::string, double>{"3.5*19", 66.5},
        std::pair<std::string, double>{"4+5-6", 3},
        std::pair<std::string, double>{"4+5-6/3-2", 5},
        std::pair<std::string, double>{"4+5-6/cos(5)-2", -14.1519205149},
        std::pair<std::string, double>{"5+(6-3/2)", 9.5},
        std::pair<std::string, double>{"3*2+5", 11},
        std::pair<std::string, double>{"(12-3)/3", 3},
        std::pair<std::string, double>{"6-3^2-11", -14},
        std::pair<std::string, double>{"5^3^2", 1953125},
        std::pair<std::string, double>{"162/(2+1)^4", 2},
        std::pair<std::string, double>{"2(3 + 4(5-6))", -2},
        std::pair<std::string, double>{"sqrt(2 * 4)", 2.828427125},
        std::pair<std::string, double>{"sqrt(2)4", 5.656854249},
        std::pair<std::string, double>{"2*(3+(5-4))", 8},
        std::pair<std::string, double>{"-(-1(-1(-1(-1(-1)))))", 1},
        std::pair<std::string, double>{"(5+6)-(9(6-3))3", -70},
        std::pair<std::string, double>{"4sqrt9", 12},
        std::pair<std::string, double>{"(3)(3)", 9},
        std::pair<std::string, double>{"sqrt(9)cos(0)", 3},
        std::pair<std::string, double>{"2-(+3)", -1},
        std::pair<std::string, double>{"sin2", 0.90929742682},
        std::pair<std::string, double>{"sin2+5", 5.90929742683},
        std::pair<std::string, double>{"x+5-4", 4},
        std::pair<std::string, double>{
            "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3", 9.927835}));

TEST_P(Calc, CalcExpr) {
  std::pair<std::string, double> a = GetParam();
  std::string expr = a.first;
  double true_res = a.second;
  calc::Calculation calc;
  std::string x = "3";
  int err = calc.SetX(x);
  EXPECT_EQ(err, 0);
  calc.CheckAndConvertStr(expr);
  double res;
  calc.CalcResult(res);
  EXPECT_FLOAT_EQ(res, true_res);
}

TEST(Calc, Error_expr) {
  std::string expr = "2..2";
  calc::Calculation calc;
  int8_t err = calc.CheckAndConvertStr(expr);
  std::string name = calc.GetErrorName(err);
  EXPECT_EQ(err, 1);
  EXPECT_EQ(name, "Many points");
}

TEST(Calc, Error_x) {
  std::string expr = "2x";
  calc::Calculation calc;
  std::string x = "a";
  int8_t err = calc.SetX(x);

  EXPECT_EQ(err, 3);
}
