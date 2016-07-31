#ifndef HD7DFDC0A_E6A2_4C6E_A3EF_3B8182623152
#define HD7DFDC0A_E6A2_4C6E_A3EF_3B8182623152

#include <tlp/tlp.h>

TLP_NS_BEGIN

#define __func_forward(Name, ...)   using Name = __VA_ARGS__
#define __func_forward_1(Name, ...) template<typename _1> using Name = __VA_ARGS__
#define __func_forward_2(Name, ...) template<typename _1, typename _2> using Name = __VA_ARGS__
#define __func_forward_3(Name, ...) template<typename _1, typename _2, typename _3> using Name = __VA_ARGS__
#define __func_forward_4(Name, ...) template<typename _1, typename _2, typename _3, typename _4> using Name = __VA_ARGS__

TLP_NS_END

#endif
