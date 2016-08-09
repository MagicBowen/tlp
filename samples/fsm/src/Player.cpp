#include <StateMachine.h>
#include <string>

namespace
{
    // Events
    struct Play{};
    struct OpenClose{};
    struct CdDetected
    {
        CdDetected(const char* name, size_t minutes)
        : name(name), minutes(minutes)
        {
        }

        std::string name;
        size_t minutes;
    };
    struct Pause{};
    struct Stop{};

    // FSM
    struct Player : fsm::StateMachine<Player>
    {
    private:
        enum States
        {
            empty, open, stopped, playing, paused, initial = empty
        };

        void startPlayback(const Play&)
        {
            std::cout << "execute : startPlayback" << std::endl;
        }

        void openDrawer(const OpenClose&)
        {
            std::cout << "execute : openDrawer" << std::endl;
        }

        void closeDrawer(const OpenClose&)
        {
            std::cout << "execute : closeDrawer" << std::endl;
        }

        void storeCdInfo(const CdDetected& cd)
        {
            std::cout << "execute : storeCdInfo";
            std::cout << " (cd info: " << cd.name << ", length : " << cd.minutes << " minutes...)" << std::endl;
        }

        void stopPlayback(const Stop&)
        {
            std::cout << "execute : stopPlayback" << std::endl;
        }

        void pausePlayback(const Pause&)
        {
            std::cout << "execute : pausePlayback" << std::endl;
        }

        void resumePlayback(const Play&)
        {
            std::cout << "execute : resumePlayback" << std::endl;
        }

        void stopAndOpen(const OpenClose&)
        {
            std::cout << "execute : stopAndOpen" << std::endl;
        }

        using P = Player;

        friend struct StateMachine<Player>;

        using TransitionTable = __type_list(
                //  +-----------+---------------+-----------+-----------------------+
                //  |   initial |   event       |   target  |   action              |
                //  +-----------+---------------+-----------+-----------------------+
                Row <   stopped ,   Play        ,   playing ,   &P::startPlayback   >,
                Row <   stopped ,   OpenClose   ,   open    ,   &P::openDrawer      >,
                //  +-----------+---------------+-----------+-----------------------+
                Row <   open    ,   OpenClose   ,   empty   ,   &P::closeDrawer     >,
                //  +-----------+---------------+-----------+-----------------------+
                Row <   empty   ,   OpenClose   ,   open    ,   &P::openDrawer      >,
                Row <   empty   ,   CdDetected  ,   stopped ,   &P::storeCdInfo     >,
                //  +-----------+---------------+-----------+-----------------------+
                Row <   playing ,   Stop        ,   stopped ,   &P::stopPlayback    >,
                Row <   playing ,   Pause       ,   paused  ,   &P::pausePlayback   >,
                Row <   playing ,   OpenClose   ,   open    ,   &P::stopAndOpen     >,
                //  +-----------+---------------+-----------+-----------------------+
                Row <   paused  ,   Play        ,   playing ,   &P::resumePlayback  >,
                Row <   paused  ,   Stop        ,   stopped ,   &P::stopPlayback    >,
                Row <   paused  ,   OpenClose   ,   open    ,   &P::stopAndOpen     >
                //  +-----------+---------------+-----------+-----------------------+
        );
    };
}

int main()
{
    Player p;

    p.processEvent(OpenClose());
    p.processEvent(OpenClose());
    p.processEvent(CdDetected("rock", 60));
    p.processEvent(Play());
    p.processEvent(Pause());
    p.processEvent(Play());
    p.processEvent(Stop());
    p.processEvent(Pause());

    return 0;
}


