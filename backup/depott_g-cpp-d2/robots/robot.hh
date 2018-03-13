#include <memory>
#include <iostream>
#include <string>
#include <optional>

#ifndef ROBOT_HH
#define ROBOT_HH

/* Common class for every subclasse of robots */
class Robot
{
public:
    Robot(int id, const std::string& country)
        : id_(id)
        , country_(country)
        , health_(100)
    {
    }

    /* Changes the country of the robot */
    void change_country(const std::string& country)
    {
        country_ = country;
    }

    /* Returns the country of the robot */
    const std::string& get_country() const
    {
        return country_;
    }

    /* Checks if the robot is "alive" */
    bool is_alive() const
    {
        return health_ > 0;
    }

    /* Decreases the robot's health */
    virtual void take_damage(size_t attack) = 0;

    /* Makes the robot introduce itself */
    virtual void print() const = 0;

    /* Inflicts damage to another robot */
    virtual void fight(Robot& enemy) const = 0;

protected:
    int id_;
    std::string country_;
    int health_;
};

#endif
