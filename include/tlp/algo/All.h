#ifndef HDA5EBD3E_C192_420F_962B_DF1D83F25D2D
#define HDA5EBD3E_C192_420F_962B_DF1D83F25D2D

#include <tlp/algo/Any.h>
#include <tlp/utils/Not.h>

TLP_NS_BEGIN

template<typename TL, template<typename T> class Pred>
struct All
{
    enum { Value = !Any<TL, Not<Pred>::template Apply>::Value };
};

TLP_NS_END

#define __all(...) TLP_NS::All<__VA_ARGS__>::Value

#endif
