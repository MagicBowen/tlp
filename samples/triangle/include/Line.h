#ifndef HDF1F8256_19AF_43C5_B868_901465BD519B
#define HDF1F8256_19AF_43C5_B868_901465BD519B

#include <tlp/list/algo/TypeList.h>
#include <tlp/func/Forward.h>

namespace triangle
{
    __func_forward_oo(Line, __type_list(_oo...));

}

#define __line(...)   triangle::Line<__VA_ARGS__>
#define __lines(...)  __type_list(__VA_ARGS__)

#endif
