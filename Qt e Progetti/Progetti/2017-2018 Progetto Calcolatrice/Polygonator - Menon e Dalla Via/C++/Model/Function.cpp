#include "Function.h"

std::string Function::getFunctionName(const FunctionType &function) {
    switch (function) {
        case FunctionType::MIDPOINT : return "Middle Point";
        case FunctionType::LENGTH : return "Length";
        case FunctionType::EQUATION : return "Equation";
        case FunctionType::AREA : return "Area";
        case FunctionType::PERIMETER : return "Perimeter";
        case FunctionType::BASE : return "Base";
        case FunctionType::HEIGHT : return "Height";
        case FunctionType::DIAGONALS : return "Diagonals";
        case FunctionType::BISECTORS : return "Bisectors";
        case FunctionType::MEDIANS : return "Medians";
        case FunctionType::APOTHEM: return "Apothem";
    }
    throw Exception("No function matching");
}

FunctionType Function::fromString(const std::string &function) {
    if(function=="Middle Point") return FunctionType::MIDPOINT;
    if(function=="Length") return FunctionType::LENGTH;
    if(function=="Equation") return FunctionType::EQUATION;
    if(function=="Area") return FunctionType::AREA;
    if(function=="Perimeter") return FunctionType::PERIMETER;
    if(function=="Base") return FunctionType::BASE;
    if(function=="Height") return FunctionType::HEIGHT;
    if(function=="Diagonals") return FunctionType::DIAGONALS;
    if(function=="Bisectors") return FunctionType::BISECTORS;
    if(function=="Medians") return FunctionType::MEDIANS;
    if(function=="Apothem") return FunctionType::APOTHEM;
    throw Exception("No function matching");
}

std::list<FunctionType> Function::getFunctionList(int pointsNumber) {
   switch (pointsNumber) {
       case 1:
           return {FunctionType::EQUATION};
       case 2:
           return {FunctionType::EQUATION, FunctionType::LENGTH, FunctionType::MIDPOINT};
       case 3:
           return {FunctionType::APOTHEM, FunctionType::AREA, FunctionType::BASE, FunctionType::BISECTORS, FunctionType::HEIGHT, FunctionType::MEDIANS, FunctionType::PERIMETER};
       default:
           return {FunctionType::APOTHEM, FunctionType::AREA, FunctionType::BASE, FunctionType::DIAGONALS, FunctionType::HEIGHT, FunctionType::PERIMETER};
   }
}
