#ifndef H35304C94_5B27_4A02_A90F_FB248D0866E7
#define H35304C94_5B27_4A02_A90F_FB248D0866E7

#include <tlp/tlp.h>
#include <string>
#include <vector>
#include <set>

TLP_NS_BEGIN

struct TestReporter
{
    virtual void onFixtureStart(std::string name, size_t testNum) = 0;
    virtual void onFixtureEnd(std::string name, size_t testNum) = 0;
    virtual void onTest(std::string fixtureName, std::string testName) = 0;
    virtual ~TestReporter(){};
};

struct TestRegister
{
private:
    struct Test
    {
        Test(const std::string& name) : name(name)
        {
        }

        std::string name;
    };

    struct Fixture
    {
        Fixture(const std::string& name) : name(name)
        {
        }

        bool operator< (const Fixture& rhs) const
        {
            return name < rhs.name;
        }

        void addTest(const Test& test) const
        {
            tests.push_back(test);
        }

        void report(TestReporter& reporter) const
        {
            reporter.onFixtureStart(name, tests.size());

            for(auto test : tests)
            {
                reporter.onTest(name, test.name);
            }

            reporter.onFixtureEnd(name, tests.size());
        }

    private:
        mutable std::vector<Test> tests;
        std::string name;
    };

    using Fixtures = std::set<Fixture>;
    Fixtures fixtures;
    std::string lastFixtureName;

    bool isExisted(const Fixture& fixture) const
    {
        return !(fixtures.find(fixture) == fixtures.end());
    }

public:
    void addFixture(const std::string& name)
    {
        lastFixtureName = name;

        Fixture fixture(name);

        if(!isExisted(fixture)) fixtures.insert(fixture);
    }

    void addTest(const std::string& testName)
    {
        auto fixture = fixtures.find(Fixture(lastFixtureName));
        fixture->addTest(Test(testName));
    }

    void report(TestReporter& reporter) const
    {
        for(auto fixture : fixtures)
        {
            fixture.report(reporter);
        }
    }

    static TestRegister& getInstance()
    {
        static TestRegister instance;
        return instance;
    }
};

struct AutoFixtureRegister
{
    AutoFixtureRegister(const std::string& fixture)
    {
        TestRegister::getInstance().addFixture(fixture);
    }
};

struct AutoTestRegister
{
    AutoTestRegister(const std::string test)
    {
        TestRegister::getInstance().addTest(test);
    }
};

TLP_NS_END

#endif
