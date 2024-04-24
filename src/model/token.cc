#include "token.h"

#include <algorithm>
#include <stack>
#include <string>
#include <vector>

namespace calc {

int8_t PolishNotation::FromStrToToken(std::string& input_str) {
  std::transform(input_str.begin(), input_str.end(), input_str.begin(),
                 tolower);
  input_str.erase(remove(input_str.begin(), input_str.end(), ' '),
                  input_str.end());
  int8_t err;

  list_token_.clear();
  len_inp_str_ = input_str.length();

  for (pos_ = 0; pos_ < len_inp_str_; ++pos_) {
    if (IsNum(input_str[pos_]) || IsDot(input_str[pos_])) {
      err = PushNumToListToken(input_str);
      if (err != ErrorCode::kOK) return err;
    } else if (input_str[pos_] == 'x') {
      PushXToListToken(input_str);
    } else if (IsOperator(input_str[pos_])) {
      err = PushOperatorToListToken(input_str);
      if (err != ErrorCode::kOK) return err;
    } else if (IsOpenBracket(input_str[pos_])) {
      PushOpenBracketToListToken(input_str);
    } else if (IsCloseBracket(input_str[pos_])) {
      PushCloseBracketToListToken(input_str);
    } else if (IsChar(input_str[pos_])) {
      err = PushFuncToListToken(input_str);
      if (err != ErrorCode::kOK) return err;
    } else {
      return ErrorCode::kUndefinedToken;
    }
  }

  return ErrorCode::kOK;
}

void PolishNotation::PushToken(int key) {
  token_.value_ = value_;
  token_.key_ = key;
  list_token_.push_back(token_);
}

bool PolishNotation::IsNum(char s) const { return s >= '0' && s <= '9'; }

bool PolishNotation::IsOperator(char s) const {
  return s == '+' || s == '-' || s == '*' || s == '/' || s == '^';
}

bool PolishNotation::IsOpenBracket(char s) const { return s == '('; }

bool PolishNotation::IsCloseBracket(char s) const { return s == ')'; }

bool PolishNotation::IsChar(char s) const { return s >= 'a' && s <= 'z'; }

bool PolishNotation::IsDot(char s) const { return s == '.'; }

bool PolishNotation::IsFunc(std::string value) const {
  std::list<std::string>::const_iterator iter = pref_func_.begin();
  for (; iter != pref_func_.end(); ++iter) {
    if (*iter == value) return true;
  }
  return false;
}

bool PolishNotation::IsUnSub(const std::string& input_str) const {
  return input_str[pos_] == '-' &&
         (pos_ == 0 || (pos_ > 0 && (input_str[pos_ - 1] == '(' ||
                                     input_str[pos_ - 1] == '^')));
}

bool PolishNotation::IsUnAdd(const std::string& input_str) const {
  return input_str[pos_] == '+' &&
         (pos_ == 0 || (pos_ > 0 && (input_str[pos_ - 1] == '(' ||
                                     input_str[pos_ - 1] == '^')));
}

int8_t PolishNotation::PushNumToListToken(const std::string& input_str) {
  value_ = "";

  if (pos_ > 0 && IsDot(input_str[pos_]) && IsDot(input_str[pos_ - 1]))
    return ErrorCode::kManyPoints;

  bool dot_was_here = false;
  bool e_was_here = false;

  while ((IsNum(input_str[pos_]) || IsDot(input_str[pos_])) &&
         pos_ < len_inp_str_) {
    if (IsDot(input_str[pos_]) && dot_was_here == false)
      dot_was_here = 1;
    else if (IsDot(input_str[pos_]) && dot_was_here == true) {
      PushToken(TokenKey::kItsNum);
      value_ = "*";
      PushToken(TokenKey::kItsOperatorMulDiv);
      --pos_;
      return ErrorCode::kOK;
    }
    value_.push_back(input_str[pos_]);
    ++pos_;
    if (pos_ + 1 < len_inp_str_ && input_str[pos_] == 'e' &&
        !IsChar(input_str[pos_ + 1]) && e_was_here == false) {
      value_.push_back(input_str[pos_]);
      ++pos_;
      if (pos_ < len_inp_str_ &&
          (input_str[pos_] == '-' || input_str[pos_] == '+')) {
        value_.push_back(input_str[pos_]);
        ++pos_;
      }
      e_was_here = true;
    }
  }
  --pos_;
  PushToken(TokenKey::kItsNum);
  return ErrorCode::kOK;
}

void PolishNotation::PushXToListToken(const std::string& input_str) {
  if (pos_ > 0 && (IsNum(input_str[pos_ - 1]) || input_str[pos_ - 1] == 'x')) {
    value_ = "*";
    PushToken(TokenKey::kItsOperatorMulDiv);
  }
  value_ = {input_str[pos_]};
  PushToken((TokenKey::kItsNum));
  if (pos_ + 1 < len_inp_str_ && IsNum(input_str[pos_ + 1])) {
    value_ = "*";
    PushToken(TokenKey::kItsOperatorMulDiv);
  }
}

int8_t PolishNotation::PushOperatorToListToken(const std::string& input_str) {
  if (pos_ > 0 && IsOperator(input_str[pos_ - 1]))
    return ErrorCode::kOperatorBeforeOperator;
  value_ = {input_str[pos_]};
  if (input_str[pos_] == '+' || input_str[pos_] == '-') {
    if (IsUnAdd(input_str)) return ErrorCode::kOK;
    token_.key_ = TokenKey::kItsOperatorSumSub;
    token_.value_ = value_;
    if (IsUnSub(input_str)) token_.value_ = "~";
  } else if (input_str[pos_] == '*' || input_str[pos_] == '/') {
    token_.key_ = TokenKey::kItsOperatorMulDiv;
    token_.value_ = value_;
  } else {
    token_.key_ = TokenKey::kItsOperatorPow;
    token_.value_ = value_;
  }

  list_token_.push_back(token_);

  return ErrorCode::kOK;
}

void PolishNotation::PushOpenBracketToListToken(const std::string& input_str) {
  if (pos_ > 0 &&
      (IsNum(input_str[pos_ - 1]) || IsCloseBracket(input_str[pos_ - 1]))) {
    value_ = "*";
    PushToken(TokenKey::kItsOperatorMulDiv);
  }
  value_ = {input_str[pos_]};
  PushToken(TokenKey::kItsOpenBracket);
}

void PolishNotation::PushCloseBracketToListToken(const std::string& input_str) {
  value_ = {input_str[pos_]};
  PushToken(TokenKey::kItsCloseBracket);
  if (pos_ + 1 < len_inp_str_ &&
      (IsNum(input_str[pos_ + 1]) || IsChar(input_str[pos_ + 1]))) {
    value_ = "*";
    PushToken(TokenKey::kItsOperatorMulDiv);
  }
}

int8_t PolishNotation::PushFuncToListToken(const std::string& input_str) {
  value_ = "";

  while (IsChar(input_str[pos_])) {
    value_.push_back(input_str[pos_]);
    ++pos_;
    if (IsFunc(value_)) break;
  }

  --pos_;

  if (list_token_.size() > 0) {
    if ((list_token_.back().key_ == TokenKey::kItsNum ||
         list_token_.back().key_ == TokenKey::kItsCloseBracket) &&
        value_ != "mod") {
      std::string tmp = value_;
      value_ = "*";
      PushToken(TokenKey::kItsOperatorMulDiv);
      value_ = tmp;
    }
  }

  if (IsFunc(value_)) {
    if (value_ == "mod") {
      value_ = "%";
      PushToken(TokenKey::kItsOperatorMulDiv);
    } else
      PushToken(TokenKey::kItsFunc);
  } else {
    return ErrorCode::kUndefinedFunc;
  }

  return ErrorCode::kOK;
}

int8_t PolishNotation::ConvertToPolishNotation() {
  out_str_.clear();
  std::stack<Token> stack;
  for (auto iter = list_token_.begin(); iter != list_token_.end(); ++iter) {
    if (iter->key_ == TokenKey::kItsNum) {
      token_.key_ = iter->key_;
      token_.value_ = iter->value_;
      out_str_.push_back(token_);
    } else if (iter->key_ == TokenKey::kItsFunc ||
               iter->key_ == TokenKey::kItsOpenBracket) {
      token_.key_ = iter->key_;
      token_.value_ = iter->value_;
      stack.push(token_);
    } else if (iter->key_ == TokenKey::kItsCloseBracket) {
      int8_t err = PushToOutStrAfterCloseBracket(iter, stack);
      if (err != ErrorCode::kOK) return err;
    } else {
      PushOperatorsToOutStr(iter, stack);
    }
  }
  int8_t err = PushRemainingToOutStr(stack);
  if (err != ErrorCode::kOK) return err;
  return ErrorCode::kOK;
}

int8_t PolishNotation::PushToOutStrAfterCloseBracket(
    std::list<Token>::iterator& iter, std::stack<Token>& stack) {
  if (iter != list_token_.begin() &&
      (*--iter).key_ == TokenKey::kItsOpenBracket) {
    ++iter;
    return ErrorCode::kEmptyBetweenBrackets;
  }
  ++iter;
  bool there_is_open_bracket = false;
  size_t size = stack.size();
  for (size_t i = 0; i < size; ++i) {
    if (stack.top().key_ == TokenKey::kItsOpenBracket) {
      stack.pop();
      there_is_open_bracket = true;
      break;
    }
    token_.key_ = stack.top().key_;
    token_.value_ = stack.top().value_;
    out_str_.push_back(token_);
    stack.pop();
  }
  if (there_is_open_bracket == false) {
    return ErrorCode::kExtraBracket;
  }
  return ErrorCode::kOK;
}

void PolishNotation::PushOperatorsToOutStr(std::list<Token>::iterator& iter,
                                           std::stack<Token>& stack) {
  if (stack.size() == 0) {
    token_.key_ = iter->key_;
    token_.value_ = iter->value_;
    stack.push(token_);
  } else {
    if (stack.top().key_ >= iter->key_) {
      if (stack.top().key_ != TokenKey::kItsOpenBracket &&
          !(iter->key_ == TokenKey::kItsOperatorPow &&
            stack.top().key_ == TokenKey::kItsOperatorPow)) {
        while (stack.size() > 0 && stack.top().key_ >= iter->key_) {
          if (stack.top().key_ == 4) break;
          token_.key_ = stack.top().key_;
          token_.value_ = stack.top().value_;
          out_str_.push_back(token_);
          stack.pop();
        }
      }
    }
    token_.key_ = iter->key_;
    token_.value_ = iter->value_;
    stack.push(token_);
  }
}

int8_t PolishNotation::PushRemainingToOutStr(std::stack<Token>& stack) {
  size_t size = stack.size();
  for (size_t i = 0; i < size; ++i) {
    if (stack.top().key_ == 4 || stack.top().key_ == 5) {
      return ErrorCode::kExtraBracket;
    }
    token_.key_ = stack.top().key_;
    token_.value_ = stack.top().value_;
    out_str_.push_back(token_);
    stack.pop();
  }
  return ErrorCode::kOK;
}

void PolishNotation::GetOutStr(std::list<Token>& out_str) {
  out_str = out_str_;
}

std::string PolishNotation::GetErrorName(int8_t err) {
  switch (err) {
    case ErrorCode::kManyPoints:
      return "Many points";
    case ErrorCode::kUndefinedToken:
      return "Underhined token";
    case ErrorCode::kExtraBracket:
      return "Extra bracket";
    case ErrorCode::kEmptyBetweenBrackets:
      return "Empty between brackets";
    case ErrorCode::kOperatorBeforeOperator:
      return "Operator before operator";
    case ErrorCode::kIncorrectExpr:
      return "Incorrect expression";
    default:
      return "Unspecified error";
  }
}

std::string PolishNotation::FromTokenToStr() {
  std::string res;
  for (auto iter = out_str_.begin(); iter != out_str_.end(); ++iter) {
    res.insert(res.size(), iter->value_);
    res.push_back(' ');
  }
  res.pop_back();
  return res;
}

}  // namespace calc
