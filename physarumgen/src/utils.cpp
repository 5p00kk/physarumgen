#include "utils.h"

#include <cstdlib>

/* FROM: https://stackoverflow.com/a/44045388 */
bool random_bool()
{
   static const int shift = static_cast<int>(std::log2(RAND_MAX));
   return (rand() >> shift) & 1;
}

s_f_vec2 dest_position(float x, float y, float angle, float distance)
{
    s_f_vec2 ret_val{x + distance * std::cos((angle)*PI/180.0f), 
                     y + distance * std::sin((angle)*PI/180.0f)};
    return ret_val;
}