#ifndef H726355C0_FC72_492C_BBDE_9B9CE70DBB1B
#define H726355C0_FC72_492C_BBDE_9B9CE70DBB1B

#include <tlp/tlp.h>

TLP_NS_BEGIN

#define __def_pred(Name, ...)                       \
template<typename ...Paras> struct Name;            \
template<> struct Name<>{ using Result = __VA_ARGS__; }

#define __def_pred_1(Name, ...)                     \
template<typename ...Paras> struct Name;            \
template<typename _1> struct Name<_1>{ using Result = __VA_ARGS__; }

TLP_NS_END

#endif
