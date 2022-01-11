#include "telefonata.h"
#include "orario.h"

int main()
{
    orario o1(1,2,3);
    orario o2(4,5,6);

    telefonata t1(o1,o2,123);
    telefonata t2(o1,o1,123);
}