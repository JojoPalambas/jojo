#include "robot.hh"
#include "rocket-robot.hh"

void RocketRobot::take_damage(size_t attack)
{
    health_ -= attack;
}

void RocketRobot::print() const
{
    std::cout << "Reporting for duty! I'm rocket robot number " << id_
        << ". I am currently in " << country_ << ". I still have "
        << health_ << "hp left!" << std::endl;
}

void RocketRobot::fight(Robot& enemy) const
{
    if (!is_alive())
        return;

    enemy.take_damage(attack_);
}
