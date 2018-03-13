#include "robot.hh"

#ifndef ROBOT_FIGHTER_HH
#define ROBOT_FIGHTER_HH

/* Class for fighter-type robots */
class RobotFighter: public Robot
{
public:
    RobotFighter(int id, const std::string& country, size_t attack)
        : Robot(id, country)
        , attack_(attack)
    {
    }

    /* Decreases the robot's health */
    void take_damage(size_t attack) override;

    /* Make the robot introduce itself */
    void print() const override;

    /* Inflicts damage to another robot */
    void fight(Robot& enemy) const override;

private:
    size_t attack_;
};

#endif
