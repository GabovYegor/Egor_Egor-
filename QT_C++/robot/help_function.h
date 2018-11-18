#ifndef HELP_FUNCTION_H
#define HELP_FUNCTION_H

int reach_x;
int reach_y;

void input_begin_coordinate(){
    std::cout << "input coordinate to reach: " << std::endl;;
    std::cout << "input x: ";
    std::cin >> reach_x;
    std::cout << "input y: " ;
    std::cin >> reach_y;
    std::cout << std::endl;
}

#endif // HELP_FUNCTION_H
