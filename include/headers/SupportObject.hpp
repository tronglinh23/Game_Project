#pragma once

#include "Common_function.hpp"
#include "BaseObject.hpp"
#include "ThreatObject.hpp"

class SupportObject: public ThreatObject
{
public:
    SupportObject();
    ~SupportObject();
    void Hand_Support_Move(const int& x_border, const int& y_border);
    void Set_x_pos(const int& val) {x_val_ = val;}
    void Remove_support_Object(const int& x_border);
private:
    int x_val_, y_val_;
};