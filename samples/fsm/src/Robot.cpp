
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

    // FSM
    struct Robot : fsm::StateMachine<Robot>
    {
    private:
        friend struct StateMachine<Robot>;

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
        using TransitionTable = __type_list(
                //  +-----------+---------------+-----------+-----------------------+
                //  |   current |   event       |   target  |   action              |
                //  +-----------+---------------+-----------+-----------------------+
                Row <   closed  ,   Open        ,   opened  ,   &Robot::sayReady    >,
                //  +-----------+---------------+-----------+-----------------------+
                Row <   opened  ,   Close       ,   closed  ,   &Robot::sayClosed   >,
                Row <   opened  ,   Play        ,   dancing ,   &Robot::doDance     >,
                //  +-----------+---------------+-----------+-----------------------+
                Row <   dancing ,   Stop        ,   opened  ,   &Robot::sayStoped   >,
                Row <   dancing ,   Close       ,   closed  ,   &Robot::sayClosed   >
                //  +-----------+---------------+-----------+-----------------------+
        );
    };
}

int main()
{
    Robot robot;

    robot.processEvent(Open());
    robot.processEvent(Close());
    robot.processEvent(Open());
    robot.processEvent(Play{.name = "hip-hop"});
    robot.processEvent(Stop());
    robot.processEvent(Close());

    robot.processEvent(Stop());

    return 0;
}
