
#include "Stack.h"

int Stack::activeStacksCount = 0;

int Stack::getactiveStacksCount() { return activeStacksCount; }

Stack::Stack() {
  activeStacksCount++;

//   LOG("No Parameter Constructor Stack()");

  sizeArray = 10;
  top = -1;
  items = new Employees[sizeArray];
}
Stack::Stack(int sizeArray) {
  activeStacksCount++;

//   LOG("Parameter Constructor Stack()");

  this->sizeArray = sizeArray;
  top = -1;
  items = new Employees[sizeArray];
}

Stack::Stack(const Stack& s) {
  activeStacksCount++;

//   LOG("Copy Constructor ::");

  sizeArray = s.sizeArray;
  top = s.top;

  items = new Employees[sizeArray];

  for (int i = 0; i <= top; i++) {
    items[i] = s.items[i];
  }
}

void Stack::push(Employees data) {
  if (top >= sizeArray - 1) {
    LOG("Stack is FULL");
    return;
  }

  top++;

//   LOG("We Write index: " << top);

  items[top] = data;
}

int Stack::pop(Employees* data) {
  if (top == -1) {
    return 0;
  }

  *data = items[top];

  top--;

  return 1;
}

void Stack::display() {
  for (int i = top; i >= 0; i--) {
    LOG(items[i].getName() << " --->");
  }
}

Stack& Stack::operator=(const Stack& s) {
//   LOG("Assignment Operator ::");

  if (this == &s) {
    return *this;
  }

  delete[] items;

  sizeArray = s.sizeArray;
  top = s.top;

  items = new Employees[sizeArray];

  for (int i = 0; i <= top; i++) {
    items[i] = s.items[i];
  }

  return *this;
}

Stack::~Stack() {
//   LOG("Destructor");

  activeStacksCount--;

  delete[] items;
}
