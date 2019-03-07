#include <iostream>
#include "shape.h"

int main(){
    Parallelogram par(Point(3, 7), 11, 13, "qwr", 17);
    par.print();
    par.changeCoordinate(Point(5, 9));
    par.setColor("yellow");
    par.multiplicateCoordinate(3);
    par.rotate(10);
    par.print();
    std::cout << par.calculateArea() << std::endl;
    std::cout << par.calculatePerimeter() << std::endl;
    EllipseSector elS(Point(3, 7), 11, 13, "qwr", 17);
    elS.print();
    std::cout << elS.calculateArea();
    return 0;
}
