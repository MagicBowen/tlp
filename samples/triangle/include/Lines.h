#ifndef HA124DDD2_B15F_4436_BC1B_A896685E79F7
#define HA124DDD2_B15F_4436_BC1B_A896685E79F7

#include <tlp/func/Forward.h>
#include <tlp/list/algo/TypeList.h>

namespace triangle
{
    __func_forward_oo(Lines, __type_list(_oo...));

}

#define __lines(...)  triangle::Lines<__VA_ARGS__>

#endif
