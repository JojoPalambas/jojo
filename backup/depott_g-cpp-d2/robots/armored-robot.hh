#include "robot.hh"

#ifndef ROBOT_ARMORED_HH
#define ROBOT_ARMORED_HH

/* Class for armored-type robots */
class ArmoredRobot: public Robot
{
public:
    ArmoredRobot(int id, const std::string& country,
            size_t armor, size_t attack)
        : Robot(id, country)
        , armor_(armor)
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
    size_t armor_;
    size_t attack_;
};

#endif
