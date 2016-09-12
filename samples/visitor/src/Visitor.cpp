#include <VisitorDef.h>
#include <iostream>
#include <memory>

namespace
{
    struct Animal;
    struct Cat;
    struct Dog;
    struct Mouse;

    using AnimalVisitor = visitor::VisitorGenerator<void, __type_list(Cat, Dog, Mouse)>;

    struct Animal
    {
        virtual void accept(AnimalVisitor&) = 0;
        virtual ~Animal() {}
    };

    struct Cat : Animal
    {
    private:
        DEFINE_VISITABLE(AnimalVisitor);
    };

    struct Dog : Animal
    {
    private:
        DEFINE_VISITABLE(AnimalVisitor);
    };

    struct Mouse : Animal
    {
    private:
        DEFINE_VISITABLE(AnimalVisitor);
    };

    struct RunVisitor : AnimalVisitor
    {
    private:
        void doVisit(Cat&) override
        {
            std::cout << "Cat is running!" << std::endl;
        }

        void doVisit(Dog&) override
        {
            std::cout << "Dog is running" << std::endl;
        }

        void doVisit(Mouse&) override
        {
            std::cout << "Mouse is running" << std::endl;
        }
    };

    struct CryVisitor : AnimalVisitor
    {
    private:
        void doVisit(Cat&) override
        {
            std::cout << "Cat is crying!" << std::endl;
        }

        void doVisit(Dog&) override
        {
            std::cout << "Dog is crying" << std::endl;
        }

        void doVisit(Mouse&) override
        {
            std::cout << "Mouse is crying" << std::endl;
        }
    };
};

int main()
{
    RunVisitor run;
    CryVisitor cry;

    Animal* animals[] = {new Cat, new Dog, new Mouse};

    animals[0]->accept(cry);
    animals[1]->accept(cry);
    animals[2]->accept(run);

    for(auto animal : animals) delete animal;

    return 0;
}
