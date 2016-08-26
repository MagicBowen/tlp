#ifndef HAEB4E27F_9DA3_4117_A178_858B2149E0CB
#define HAEB4E27F_9DA3_4117_A178_858B2149E0CB

#include <tlp/tlp.h>
#include <tlp/test/details/utils/UniqueName.h>

TLP_NS_BEGIN

template <typename T>
struct Print
{
    const int Value = 1 / (sizeof(T) - sizeof(T));
};

TLP_NS_END

#define __print(...) TLP_NS::Print<__VA_ARGS__> UNIQUE_NAME(tlp_print_)

#endif
