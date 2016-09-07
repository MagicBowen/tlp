#ifndef H697DBCEC_12E1_4BA8_A95D_1ADF47ABBA80
#define H697DBCEC_12E1_4BA8_A95D_1ADF47ABBA80

#include <tlp/list/algo/TypeList.h>
#include <tlp/list/algo/IsIncluded.h>
#include <tlp/bool/BoolType.h>
#include <tlp/base/algo/Valid.h>

TLP_NS_BEGIN

template<typename T>
struct IsBuiltIn
{
private:
    using BuiltInTypes = __type_list(char, wchar_t, char16_t, char32_t, bool, short,
                                     int, long, long long, float, double, long double);

public:
    using Result = __is_included(BuiltInTypes, T);
};

TLP_NS_END

#define __is_built_in(...)  typename TLP_NS::IsBuiltIn<__VA_ARGS__>::Result

#endif
