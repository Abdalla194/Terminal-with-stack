
#include <termios.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>
#include <string>

#include "Employees.h"
#include "Stack.h"
#include "mylib.h"

using namespace std;

// class Employees {
//  private:
//   string name;

//  public:
//   void setName(string n) { name = n; }

//   string getName() { return name; }
// };

char getch_linux() {
  char buf = 0;
  struct termios old = {0};

  tcgetattr(0, &old);

  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;

  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;

  tcsetattr(0, TCSANOW, &old);

  read(0, &buf, 1);

  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;

  tcsetattr(0, TCSADRAIN, &old);

  return buf;
}

void enterEmployees(Stack& emp) {
  Employees discarded;

  while (emp.pop(&discarded)) {
  }

  cout << "\033[2J\033[H";
  setColor("yellow");
  display(5, 3, "Enter Employee Names:");
  display(5, 4, "Press ESC Twice to return to menu");
  setColor("white");
  for (int i = 0; i < 20; i++) {
    string n;
    char key;
    int spaceflag = 0;
    cout << "\n    Enter employee " << i + 1 << ": " << flush;

    while (true) {
      key = getch_linux();

      if (key == '\033') {
        char next = getch_linux();

        if (next == '[' || next == 'O') {
          getch_linux();
          continue;
        }

        return;
      }

      if (key == '\n' || key == '\r') {
        cout << endl;
        break;
      }

      if (key == 127) {
        if (!n.empty()) {
          n.pop_back();

          if (n.empty()) {
            spaceflag = 0;
          }

          cout << "\033[1D \033[1D" << flush;
        }
        continue;
      }

      if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) {
        n += key;
        cout << key << flush;
        spaceflag = 1;

      } else if (key == ' ' && spaceflag) {
        n += key;
        cout << key << flush;
      }
    }

    if (!n.empty()) {
      Employees e;
      e.setName(n);
      emp.push(e);
    }
  }
}

void showEmployees(const Stack& emp) {
  Stack temp(emp);

  cout << "\033[2J\033[H";
  setColor("yellow");
  display(5, 3, "Employee Names:");
  setColor("white");
  if (temp.empty()) {
    cout << "\n    No employees entered yet.";
  }

  Employees e;
  int i = 1;

  while (temp.pop(&e)) {
    cout << "\n    " << i << ": " << e.getName();
    i++;
  }
}
// void popEmployees(Stack& emp) {
//   cout << "\033[2J\033[H";
//   setColor("yellow");
//   display(5, 3, "Pop Employees");
//   display(5, 5, "Press ENTER to pop an employee");
//   display(5, 6, "Press ESC Twice to return to menu");
//   setColor("white");
//   Employees e;

//   while (true) {
//     char key = getch_linux();
//     if (key == '\033') {
//       char next = getch_linux();

//       if (next == '[' || next == 'O') {
//         getch_linux();
//         continue;
//       }

//       return;
//     } else if (key == '\n' || key == '\r') {
//       cout << "\033[2J\033[H";

//       display(5, 3, "Pop Employees");

//       if (emp.pop(&e)) {
//         cout << "\n\n    Employee Popped: " << e.getName();

//         cout << "\n\n    Remaining Employees: " << emp.size();

//       } else {
//         cout << "\n\n    No employees left!";
//       }
//       setColor("yellow");
//       display(5, 22, "ENTER: Next Employee | ESC: Menu");
//       setColor("white");
//     }
//   }
// }
void popEmployees(Stack& emp) {
  cout << "\033[2J\033[H";

  setColor("yellow");
  display(5, 3, "Pop Employees");
  display(5, 5, "Press ENTER to pop an employee");
  display(5, 6, "Press ESC Twice to return to menu");
  setColor("white");

  Employees e;
  int row = 9;

  while (true) {
    char key = getch_linux();

    if (key == '\033') {
      char next = getch_linux();

      if (next == '[' || next == 'O') {
        getch_linux();
        continue;
      }

      return;
    } else if (key == '\n' || key == '\r') {
      if (emp.pop(&e)) {
        display(5, row, "Employee Popped: " + e.getName());
      } else {
        display(5, row, "No employees left!");
      }

      row++;
    }
  }
}
void showMenu() {
  cout << "\033[2J\033[H";

  setColor("red");

  display(5, 3, "JERRY'S MENU");

  setColor("white");
  display(5, 5, "Screen 1");
  display(5, 6, "Screen 2");
  display(5, 7, "Exit");
  setColor("yellow");
  display(3, 4, "->");

  display(5, 4, "Employees");
}

