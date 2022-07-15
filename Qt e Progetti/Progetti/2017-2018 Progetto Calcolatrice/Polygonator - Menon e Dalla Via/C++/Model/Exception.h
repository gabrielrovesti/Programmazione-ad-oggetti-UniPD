#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

using std::string;

class Exception {
private:
    string reason;

public:
    explicit Exception(const string & = "Generic Error");

    string getReason() const;
};


#endif
