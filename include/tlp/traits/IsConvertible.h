#ifndef H166D0F49_5D4C_46C8_A9A1_0A3B55521C37
#define H166D0F49_5D4C_46C8_A9A1_0A3B55521C37

#include <tlp/bool/BoolType.h>
#include <tlp/bool/algo/And.h>

TLP_NS_BEGIN

template<typename T, typename U>
struct IsConvertible
{
private:
    using  Yes = char;
    struct No { char dummy[2]; };

    static Yes test(U);
    static No  test(...);
    static T self();

public:
    using Result = BoolType<sizeof(test(self())) == sizeof(Yes)>;
};

TLP_NS_END

#define __is_convertible(...)           typename TLP_NS::IsConvertible<__VA_ARGS__>::Result
#define __is_both_convertible(T, U)     __and(__is_convertible(T, U), __is_convertible(U, T))

#endif
