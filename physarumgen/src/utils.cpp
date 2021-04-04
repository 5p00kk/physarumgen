#include "utils.h"

#include <cstdlib>
#include <random>

bool operator==(const s_ui_vec2& lhs, const s_ui_vec2& rhs)
{
    return((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

bool operator!=(const s_ui_vec2& lhs, const s_ui_vec2& rhs)
{
    return((lhs.x != rhs.x) || (lhs.y != rhs.y));
}

bool operator==(const s_f_vec2& lhs, const s_f_vec2& rhs)
{
    return((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

bool operator!=(const s_f_vec2& lhs, const s_f_vec2& rhs)
{
    return((lhs.x != rhs.x) || (lhs.y != rhs.y));
}

/* FROM: https://stackoverflow.com/a/44045388 */
bool random_bool()
{
   static const int shift = static_cast<int>(std::log2(RAND_MAX));
   return (rand() >> shift) & 1;
}


float random_angle()
{
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist360(0, 359);
    return (float)dist360(rng);
}
