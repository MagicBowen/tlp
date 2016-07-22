#ifndef H166D0F49_5D4C_46C8_A9A1_0A3B55521C37
#define H166D0F49_5D4C_46C8_A9A1_0A3B55521C37

#include <tlp/tlp.h>

TLP_NS_BEGIN

template<typename T, typename U>
struct Convertible
{
private:
    using Small = char;
    struct Big { char dummy[2]; };

    static Small Test(U);
    static Big   Test(...);
    static T MakeT();

public:
    enum{ Value = sizeof(Test(MakeT())) == sizeof(Small) };
};

TLP_NS_END

#define CONVERTIBLE(...) TLP_NS::Convertible<__VA_ARGS__>::Value
#define BOTH_CONVERTIBLE(T, U) (CONVERTIBLE(T, U) && CONVERTIBLE(U, T))

#endif
