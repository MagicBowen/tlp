#ifndef H217F61F8_7901_4A47_B765_24D47FA326D0
#define H217F61F8_7901_4A47_B765_24D47FA326D0

#include <tlp/tlp.h>

TLP_NS_BEGIN

#define __def_func(Name, ...)   struct Name { using Result = __VA_ARGS__; }
#define __def_func_1(Name, ...) template<typename _1> struct Name { using Result = __VA_ARGS__; }
#define __def_func_2(Name, ...) template<typename _1, typename _2> struct Name { using Result = __VA_ARGS__; }
#define __def_func_3(Name, ...) template<typename _1, typename _2, typename _3> struct Name { using Result = __VA_ARGS__; }
#define __def_func_4(Name, ...) template<typename _1, typename _2, typename _3, typename _4> struct Name { using Result = __VA_ARGS__; }

TLP_NS_END

#endif
