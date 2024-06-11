#pragma once
#include "../../ExtendedMenu/ICommand.h"
#include <random>

class StressTestCommand : public ICommand
{
public:
    class RandomGenerator
    {
    private:
        std::random_device rd;
        std::mt19937 mt;
        std::uniform_int_distribution<int> dist;

    public:
        RandomGenerator(int min, int max) : rd(), mt(rd()), dist(min, max) {}

        int get() { return dist(mt); }
    };

    StressTestCommand(/* args */);
    ~StressTestCommand();
    void exec() override;
    StressTestCommand *clone() override;
};
