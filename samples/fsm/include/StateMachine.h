#ifndef H0CA09D4E_981F_4390_A7B6_1F953CC66C08
#define H0CA09D4E_981F_4390_A7B6_1F953CC66C08

#include <tlp/list/algo/TypeList.h>
#include <tlp/list/algo/Fold.h>
#include <tlp/list/algo/Filter.h>
#include <tlp/bool/algo/IsEqual.h>
#include <tlp/func/Forward.h>
#include <typeinfo>
#include <iostream>

namespace fsm
{
    namespace details
    {
        template<typename Next, typename Transition>
        struct EventDispatcher
        {
            using Fsm = typename Transition::Fsm;
            using Event = typename Transition::Event;

            static int dispatch(Fsm& fsm, int state, const Event& e)
            {
                if(state == Transition::current)
                {
                    Transition::execute(fsm, e);
                    return Transition::next;
                }
                else
                {
                    return Next::dispatch(fsm, state, e);
                }
            }

            using Result = EventDispatcher;
        };

        struct DefaultDispatcher
        {
            template<typename Fsm, typename Event>
            static int dispatch(Fsm& fsm, int state, const Event& e)
            {
                return fsm.onUndefined(state, e);
            }
        };

        template<typename Event, typename Transition>
        struct EventMatcher
        {
            using Result = __is_eq(Event, typename Transition::Event);
        };

        template<typename Table, typename Event>
        struct DispatcherGenerator
        {
        private:
            template<typename Transition>
            using TransitionMatcher = typename EventMatcher<Event, Transition>::Result;

            using MatchedTransitions = __filter(Table, TransitionMatcher);

        public:
            using Result = __fold(MatchedTransitions, DefaultDispatcher, EventDispatcher);
        };
    }

    template<typename Derived>
    struct StateMachine
    {
        template<typename Event>
        int processEvent(const Event& e)
        {
            using Dispatcher = typename details::DispatcherGenerator<typename Derived::TransitionTable, Event>::Result;

            this->state = Dispatcher::dispatch(*static_cast<Derived*>(this), this->state, e);

            return this->state;
        }

        template<typename Event>
        int onUndefined(int state, const Event& e)
        {
            return static_cast<Derived*>(this)->noTransition(state, e);
        }

    protected:
        template< int CurrentState,
                  typename EventType,
                  int NextState,
                  void (Derived::*action)(const EventType&) >
        struct Row
        {
            enum
            {
                current = CurrentState,
                next = NextState
            };

            using Fsm = Derived;
            using Event = EventType;

            static void execute(Fsm& fsm, const Event& e)
            {
                (fsm.*action)(e);
            }
        };

        template<typename Event>
        int noTransition(int state, const Event& e)
        {
            std::cout << "Error: no transition on state(" << state << ") handle event( " << typeid(e).name() << " )" << std::endl;
            return state;
        }

    protected:
        StateMachine() : state(Derived::initial)
        {
        }

    private:
        int state;
    };
}

#endif
