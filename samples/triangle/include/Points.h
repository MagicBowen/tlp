#ifndef HD0E7D0DA_7583_4BC9_B7C2_58C3CF230F8F
#define HD0E7D0DA_7583_4BC9_B7C2_58C3CF230F8F

#include <tlp/func/Forward.h>
#include <tlp/list/algo/TypeList.h>

namespace triangle
{
    __func_forward_oo(Points, __type_list(_oo...));
}

#define __points(...)   triangle::Points<__VA_ARGS__>

#endif
