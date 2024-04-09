#pragma once
class IPair{
public:
    IPair() = default;
    ~IPair() = default;
    virtual void work();
    virtual void printWork();
};