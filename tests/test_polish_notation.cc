#include <gtest/gtest.h>

#include <iostream>
#include <list>
#include <string>

#include "../src/model/token.h"

class PolishNotation
    : public testing::TestWithParam<std::pair<std::string, std::string>> {};

INSTANTIATE_TEST_SUITE_P(
    InputStr, PolishNotation,
    testing::Values(
        std::pair<std::string, std::string>{"3.6.5 + (( 4-6 ))",
                                            "3.6 .5 * 4 6 - +"},
        std::pair<std::string, std::string>{"-2(-1 + 6)", "2 1 ~ 6 + * ~"},
        std::pair<std::string, std::string>{" 5 - 10 ", "5 10 -"},
        std::pair<std::string, std::string>{"3.5*19", "3.5 19 *"},
        std::pair<std::string, std::string>{"4+5-6", "4 5 + 6 -"},
        std::pair<std::string, std::string>{"4+5-6/3-2", "4 5 + 6 3 / - 2 -"},
        std::pair<std::string, std::string>{" 4 + 5 - 6 / cos(5) - 2 ",
                                            "4 5 + 6 5 cos / - 2 -"},
        std::pair<std::string, std::string>{"5+(6-3/2)", "5 6 3 2 / - +"},
        std::pair<std::string, std::string>{"3*2+5", "3 2 * 5 +"},
        std::pair<std::string, std::string>{"(12-3)/3", "12 3 - 3 /"},
        std::pair<std::string, std::string>{"6-3^2-11", "6 3 2 ^ - 11 -"},
        std::pair<std::string, std::string>{"5^3^2", "5 3 2 ^ ^"},
        std::pair<std::string, std::string>{"162/(2+1)^4", "162 2 1 + 4 ^ /"},
        std::pair<std::string, std::string>{"2x", "2 x *"},
        std::pair<std::string, std::string>{"2(3 + 4(5-6))",
                                            "2 3 4 5 6 - * + *"},
        std::pair<std::string, std::string>{"sqrtx4", "x sqrt 4 *"},
        std::pair<std::string, std::string>{"sqrt4x", "4 sqrt x *"},
        std::pair<std::string, std::string>{"sqrt(x)4", "x sqrt 4 *"},
        std::pair<std::string, std::string>{"sqrt(x4)", "x 4 * sqrt"},
        std::pair<std::string, std::string>{"2*(3+(5-4))", "2 3 5 4 - + *"},
        std::pair<std::string, std::string>{"-(-1(-1(-1(-1(-1)))))",
                                            "1 1 1 1 1 ~ * ~ * ~ * ~ * ~ ~"},
        std::pair<std::string, std::string>{"(5+6)-(9(6-3))3",
                                            "5 6 + 9 6 3 - * 3 * -"},
        std::pair<std::string, std::string>{"4sqrt9", "4 9 sqrt *"},
        std::pair<std::string, std::string>{"(3)(3)", "3 3 *"},
        std::pair<std::string, std::string>{"sqrt(9)cos(0)", "9 sqrt 0 cos *"},
        std::pair<std::string, std::string>{"2-(+3)", "2 3 -"},
        std::pair<std::string, std::string>{"mod3", "3 %"},
        std::pair<std::string, std::string>{"sinx", "x sin"},
        std::pair<std::string, std::string>{"sinx+5", "x sin 5 +"},
        std::pair<std::string, std::string>{"4mod2sqrt4", "4 2 % 4 sqrt *"},
        std::pair<std::string, std::string>{"4mod2", "4 2 %"},
        std::pair<std::string, std::string>{"2e2", "2e2"},
        std::pair<std::string, std::string>{"2e-2", "2e-2"},
        std::pair<std::string, std::string>{"2.3.4.2", "2.3 .4 * .2 *"},
        std::pair<std::string, std::string>{
            "15 / 5 * 3 - 4 * 15 / (-194) * 3",
            "15 5 / 3 * 4 15 * 194 ~ / 3 * -"}));

TEST_P(PolishNotation, ConvertToPN) {
  std::pair<std::string, std::string> a = GetParam();
  calc::PolishNotation model;
  std::string before = a.first;
  std::string after = a.second;
  model.FromStrToToken(before);
  model.ConvertToPolishNotation();
  before = model.FromTokenToStr();
  EXPECT_EQ(before, after);
}
