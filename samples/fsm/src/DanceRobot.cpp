
// Assume existing a dancing robot:
// It has 3 states:          { closed,  opened,  dancing }
// It can receive 4 events : { close,   open,    play,   stop }
// It can do 4 actions :     { sayReady,  sayClosed,  doDance,  sayStoped}

// The following table describes how the robot acting in detail!

/*******************************************************************/
/*  Current State |   Event    |    Next State     |   Action      */
/*----------------|------------|-------------------|---------------*/
/*   closed       |   open     |     opened        |   sayReady    */
/*----------------|------------|-------------------|---------------*/
/*   opened       |   close    |     closed        |   sayClosed   */
/*----------------|------------|-------------------|---------------*/
/*   opened       |   play     |     dancing       |   doDance     */
/*----------------|------------|-------------------|---------------*/
/*   dancing      |   stop     |     opened        |   sayStoped   */
/*----------------|------------|-------------------|---------------*/
/*   dancing      |   close    |     closed        |   sayClosed   */
/*******************************************************************/

#include <StateMachine.h>
#include <string>

namespace
{
    // Events
    struct Close {};
    struct Open {};
    struct Play
    {
        std::string name;
    };
    struct Stop {};
}

namespace NormalImplementation
{
    struct DanceRobot
    {
        void processEvent(const Open& event)
        {
            if(state == closed)
            {
                sayReady(event);
                state = opened;
            }
            else
            {
                reportError(event);
            }
        }

        void processEvent(const Close& event)
        {
            if(state == opened)
            {
                sayClosed(event);
                state = closed;
            }
            else if(state == dancing)
            {
                sayClosed(event);
                state = closed;
            }
            else
            {
                reportError(event);
            }
        }

        void processEvent(const Play& event)
        {
            if(state == opened)
            {
                doDance(event);
                state = dancing;
            }
            else
            {
                reportError(event);
            }
        }

        void processEvent(const Stop& event)
        {
            if(state == dancing)
            {
                sayStoped(event);
                state = opened;
            }
            else
            {
                reportError(event);
            }
        }

    private:
        // actions
        void sayReady(const Open&)
        {
            std::cout << "Robot is ready for play!" << std::endl;
        }

        void sayClosed(const Close&)
        {
            std::cout << "Robot is closed!" << std::endl;
        }

        void sayStoped(const Stop&)
        {
            std::cout << "Robot stops playing!" << std::endl;
        }

        void doDance(const Play& playInfo)
        {
            std::cout << "Robot is dancing (" << playInfo.name << ") now!" << std::endl;
        }

        template<typename Event>
        void reportError(Event& event)
        {
            std::cout << "Error: robot on state(" << state
                      << ") receives unknown event( " << typeid(event).name() << " )" << std::endl;
        }

    private:
        enum
        {
            closed, opened, dancing, initial = closed

        }state{initial};
    };
}

namespace DslImplementation
{
    struct DanceRobot : fsm::StateMachine<DanceRobot>
    {
    private:
        friend struct StateMachine<DanceRobot>;

        enum States
        {
            closed, opened, dancing, initial = closed
        };

        // actions
        void sayReady(const Open&)
        {
            std::cout << "Robot is ready for play!" << std::endl;
        }

        void sayClosed(const Close&)
        {
            std::cout << "Robot is closed!" << std::endl;
        }

        void sayStoped(const Stop&)
        {
            std::cout << "Robot stops playing!" << std::endl;
        }

        void doDance(const Play& playInfo)
        {
            std::cout << "Robot is dancing (" << playInfo.name << ") now!" << std::endl;
        }

        // table
        using R = DanceRobot;

        using TransitionTable = __type_list(
                //  +----------+----------+----------+----------------+
                //  |  current |   event  |  target  |  action        |
                //  +----------+----------+----------+----------------+
                Row <  closed  ,   Open   ,  opened  ,  &R::sayReady  >,
                //  +----------+----------+----------+----------------+
                Row <  opened  ,   Close  ,  closed  ,  &R::sayClosed >,
                Row <  opened  ,   Play   ,  dancing ,  &R::doDance   >,
                //  +----------+----------+----------+----------------+
                Row <  dancing ,   Stop   ,  opened  ,  &R::sayStoped >,
                Row <  dancing ,   Close  ,  closed  ,  &R::sayClosed >
                //  +----------+----------+----------+----------------+
        );
    };
}

int main()
{
    using namespace DslImplementation;

    DanceRobot robot;

    robot.processEvent(Open());
    robot.processEvent(Close());
    robot.processEvent(Open());
    robot.processEvent(Play{.name = "hip-hop"});
    robot.processEvent(Stop());
    robot.processEvent(Close());

    robot.processEvent(Stop());

    return 0;
}
