#ifndef H240DB723_EABE_43B0_B27C_0E7C3DB3F303
#define H240DB723_EABE_43B0_B27C_0E7C3DB3F303

#include <tlp/base/EmptyType.h>
#include <tlp/utils/UniqueName.h>
#include <tlp/test/details/TestRegister.h>

////////////////////////////////////////////////////////////////////////
#define FIXTURE(name)                                   \
TLP_NS::AutoFixtureRegister _JOIN(tlp_auto_fixture_register, name)(#name);   \
namespace _JOIN(TlpTestFixture_, name)

////////////////////////////////////////////////////////////////////////
#define TEST_SETUP_NAME   TlpTestSetUp
using   TEST_SETUP_NAME = TLP_NS::EmptyType;

#define SETUP()           struct TEST_SETUP_NAME
#define SETUP_BEGIN()     SETUP(){
#define SETUP_END()       };

////////////////////////////////////////////////////////////////////////
#define TEST_TEARDOWN_NAME   TlpTestTearDown
template<typename TLP_TEST>  struct TEST_TEARDOWN_NAME {};

#define TEARDOWN_BEGIN()                                \
template<typename TLP_TEST>  struct TEST_TEARDOWN_NAME  \
{                                                       \
    TEST_TEARDOWN_NAME()                                \
    {                                                   \
        struct TearDown: TLP_TEST                       \
        {

#define TEARDOWN_END()                              };}};

#define __test_refer(...)       typename TLP_TEST::__VA_ARGS__
#define __test_invoke(op, ...)  typename TLP_TEST:: template op<__VA_ARGS__>::Result

////////////////////////////////////////////////////////////////////////
#define __TEST_NAME(id)         _JOIN(tlp_test_, id)

#define __DEF_TEST(name, id)                                        \
struct __TEST_NAME(id);                                             \
TEST_TEARDOWN_NAME<__TEST_NAME(id)> _JOIN(tlp_test_teardown_, id);  \
TLP_NS::AutoTestRegister _JOIN(tlp_auto_test_register, id)(#name);  \
struct __TEST_NAME(id) : TEST_SETUP_NAME

#define TEST(name)   __DEF_TEST(name, UNIQUE_ID)

#endif
