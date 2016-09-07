#include <tlp/test/Test.hpp>
#include <tlp/list/algo/Comb.h>
#include <Point.h>
#include <Line.h>
#include <Points.h>
#include <Lines.h>
#include <Triple.h>
#include <CountTriangles.h>

FIXTURE(TestTriangle)
{
    using Lines = __lines( __line(__p('a'), __p('b'), __p('h'))
                         , __line(__p('a'), __p('c'), __p('g'), __p('i'))
                         , __line(__p('a'), __p('d'), __p('f'), __p('j'))
                         , __line(__p('a'), __p('e'), __p('k'))
                         , __line(__p('b'), __p('c'), __p('d'), __p('e'))
                         , __line(__p('h'), __p('g'), __p('f'), __p('e'))
                         , __line(__p('h'), __p('i'), __p('j'), __p('k')));

    TEST("test triangle")
    {
        ASSERT_TRUE(__is_triangle(__triple(__p('a'), __p('b'), __p('c')), Lines));
        ASSERT_FALSE(__is_triangle(__triple(__p('a'), __p('b'), __p('h')), Lines));
    };

    TEST("count triangles")
    {
        using Points = __points( __p('a'), __p('b'), __p('c'), __p('d'), __p('e'), __p('f')
                               , __p('g'), __p('h'), __p('i'), __p('j'), __p('k'));

        using TriplePoints = __comb(Points, __int(3));

        ASSERT_EQ(__count_triangles(TriplePoints, Lines), __int(24));
    };
}

int main()
{
    TLP_REPORT_ALL_TESTS();
    return 0;
}
