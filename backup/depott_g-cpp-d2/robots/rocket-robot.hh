#include "robot.hh"

#ifndef ROCKET_ROBOT_HH
#define ROCKET_ROBOT_HH

/* Class for rocket-type robots */
class RocketRobot: public Robot
{
public:
    RocketRobot(int id, const std::string& country, size_t attack)
        : Robot(id, country)
        , attack_(attack)
    {
    }

    /* Decreases the robot's armor before the robot's health */
    void take_damage(size_t attack) override;

    /* Makes the robot introduce itself */
    void print() const override;

    /* Inflicts damage to another robot */
    void fight(Robot& enemy) const override;

private:
    size_t attack_;
};

#endif
