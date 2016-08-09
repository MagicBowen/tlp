#include <VisitorDef.h>

namespace
{
    struct DocElem;
    struct Paragraph;
    struct Picture;

    using MyVisitor = visitor::VisitorGenerator<void, __type_list(DocElem, Paragraph, Picture)>;

    struct DocElem
    {
        virtual void accept(MyVisitor&) = 0;
        virtual ~DocElem() {}
    };

    struct Paragraph : DocElem
    {
    private:
        DEFINE_VISITABLE(MyVisitor);
    };

    struct Picture : DocElem
    {
    private:
        DEFINE_VISITABLE(MyVisitor);
    };

    struct ConcreteVisitor : MyVisitor
    {
    private:
        void doVisit(DocElem&) override
        {
            std::cout << "DocElem" << std::endl;
        }

        void doVisit(Paragraph&) override
        {
            std::cout << "Paragraph" << std::endl;
        }

        void doVisit(Picture&) override
        {
            std::cout << "Picture" << std::endl;
        }
    };
};

int main()
{
    ConcreteVisitor visitor;

    Picture picture;
    static_cast<DocElem&>(picture).accept(visitor);

    Paragraph para;
    static_cast<DocElem&>(para).accept(visitor);

    return 0;
}
