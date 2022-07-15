#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <list>
#include "Model/Exception.h"

enum class FunctionType {
    //Line Functions
    MIDPOINT, LENGTH, EQUATION,
    //Polygon Functions
    AREA, PERIMETER, BASE, HEIGHT, DIAGONALS, APOTHEM,
    //Triangle only
    BISECTORS, MEDIANS
};

class Function {
public:
    //Returns the string corresponding the given enum Function
    static std::string getFunctionName(const FunctionType &);

    //Returns the FunctionType corresponding the given string
    static FunctionType fromString(const std::string&);

    //Returns the list of functions corresponding the figure, depending on the number of points given
    static std::list<FunctionType> getFunctionList(int);
};


#endif
