#pragma once

#include <math.h>

#define PI 3.14159265

struct s_vec2
{
    unsigned int x;
    unsigned int y;
};

inline unsigned int to_grid(float value)
{
    return std::round(value);
};