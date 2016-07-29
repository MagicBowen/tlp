#ifndef HDA5EBD3E_C192_420F_962B_DF1D83F25D2D
#define HDA5EBD3E_C192_420F_962B_DF1D83F25D2D

#include <tlp/list/algo/Any.h>
#include <tlp/bool/algo/Not.h>
#include <tlp/func/Negative.h>

TLP_NS_BEGIN

template<typename TL, template<typename T> class Pred>
struct All
{
    using Result = typename Not<typename Any<TL, Negative<Pred>::template Apply>::Result>::Result;
};

TLP_NS_END

#define __all(...)   typename TLP_NS::All<__VA_ARGS__>::Result

#endif
