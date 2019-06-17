#include <iostream>
#include <limits>
#include "route.hpp"

int main(int argc, char * argv[])
{
    Route rt;
    rt.add(Coordinates(40.544279, 22.233486, 0));
    rt.add(Coordinates(40.544280, 22.234237, 0));
    rt.add(Coordinates(40.543330, 22.234235, 0));
    rt.add(Coordinates(40.543331, 22.233481, 0));
    std::cout.precision(std::numeric_limits<double>::max_digits10);
    for (auto cor:rt){
        std::cout << cor.getLon() << ", " << cor.getLat() << std::endl;
    }
    std::cout << "sceleton c++ project" << std::endl;
    return 0;
}