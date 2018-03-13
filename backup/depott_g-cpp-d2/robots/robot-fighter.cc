#include "robot.hh"
#include "robot-fighter.hh"

void RobotFighter::take_damage(size_t attack)
{
    health_ -= attack;
}

void RobotFighter::print() const
{
    std::cout << "Reporting for duty! I'm robot fighter number " << id_
        << ". I am currently in " << country_ << ". I still have "
        << health_ << "hp left!" << std::endl;
}

void RobotFighter::fight(Robot& enemy) const
{
    if (!is_alive())
        return;

    if (!country_.compare(enemy.get_country()))
        enemy.take_damage(attack_);
}
