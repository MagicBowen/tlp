#ifndef HAEB4E27F_9DA3_4117_A178_858B2149E0CB
#define HAEB4E27F_9DA3_4117_A178_858B2149E0CB

#include <tlp/tlp.h>
#include <tlp/utils/UniqueName.h>

TLP_NS_BEGIN

template<int V>
struct Print
{
    operator char()
    {
        return V + 0xFF; // INVOKE OVERFLOW WARNNING LOG !
    }
};

TLP_NS_END

#define __print(value) char UNIQUE_NAME(tlp_print_) = TLP_NS::Print<value>()

#endif
