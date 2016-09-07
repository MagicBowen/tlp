#ifndef H088A985C_B64D_45E9_8BD6_0EADBB29CA48
#define H088A985C_B64D_45E9_8BD6_0EADBB29CA48

#include <tlp/func/Forward.h>
#include <tlp/list/algo/TypeList.h>

namespace triangle
{
    __func_forward_3(Triple, __type_list(_1, _2, _3));
}

#define __triple(...)   triangle::Triple<__VA_ARGS__>

#endif
