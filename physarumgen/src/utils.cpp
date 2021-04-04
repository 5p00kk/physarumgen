#include "utils.h"

#include <cstdlib>

/* FROM: https://stackoverflow.com/a/44045388 */
bool random_bool()
{
   static const int shift = static_cast<int>(std::log2(RAND_MAX));
   return (rand() >> shift) & 1;
}


float random_angle()
{
    static std::random_device dev;
    static std::mt19937 rng(m_dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist360(0, 359);
    return (float)m_dist360(rng);
}
