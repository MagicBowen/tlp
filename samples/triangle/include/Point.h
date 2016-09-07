#ifndef H697E9811_4AB8_4ADB_8284_CF84BBA40794
#define H697E9811_4AB8_4ADB_8284_CF84BBA40794

#include <tlp/func/Forward.h>
#include <tlp/list/algo/TypeList.h>

namespace triangle
{
    __func_forward_1(Point, _1);
}

#define __p(N)  triangle::Point<__int(N)>
#define __points(...) __type_list(__VA_ARGS__)

#endif
