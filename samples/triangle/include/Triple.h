#ifndef H088A985C_B64D_45E9_8BD6_0EADBB29CA48
#define H088A985C_B64D_45E9_8BD6_0EADBB29CA48

#include <tlp/list/algo/TypeList.h>

namespace triangle
{
    template<typename P1, typename P2, typename P3>
    struct Triple
    {
        using Result = __type_list(P1, P2, P3);
    };
}

#define __triple(...)   typename triangle::Triple<__VA_ARGS__>::Result

#endif
