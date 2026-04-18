// Copyright 2025 NNTU-CS
#include "alg.h"
#include "tstack.h"
#include <cctype>
#include <sstream>
#include <string>

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
            st.Push(ch);
        } else if (ch == ')') {
            while (!st.IsEmpty() && st.Top() != '(') {
                result += st.Pop();
                result += ' ';
            }
            if (!st.IsEmpty() && st.Top() == '(') {
                st.Pop();
            }
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!st.IsEmpty() && st.Top() != '(' &&
                   priority(st.Top()) >= priority(ch)) {
                result += st.Pop();
                result += ' ';
            }
            st.Push(ch);
        }
        ++i;
    }

    while (!st.IsEmpty()) {
        result += st.Pop();
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
            st.Push(std::stoi(token));
        } else {
            int right = st.Pop();
            int left = st.Pop();
            int res = 0;
            switch (token[0]) {
                case '+': res = left + right; break;
                case '-': res = left - right; break;
                case '*': res = left * right; break;
                case '/': res = left / right; break;
                default: break;
            }
            st.Push(res);
        }
    }
    return st.Pop();
}
