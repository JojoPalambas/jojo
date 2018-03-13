#include "robot-agency.hh"
#include "robot-fighter.hh"
#include "armored-robot.hh"
#include "rocket-robot.hh"

RobotAgency::RobotAgency(std::shared_ptr<Robot> *robots, size_t robots_size)
{
    size_t size = robots_size < MAX_ROBOTS_SIZE ? robots_size : MAX_ROBOTS_SIZE;
    /*robots_ = new std::shared_ptr<Robot> [size];*/

    for (size_t i = 0; i < size; i++)
    {
        robots_[i] = robots[i];
    }
    cur_size_ = size;
}

bool RobotAgency::has_valid_robot() const
{
    for (size_t i = 0; i < cur_size_; i++)
    {
        if (robots_[i]->is_alive())
            return true;
    }
    return false;
}

std::optional<std::shared_ptr<Robot>> RobotAgency::get_robot(size_t index) const
{
    if (index >= cur_size_)
        return std::nullopt;
    return std::optional<std::shared_ptr<Robot>>{robots_[index]};
}

void RobotAgency::travel(size_t index, const std::string& dest)
{
    if (index >= cur_size_)
        return;
    robots_[index]->change_country(dest);
}

void RobotAgency::fight(const RobotAgency& enemy, size_t target) const
{
    std::optional<std::shared_ptr<Robot>> t = enemy.get_robot(target);
    if (!t || !(*t)->is_alive())
        return;

    for (size_t i = 0; i < cur_size_; i++)
        robots_[i]->fight(t);
}

void RobotAgency::print_robots() const
{
    for (size_t i = 0; i < cur_size_; i++)
        robots_[i]->print();
}

int main()
{
    auto armor_ptr = std::make_shared<ArmoredRobot>(1, "France", 40, 10);
    auto rocket_ptr = std::make_shared<RocketRobot>(1, "Espagne", 30);
    auto fighter_ptr = std::make_shared<RobotFighter>(2, "France", 45);
    auto fighter2_ptr = std::make_shared<RobotFighter>(1, "France", 20);

    std::shared_ptr<Robot> alliance_arr[2] = { armor_ptr, rocket_ptr };
    auto all_agency = RobotAgency(alliance_arr, 2);

    std::shared_ptr<Robot> republic_arr[2] = { fighter_ptr, fighter2_ptr };
    auto all_agency = RobotAgency(republic_arr, 2);

    all_agency.fight(rep_agency, 2);
    rep_agency.fight(all_agency, 0);

    std::cout << "Printing Alliance agency\n";
    all_agency.print_robots();

    std::cout << std::endl;

    std::cout << "Printing Republic agency\n";
    rep_agency.print_robots();
}
