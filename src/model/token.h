#ifndef SMART_CALC_SRC_MODEL_TOKEN
#define SMART_CALC_SRC_MODEL_TOKEN

#include <list>
#include <stack>
#include <string>

namespace calc {

struct Token {
  int16_t key_;
  std::string value_;
};

enum TokenKey : int8_t {
  kItsNum = 0,
  kItsOperatorSumSub,  // + -
  kItsOperatorMulDiv,  // * /
  kItsOperatorPow,     // ^
  kItsOpenBracket,
  kItsCloseBracket,
  kItsFunc,
};

enum ErrorCode : int8_t {
  kOK = 0,
  kManyPoints,
  kUndefinedFunc,
  kUndefinedToken,
  kExtraBracket,
  kEmptyBetweenBrackets,
  kOperatorBeforeOperator,
  kMissNum,
  kIncorrectExpr,
};

class PolishNotation {
 public:
  PolishNotation() {}
  ~PolishNotation() {}

  /// @brief Converts an expression in infix notation to a list of tokens
  /// @param input_str Input expression
  /// @return Returns an error code if the expression is invalid
  int8_t FromStrToToken(std::string& input_str);

  /// @brief Converts a token sheet to reverse Polish notation
  /// @return Returns an error code if the token list is incorrect
  int8_t ConvertToPolishNotation();

  /// @brief Writes an expression in reverse Polish notation
  /// @param out_str The list of tokens in which the expression is written
  void GetOutStr(std::list<Token>& out_str);

  std::string GetErrorName(int8_t err);
  std::string FromTokenToStr();  // for tests

 private:
  bool IsNum(char s) const;
  bool IsOperator(char s) const;
  bool IsOpenBracket(char s) const;
  bool IsCloseBracket(char s) const;
  bool IsChar(char s) const;
  bool IsDot(char s) const;
  bool IsFunc(std::string value) const;
  bool IsUnSub(const std::string& input_str) const;
  bool IsUnAdd(const std::string& input_str) const;

  int8_t PushNumToListToken(const std::string& input_str);
  void PushXToListToken(const std::string& input_str);
  int8_t PushOperatorToListToken(const std::string& input_str);
  void PushOpenBracketToListToken(const std::string& input_str);
  void PushCloseBracketToListToken(const std::string& input_str);
  int8_t PushFuncToListToken(const std::string& input_str);

  void PushToken(int key);

  int8_t PushToOutStrAfterCloseBracket(std::list<Token>::iterator& iter,
                                       std::stack<Token>& stack);
  void PushOperatorsToOutStr(std::list<Token>::iterator& iter,
                             std::stack<Token>& stack);
  int8_t PushRemainingToOutStr(std::stack<Token>& stack);

  Token token_;
  std::list<Token> list_token_;
  std::list<Token> out_str_;
  const std::list<std::string> pref_func_ = {"sin",  "cos",  "tan",  "acos",
                                             "asin", "atan", "sqrt", "ln",
                                             "log",  "mod",  "exp"};
  std::string value_;
  int pos_;
  int len_inp_str_;
};

}  // namespace calc

#endif  // SMART_CALC_SRC_MODEL_TOKEN
