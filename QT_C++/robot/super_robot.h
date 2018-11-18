#ifndef SUPER_ROBOT_H
#define SUPER_ROBOT_H
#include "robot.h"

class Super_Robot: public Robot{
public:
    Super_Robot(int, int, Direction);
};

Super_Robot::Super_Robot(int x_to_set = 0, int y_to_set = 0, Direction direction_to_set = UP){
    coordinate_x = x_to_set;
    coordinate_y = y_to_set;
    direction = direction_to_set;
}

#endif // SUPER_ROBOT_H
