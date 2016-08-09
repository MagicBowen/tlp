#ifndef HD32859A3_2126_496E_90DB_8149C3B25EDE
#define HD32859A3_2126_496E_90DB_8149C3B25EDE

#include <tlp/list/algo/TypeList.h>
#include <tlp/list/algo/ScatterInherits.h>

namespace visitor
{
    namespace details
    {
        template<typename R, typename T>
        struct Visitor
        {
            virtual R doVisit(T&) = 0;
            virtual ~Visitor() {}
        };

        template<typename R>
        struct VisitorBinder
        {
            template<typename T>
            using Result = Visitor<R, T>;
        };
    }

    template<typename R, typename TL>
    struct VisitorGenerator : __scatter_inherits(TL, details::VisitorBinder<R>::template Result)
    {
        using ResultType = R;

        template<typename Visited>
        ResultType visit(Visited& host)
        {
            return static_cast<details::Visitor<R, Visited>*>(this)->doVisit(host);
        }
    };
}

#endif

#define DEFINE_VISITABLE(VISITOR)           \
void accept(VISITOR& visitor) override      \
{                                           \
    visitor.visit(*this);                   \
}
