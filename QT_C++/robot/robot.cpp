#include <iostream>
#include "robot.h"

Robot::Robot(){
    coordinate_x = 0;
    coordinate_y = 0;
    direction = UP;
}

Robot::Robot(int x_to_set = 0, int y_to_set = 0, Direction direction_to_set = UP){
    coordinate_x = x_to_set;
    coordinate_y = y_to_set;
    direction = direction_to_set;
}

int Robot::get_coordinate_x(){
    return coordinate_x;
}

int Robot::get_coordinate_y(){
    return coordinate_y;
}

Direction Robot::get_direction(){
    return direction;
}

void Robot::left_rotate(){
    switch (direction) {
    case UP:
        direction = LEFT;
        break;
    case RIGHT:
        direction = UP;
        break;
    case DOWN:
        direction = RIGHT;
        break;
    case LEFT:
        direction = DOWN;
        break;
    default:
        break;
    }
}

void Robot::right_rotate(){
    switch (direction) {
    case UP:
        direction = RIGHT;
        break;
    case RIGHT:
        direction = DOWN;
        break;
    case DOWN:
        direction = LEFT;
        break;
    case LEFT:
        direction = UP;
        break;
    default:
        break;
    }
}

void Robot::do_step(){
    switch(direction){
    case UP:
        coordinate_y++;
        break;
    case DOWN:
        coordinate_y--;
        break;
    case LEFT:
        coordinate_x--;
        break;
    case RIGHT:
        coordinate_x++;
        break;
    default:
        break;
    }
}

void Robot::print_robot_status(){
    switch(direction){
    case UP:
        std::cout << "UP" << std::endl;
        break;
    case LEFT:
        std::cout << "LEFT" << std::endl;
        break;
    case DOWN:
        std::cout << "DOWN" << std::endl;
        break;
    case RIGHT:
        std::cout << "RIGHT" << std::endl;
        break;
    default:
        break;
    }
    std::cout << "coordinate x: " << coordinate_x << std::endl;
    std::cout << "coordinate y: " << coordinate_y << std::endl;
}

void Robot::print_robot_model(){

}






