#pragma once

#include <optional>
#include "robot.hh"

#define MAX_ROBOTS_SIZE 100

class RobotAgency
{
  public:
    //Constructor for RobotAgency
    //Creates a shared_ptr on the Robots array
    RobotAgency(std::shared_ptr<Robot> *robots, size_t robots_size);

    //Returns true if at least one robot is valid (health > 0)
    bool has_valid_robot() const;

    //Returns the robot at the `index` position
    std::optional<std::shared_ptr<Robot>> get_robot(size_t index) const;

    //Change the `country` string of the robot at `index` position
    void travel(size_t index, const std::string& dest);

    //Call the `fight` method for every robot on the `target` enemy robot
    void fight(const RobotAgency& enemy, size_t target) const;

    //Call the `print` method on every robot
    void print_robots() const;
  private:
    //Array containing pointer to Robot
    std::shared_ptr<Robot> robots_[MAX_ROBOTS_SIZE];

    //Size of the array
    size_t cur_size_;
};
