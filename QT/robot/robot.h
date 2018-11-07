#ifndef ROBOT_H
#define ROBOT_H
#include <iostream>

enum Direction{UP, RIGHT, LEFT, DOWN};

class Robot{
protected:
    int coordinate_x;
    int coordinate_y;
    Direction direction;
    static std::string robot_model;
public:
    Robot();
    Robot(int, int, Direction);
    int get_coordinate_x();
    int get_coordinate_y();
    Direction get_direction();
    void left_rotate();
    void right_rotate();
    void do_step();
    void print_robot_status();
    static void print_robot_model();
};

#endif // ROBOT_H
