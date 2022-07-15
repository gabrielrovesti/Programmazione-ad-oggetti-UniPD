#include "Exception.h"

Exception::Exception(const string &reason) : reason(reason) {}

string Exception::getReason() const {
    return reason;
}
