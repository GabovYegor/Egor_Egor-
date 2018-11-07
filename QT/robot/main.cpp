#include <iostream>
#include "robot.h"
#include "help_function.h"
#include "super_robot.h"

/**
 * @brief main
 * не получаются static методы
 * @return
 */

int main(){
    class Super_Robot super_robot(1, 5, RIGHT);
    super_robot.print_robot_status();
    return 0;
}
