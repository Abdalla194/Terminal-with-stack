
#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include <string>

class Employees {
private:
    std::string name;

public:
    void setName(std::string n) {
        name = n;
    }

    std::string getName() const {
        return name;
    }
};

#endif
