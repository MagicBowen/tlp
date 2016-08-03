#ifndef H240DB723_EABE_43B0_B27C_0E7C3DB3F303
#define H240DB723_EABE_43B0_B27C_0E7C3DB3F303

#include <tlp/base/EmptyType.h>
#include <tlp/utils/UniqueName.h>

using TlpSetUp = TLP_NS::EmptyType;

template<typename TEST> struct TlpTearDown {};

////////////////////////////////////////////////////////////////////////
#define FIXTURE(name)       namespace _JOIN(TlpTestFixture_, name)

////////////////////////////////////////////////////////////////////////
#define SETUP()             struct TlpSetUp

#define SETUP_BEGIN()       SETUP(){
#define SETUP_END()         };

////////////////////////////////////////////////////////////////////////
#define TEARDOWN_BEGIN()                        \
template<typename TLP_TEST> struct TlpTearDown  \
{                                               \
    TlpTearDown()                               \
    {                                           \
        struct TearDown: TLP_TEST               \
        {

#define TEARDOWN_END()                      };}};

#define __test_refer(...)       typename TLP_TEST::__VA_ARGS__
#define __test_invoke(op, ...)  typename TLP_TEST:: template op<__VA_ARGS__>::Result

////////////////////////////////////////////////////////////////////////
#define __TEST_NAME(id)     _JOIN(tlp_test_, id)

#define __DEF_TEST(name, id)                    \
struct __TEST_NAME(id);                         \
TlpTearDown<__TEST_NAME(id)> _JOIN(tlp_teardown_, id);\
struct __TEST_NAME(id) : TlpSetUp               \

#define TEST(name)   __DEF_TEST(name, UNIQUE_ID)

#endif
