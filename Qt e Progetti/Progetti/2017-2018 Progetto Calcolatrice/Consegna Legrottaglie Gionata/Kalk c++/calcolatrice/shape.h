#ifndef SHAPE_H
#define SHAPE_H

#include "vertice.h"
#include<vector>
#include<iostream>
#include<ostream>
#include<QVector>
using std::ostream;
class Shape
{
    friend ostream& operator<< (ostream&,const Shape&);

    protected:
            static void reduce_n_shape();
            int id=0;

    public:
            Shape(const Shape&);
            virtual ~Shape()=default;
            Shape();
            int get_id() const;
            virtual QString toString() const =0;
            virtual QString get_nomeClasse() const=0;
            virtual double get_perimetro()const = 0;
            virtual double get_area()const = 0;
    private:
            static int n_shape;


};

#endif // SHAPE_H
