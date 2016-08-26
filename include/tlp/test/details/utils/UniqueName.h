#ifndef HEE98F4BB_2BA6_4D1D_9889_EA8BD746A841
#define HEE98F4BB_2BA6_4D1D_9889_EA8BD746A841

#define __DO_STRINGIZE( symbol ) #symbol
#define _STRINGIZE(symbol) __DO_STRINGIZE(symbol)

////////////////////////////////////////////////////////////////////////////////
#define __DO_JOIN(symbol1, symbol2) symbol1##symbol2
#define _JOIN(symbol1, symbol2) __DO_JOIN(symbol1, symbol2)

////////////////////////////////////////////////////////////////////////////////
#ifdef __COUNTER__
# define UNIQUE_ID __COUNTER__
#else
# define UNIQUE_ID __LINE__
#endif

////////////////////////////////////////////////////////////////////////////////
# define UNIQUE_NAME(prefix) _JOIN(prefix, UNIQUE_ID)

#endif
