// Copyright 2021 NNTU-CS
#include "alg.h"

#include <cctype>
#include <sstream>
#include <string>

#include "tstack.h"

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> st;
  std::string result;
  size_t i = 0;
  int len = inf.length();

  while (i < len) {
    char ch = inf[i];
    if (isdigit(ch)) {
      while (i < len && isdigit(inf[i])) {
        result += inf[i];
        ++i;
      }
      result += ' ';
      continue;
    } else if (ch == '(') {
      st.push(ch);
    } else if (ch == ')') {
      while (!st.isEmpty() && st.get() != '(') {
        result += st.pop();
        result += ' ';
      }
      if (!st.isEmpty() && st.get() == '(') {
        st.pop();
      }
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      while (!st.isEmpty() && st.get() != '(' &&
             priority(st.get()) >= priority(ch)) {
        result += st.pop();
        result += ' ';
      }
      st.push(ch);
    }
    ++i;
  }
  while (!st.isEmpty()) {
    result += st.pop();
    result += ' ';
  }
  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }
  return result;
}

int eval(const std::string& post) {
  TStack<int, 100> st;
  std::istringstream iss(post);
  std::string token;

  while (iss >> token) {
    if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
      st.push(std::stoi(token));
    } else {
      int right = st.pop();
      int left = st.pop();
      int res = 0;
      switch (token[0]) {
        case '+': res = left + right; break;
        case '-': res = left - right; break;
        case '*': res = left * right; break;
        case '/': res = left / right; break;
        default: break;
      }
      st.push(res);
    }
  }
  return st.pop();
}
