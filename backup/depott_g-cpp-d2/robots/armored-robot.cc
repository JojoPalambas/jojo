#include "robot.hh"
#include "armored-robot.hh"

void ArmoredRobot::take_damage(size_t attack)
{
    if (!armor_)
        health_ -= attack;
    else if (armor_ < attack)
    {
        attack -= armor_;
        armor_ = 0;
        health_ -= attack;
    }
    else
        armor_ -= attack;
}

void ArmoredRobot::print() const
{
    std::cout << "Reporting for duty! I'm armored robot number " << id_
        << ". I am currently in " << country_ << ". I still have "
        << armor_ << " armor and " << health_ << "hp left!" << std::endl;
}

void ArmoredRobot::fight(Robot& enemy) const
{
    if (!is_alive())
        return;

    if (!country_.compare(enemy.get_country()))
        enemy.take_damage(attack_);
}
