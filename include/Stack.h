
#ifndef STACK_H
#define STACK_H

#include <iostream>

#include "Employees.h"

#define LOG(str) std::cout << str << std::endl

class Stack {
 public:
  Stack();
  Stack(int sizeArray);
  ~Stack();

  Stack(const Stack& s);

  void push(Employees data);
  int pop(Employees* data);
  bool empty() const { return top == -1; }

  int size() const { return top + 1; }
  void display(void);

  Stack& operator=(const Stack& s);

  static int getactiveStacksCount();

 private:
  int top;
  int sizeArray;
  Employees* items;

  static int activeStacksCount;
};

#endif