int main() {
  Stack emp(20);

  int count1 = 1;

  showMenu();

  while (true) {
    char key = getch_linux();

    if (key == '\033') {
      char bracket = getch_linux();
      char arrow = getch_linux();

      if (bracket == '[') {
        // DOWN ARROW
        if (arrow == 'B') {
          if (count1 == 1) {
            setColor("white");
            display(3, 4, "  Employees");

            setColor("yellow");
            display(3, 5, "->Screen 1");

            count1 = 2;

          } else if (count1 == 2) {
            setColor("white");
            display(3, 5, "  Screen 1");

            setColor("yellow");
            display(3, 6, "->Screen 2");

            count1 = 3;

          } else if (count1 == 3) {
            setColor("white");
            display(3, 6, "  Screen 2");

            setColor("yellow");
            display(3, 7, "->Exit");

            count1 = 4;

          } else if (count1 == 4) {
            setColor("white");
            display(3, 7, "  Exit");

            setColor("yellow");
            display(3, 4, "->Employees");

            count1 = 1;
          }
        }

        // UP ARROW
        else if (arrow == 'A') {
          if (count1 == 4) {
            setColor("white");
            display(3, 7, "  Exit");

            setColor("yellow");
            display(3, 6, "->Screen 2");

            count1 = 3;

          } else if (count1 == 3) {
            setColor("white");
            display(3, 6, "  Screen 2");

            setColor("yellow");
            display(3, 5, "->Screen 1");

            count1 = 2;

          } else if (count1 == 2) {
            setColor("white");
            display(3, 5, "  Screen 1");

            setColor("yellow");
            display(3, 4, "->Employees");

            count1 = 1;

          } else if (count1 == 1) {
            setColor("white");
            display(3, 4, "  Employees");

            setColor("yellow");
            display(3, 7, "->Exit");

            count1 = 4;
          }
        }

        // HOME KEY
        else if (arrow == 'H') {
          setColor("white");
          display(3, 5, "  Screen 1");
          display(3, 6, "  Screen 2");
          display(3, 7, "  Exit");

          setColor("yellow");
          display(3, 4, "->Employees");

          count1 = 1;
        }

        // END KEY
        else if (arrow == 'F') {
          setColor("white");
          display(3, 4, "  Employees");
          display(3, 5, "  Screen 1");
          display(3, 6, "  Screen 2");

          setColor("yellow");
          display(3, 7, "->Exit");

          count1 = 4;
        }
      }

    } else if (key == '\n' || key == '\r') {
      setColor("white");
      // EMPLOYEES
      if (count1 == 1) {
        enterEmployees(emp);

        showMenu();
        count1 = 1;

      }
      // SCREEN 1
      else if (count1 == 2) {
        showEmployees(emp);

        display(5, 22, "Press ESC to return to menu...");

        while (true) {
          char key = getch_linux();

          if (key == '\033') {
            break;
          }
        }

        showMenu();
        count1 = 1;
      }
      // SCREEN 2
      else if (count1 == 3) {
        popEmployees(emp);

        showMenu();
        count1 = 1;
      }
      // EXIT
      else if (count1 == 4) {
        cout << "\033[2J\033[H" << flush;
        return 0;
      }
    }
  }

  return 0;
}
