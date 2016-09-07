#ifndef H3D3D0E97_F53A_429D_8969_D09A1C979871
#define H3D3D0E97_F53A_429D_8969_D09A1C979871

#include <IsTriangle.h>
#include <tlp/int/algo/Add.h>
#include <tlp/list/algo/Fold.h>
#include <tlp/bool/algo/IfThenElse.h>

namespace triangle
{
    template<typename Triples, typename Lines>
    struct CountTriangles
    {
    private:
        template<typename Acc, typename Triple>
        struct Count
        {
            using Result = __if(__is_triangle(Triple, Lines), __add(Acc, __int(1)), Acc);
        };

    public:
        using Result = __fold(Triples, __int(0), Count);
    };
}

#define __count_triangles(...)  typename triangle::CountTriangles<__VA_ARGS__>::Result

#endif
