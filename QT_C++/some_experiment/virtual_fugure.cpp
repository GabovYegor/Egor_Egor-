#include <iostream>
#include <string>

class figure{
protected:
    std::string color;
public:
    figure(std::string color = "red"){
        this->color = color;
    }
    void virtual print_info() const{
        std::cout << "color is " << color << std::endl;
    }
    double virtual get_square() const  = 0;
};

class circle: public figure{
private:
    int radius;
    const double pi = 3.14159;
public:
    circle(std::string color = "write" , int radius = 7){
        this->color = color;
        this->radius = radius;
    }
    double get_square() const override{
        std::cout << "Square is: " << radius * radius * pi << std::endl;
        return 0;
    }
    void print_info() const override{
        std::cout << "color is: " << color << std::endl;
        std::cout << "radius is: " << radius << std::endl;
    }
};

int main(){
    class circle Circle("blue" , 34);
    class circle* pC = &Circle;
    pC->print_info();
    return 0;
}
