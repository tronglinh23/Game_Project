#pragma once
#include <BaseObject.hpp>
#include <vector>
class PlayerPower: public BaseObject
{
public:
    PlayerPower();
    ~PlayerPower();
    void SetNumber(const int& num) {number_ = num;}
    void AddPos( const int& xpos);
    void DisplayLife(SDL_Renderer* des);
    void Init();
    void Decrease();
    void Increase();
private:
    int number_;
    std::vector<int> pos_life_;
};