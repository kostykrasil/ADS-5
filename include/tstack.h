// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int STACK_SIZE>
class TStack {
 private:
  T data[STACK_SIZE];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  void push(T value) {
    if (topIndex < STACK_SIZE - 1) {
      data[++topIndex] = value;
    }
  }

  T pop() {
    if (topIndex >= 0) {
      return data[topIndex--];
    }
    return T();
  }

  T get() const {
    if (topIndex >= 0) {
      return data[topIndex];
    }
    return T();
  }

  bool isEmpty() const {
    return topIndex == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
