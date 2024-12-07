#pragma once

class IHaveWeight {
private:
    int _weight;

public:
    IHaveWeight(int weight) : _weight(weight) {} 

    virtual int getWeight() const;
};
