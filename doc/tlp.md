# TLP: learning template meta programming by C++11

[toc]

## 前言

熟悉C\++的程序员都知道，C\++是一门多范式编程语言，支持面向过程、面向对象、泛型编程以及函数式编程范式。然而提到C\++模板元编程，在很多人心里这却似乎是C\++里的一种黑魔法：它很难学习，一旦进入这个领域曾经那些熟悉的东西（if，for...）都不再灵验；它很强大，但现实中却鲜见有人用它来解决实际问题，除过偶尔在一些编码练习中被某些C\++狂热粉作为奇淫巧技拿出来秀肌肉。

其实模板元编程是C\++所支持的一种非常强大的计算能力，它是使用C\++开发高质量库和框架所离不开的一项武器。

掌握C\++模板元编程，可以帮助你做到：

- 实现高扩展性，并且兼具高性能的库
- 实现更加灵活且易于使用的框架
- 实现基于C\++的内部DSL（Domain Special Language）
- 帮助更好地理解并使用模板和泛型编程，更深入地使用C\++ STL库的一些高级特性

如果你是一个C\++的库或框架的开发者，了解和掌握一些模板元编程的知识，可能会让你的作品更易于扩展、拥有更易用的接口，甚至更高的运行时效率。而即使你只使用C\++设计和开发应用程序，了解模板元编程也会帮助你更好的去使用STL库的各种特性，甚至帮助你的局部设计做的更加漂亮。

实际上C\++模板元编程技术已经渗透在我们日常使用的各种库和框架中，例如STL库以及各种xUnit测试框架和mock框架。可以说，模板元编程是中级C\++程序员迈向高级的必经之路！

然而现实是，C\++模板元编程的学习之旅却并不平坦。

一方面，由于C\++模板元编程的本质是函数式编程，熟练掌握并使用函数式编程的程序员比较小众，绝大多数程序员初次进入这个领域时面对模式匹配、递归和不可变性时都会手足无措。另一方面，由于C\++的模板元编程能力是被意外发现的，不像别的函数式编程语言经过良好的设计，所以C\++的这种函数式计算能力天生存在着各种缺陷，直到C\++11标准才开始逐渐完善起来。在之前很多重要特性都要靠很绕的方式去迂回实现，增加了学习的难度。

另外，市面上介绍模板元编程的书和资料也乏善可陈，以下的书相对还不错，但对于模板元编程的介绍仍旧存在一些问题：

- 《C\++ Templates Complete》
	介绍C++模板知识最全面的一本书，涉及到了模板各个方面的基础知识和应用技巧。由于元编程并不是此书重点，所以仅有短短一章列举了一些利用模板元编程做数值计算的例子。现实中模板元编程很少用来做数值计算，更多被用来做类型计算和代码生成，书中却涉及甚少。

- 《Modern C\++ Design》
	介绍如何使用模板进行C\++高阶设计的一本书。介绍了`TypeLists`的概念，作为一种重要的编译时数据结构，是元编程的基础。但遗憾作者并没有显示的提出元编程的概念，也没有对C\++编译时运算特征进行总结和提炼。最后由于此书基于的C\++ 98标准对于模板以及编译期类型计算支持上的欠缺，书中介绍的不少实现比较迂回复杂。

- 《C\++模板元编程》
	正式介绍C\++模板元编程的一本书，引入了元函数的概念，对基于模板的函数式计算进行了规范化，发挥了编译期元函数可组合的优势。遗憾的是，此书只能算是boost中模板元编程库（mpl）的用户手册，基本上是在讲mpl库的用户接口和使用方法，没有涉及库的实现细节。现实中我们采用元编程解决问题，一般不会引用boost这么重的库，往往只会在某一局部借鉴类似的设计技巧。所以对于元编程来说，授之以渔的意义远大于授之以鱼。另外由于boost mpl库中用了大量C\++预处理期代码生成技术，导致想通过看mpl的源码掌握模板元编程的人基本是会陷入到一堆宏中，对于学习元编程增加了非常多的干扰因素。

基于以上原因，我使用C\++11实现了一个C\++模板元编程的库：[TLP ](https://github.com/MagicBowen/tlp)[(https://github.com/MagicBowen/tlp)]()，然后再通过本文这一系列文章结合TLP库中的代码示例来为大家介绍C\++模板元编程的各方面知识。

TLP库包含以下内容：
- 基本的编译期数据类型IntType、BoolType以及基于其的运算函数；
- 基本的编译期数据结构TypeList，以及对于它的基本算法append、erase、replace、sort...
- 基于TypeList的高阶函数，如 any，all，map，filter，fold...
- 帮助进行模板元编程的一些辅助函数，如 IsEqual，IfThenElse，Print...
- 一个面向模板元编程的测试框架，所有的测试用例执行在C\++的编译期，我们使用它来对TLP进行测试；

除此之外，TLP库中还包含了两个介绍如何在现实中使用TLP库的示例代码，分别是：
- 示范了如何使用模板元编程技术来实现代码生成，自动创建visitor设计模式；
- 示范了如何使用模板元编程技术来实现一个DSL，用于描述并生成有限状态机；

上面提到的TypeList以及使用代码生成来创建visitor设计模式的原创者是《Modern C\++ Design》的作者Andrei Alexandrescu。在TLP中我用C\++11对TypeList及其算法进行了改写，并进行了高阶函数的扩展。得益于C\++11标准对模板元编程的更好支持，新的实现比起原来的更加清晰和简洁。

示例代码中利用模板元编程创建有限状态机DSL的例子来自于《C++模板元编程》一书，为了更好的展示其实现，我用TypeList对其进行了改写。

最后，TLP库自身的测试通过一个原创的C\++模板元编程测试框架。该框架专门针对C\++编译期计算进行测试，它的用法和常见的xUnit测试框架类似，但有趣的是使用该框架所描述的所有测试用例的执行发生在C\++编译期。后面会专门介绍该框架的一些实现细节。

C\++模板元编程当年被提出来的时候，函数式编程还没有像今天这样被更多的人所了解和接受，当时的C\++标准和编译器对模板和编译期计算的支持也非常有限。然而到了今天，很多事情发生了变化！本文的读者最好能够有一些函数式编程的基础，了解C\++模板的基本用法，熟悉一些C\++11标准的内容。当然文中所有用的到模板技术、C\++11标准和涉及到的函数式编程概念也都会专门介绍和说明。

如果你从来没有接触过C\++模板元编程，那么最好从一开始就把它当做一门全新的语言去学习，从头掌握C\++中这种新的计算模型和语法。这种新的语言和我们熟识的运行期C\++的语法和计算模型有很大的差异，但它的优势在于能和运行期C\++紧密无缝地结合在一起，无论是在提高程序可扩展性还是提高程序运行效率上，都能创造出非常不可思议的效果来。希望通过这一系列文章，可以让更多的人掌握C\++模板元编程这一设计利器，在适合的场合下以更酷、更有效的方式去解决问题。

## 模板的基本知识

模板最开始作为一种更加安全的宏被引入C\++，用来解决代码在不同类型间复用的问题。
下面我们以类模板举例，介绍一些我们后面会用到的模板基本概念。

### 类型参数

~~~cpp
#include <vector>
#include <stdexcept>

template<typename T>
struct Stack
{
    void push(const T& elem)
    {
        elems.push_back(elem);
    }

    T pop()
    {
        if(empty()) throw std::out_of_range("Stack<>::pop: empty!");

        auto elem = elems.back();
        elems.pop_back();
        return elem;
    }

    bool empty() const
    {
        return elems.empty();
    }

private:
    std::vector<T> elems;
};
~~~

上面我们用模板类实现了一个简单的容器栈，它可以支持不同的类型做元素。如下：

~~~cpp
Stack<int> intStack;
intStack.push(-1);
intStack.push(2);
intStack.push(-3);
std::cout << intStack.pop() << std::endl;

Stack<char> charStack;
charStack.push('A');
charStack.push('B');
std::cout << charStack.pop() << std::endl;
~~~

可以将类模板想象成一个编译期的函数，不同的是它的参数列表放在一对尖括号中。通过`template<typename T> struct Stack`我们声明了一个编译期的函数，它的名字叫做Stack，它有一个类型形参T。

标准规定可以用typename或者class关键字指示模板形参是一个类型，不能使用struct。由于模板的类型形参不仅可以被替换为用户自定义类型，也可以被替换为内置类型（int, char, double...），所以使用typename语义上比class更清晰一些。本文统一使用typename。

如同把具体的实参传递给一个函数，函数就会计算求值一样，当我们把具体的类型当做实参传递给类模板时，类模板会在编译期进行计算，返回一个具体的类型。类模板的传参和函数类似，只不过语法上使用尖括号。

上例中我们分别将int和char当做实参，传递给类模板Stack。Stack得到实参后变成具体的类型`Stack<int>`和`Stack<char>`。根据运行期C\++的要求，只有具体类型才能产生对象，所以我们分别用`Stack<int>`和`Stack<char>`生成了两个对象`intStack`和`charStack`。

类模板的实现中可以继续使用类模板。上例中Stack的实现中使用了标准库中的类模板`std::vector`。一旦我们在Stack中用具体类型替换形参T，`std::vector<T>`也会被传递参数从而变成一个具体类型，使得可以产生`elems`对象。

上面虽然我们用编译期函数来类比类模板，但是这时的类模板还远未达到模板元编程的要求，我们继续！

### 默认模板参数

上面例子中，栈的实现使用了std::vector。为了让栈的实现更加灵活，我们将实现栈的容器也作为模板的参数之一。

~~~cpp
template<typename T, typename Container = std::vector<T>>
struct Stack
{
    void push(const T& elem)
    {
        elems.push_back(elem);
    }

    T pop()
    {
        if(empty()) throw std::out_of_range("Stack<>::pop: empty!");

        auto elem = elems.back();
        elems.pop_back();
        return elem;
    }

    bool empty() const
    {
        return elems.empty();
    }

private:
    Container elems;
};
~~~

如上我们为类模板增加了一个类型参数`Container`。和函数类似，模板也支持声明默认参数，这里我们将Container默认设值为`std::vector<T>`。由于在模板的形参声明过程中，后面的声明可以使用前面出现过的形参，我们在`typename Container = std::vector<T>`中使用了T，因此这里`std::vector<T>`仍旧是一个类型。

现在我们还可以像之前一样使用该类模板，当使用`Stack<int>`定义`intStack`时Container使用默认的`std::vector<T>`。同时我们可以显示指定Container为别的容器类，例如`Stack<int, std::deque<int>> intStack;`。

每个用于替换模板形参Container的具体类型，必须满足Stack使用Container时的隐式约束。例如上例中Stack使用了Container的无参构造函数，调用了Container的`push_back`，`back`，`pop_back`，`empty`接口，并且对每个接口的参数和返回值都有一定预期。上面使用的`std::vector<T>`和`std::deque<T>`都满足如上约束。一旦不满足，会出现编译错误。

目前C\++中，模板这种对参数特征的约束只能通过参数被使用的情况隐式推断出来，后续的标准后可能会引进concept的概念对其显示化。

### 模板的模板参数

上例中由于Stack类模板的声明中第二个参数是一个类型（`typename Container`），所以我们通过`Stack<int, std::deque<int>>`定义一个具体的栈类型时，第二个参数传递`std::deque<int>`，而不能是`std::deque`。上述定义中我们一共把int写了两遍，而这种重复是一种必然的重复。

为了避免上述重复，我们可以让Stack的第二个参数直接是一个模板，而不再是一个具体类型。

~~~cpp
template<typename T,
         template<typename> class Container = std::vector>
struct Stack
{
    void push(const T& elem)
    {
        elems.push_back(elem);
    }

    T pop()
    {
        if(empty()) throw std::out_of_range("Stack<>::pop: empty!");

        auto elem = elems.back();
        elems.pop_back();
        return elem;
    }

    bool empty() const
    {
        return elems.empty();
    }

private:
    Container<T> elems;
};
~~~

如上Stack类模板的第二个参数变为`template<typename> class Container`，它的名字仍旧是Container，但是类型变为一个模板，这个模板具有一个类型参数。由于Container自身的模板形参名字没有被使用，所以我们可以省略。按照标准这里声明Container前的关键字只能是class，不能是typename。最后，模板的模板参数也可以有默认值，这里我们设置为`std::vector`。

有了上面的定义，我们期望可以这样使用Stack：`Stack<int, std::deque> intStack`，但编译器却给了我们一个教训。

std::deque类模板在stl库中的定义有两个类型参数，第一个参数是元素类型，第二个参数是分配器allocator的类型。虽然std::deque的第二个类型参数有默认值，但是当编译器使用std::deque替换Container时却会严格匹配参数，默认值被忽略了。

我们修改Stack的定义如下：

~~~cpp
template<typename T,
         template<typename Elem, typename Allocator = std::allocator<Elem>> class Container = std::vector>
struct Stack
{
    void push(const T& elem)
    {
        elems.push_back(elem);
    }

    T pop()
    {
        if(empty()) throw std::out_of_range("Stack<>::pop: empty!");

        auto elem = elems.back();
        elems.pop_back();
        return elem;
    }

    bool empty() const
    {
        return elems.empty();
    }

private:
    Container<T> elems;
};
~~~

现在`Stack<int, std::deque> intStack`可以编译通过了！

可以看到模板的模板参数特性，可以让类模板之间通过模板参数互相组合。如果我们将类模板比作C\++编译期的函数，那么可以接受模板作为参数的类模板，就相当于一个函数的入参仍旧可以是函数，这是后面我们会介绍到的高阶函数的概念。

### 模板特化

前面定义的Stack中，第二个模板参数要求支持`back`，`push_back`，`pop_back`等接口。如果我们已经有一个自定义的容器`Array`，它的定义如下：

~~~cpp
template<typename T, typename Allocator = std::allocator<T>>
struct Array
{
    void put(size_t index, const T& t)；
    T get(size_t index)；
    ...
};
~~~

Array只有put和get接口，并辅助以index参数进行元素存取。为了让Array也能参与实现Stack，我们可以对Stack进行特化，当Stack的第二个参数是Array时重新定义Stack的实现：

~~~cpp
template<typename T>
struct Stack<T, Array>
{
    Stack() : size(0)
    {
    }

    void push(const T& elem)
    {
        elems.put(size++, elem);
    }

    T pop()
    {
        if(empty()) throw std::out_of_range("Stack<>::pop: empty!");
        return elems.get(--size);
    }

    bool empty() const
    {
        return size == 0;
    }

private:
    size_t size;
    Array<T> elems;
};
~~~

在Stack特化版本的声明`template<typename T> struct Stack<T, Array>`中，Stack名字后面的尖括号中`Stack<T, Array>`传递的参数可以是具体类型，也可以不是具体类型，但是至少要比Stack主模板（非特化版本）的参数更加特殊一些，而且和主模板的参数声明顺序和约束必须一致。

如果特化版本中，所有的模板参数都被替换成了具体类型，那么就叫做**全特化**，例如：

~~~cpp
template<> 
struct Stack<int*, Array>
{
	...
};
~~~

如果参数中还有非具体类型，那么就叫做**部分特化**或者**偏特化**，例如：

~~~cpp
template<typename T>
struct Stack<T, Array>
{
	...
}；
~~~

无论是全特化还是偏特化，特化版本的声明仍然需要使用关键字template，后面紧跟的尖括号中声明特化版本中还在使用的非具体类型形参。由于全特化不再存在非具体类型，所以尖括号中为空，但是不能省略，皆以`template <>`开头。

注意，主模板的template关键字后面定义了该模板的基本原型特征，特化模板的**模板名称关键字后面的尖括号**中的模板参数必须和**主模板template关键字后面尖括号**中的参数顺序和约束一致。上例中由于主模板声明第一个模板参数是类型，第二个模板参数是模板，所以特化版本`Stack<T, Array>`尖括号中的参数不能多也不能少，且顺序不能颠倒，而且第二个参数模板Array的定义必须和主模板中对Container的模板约束一致。

特化版本的template后面紧跟的尖括号中仅是声明特化版本中还在使用的非具体类型参数，和主模板template后面紧跟的尖括号中的参数没有任何关系。

上例中，我们修改了`Stack<T, Array>`中`push`、`pop`、`empty`成员方法的实现，并且增加了`size`数据成员。我们甚至还可以修改`Stack<T, Array>`中的接口名称，不再叫push和pop，或者删掉empty的实现，只要`Stack<T, Array>`的客户正确地使用该特化版本的接口即可。可见对于模板的特化，只需要其签名（模板名和模板参数）和主模板保持一致，而对于其实现，和主模板以及其它特化版本的实现没有任何关系，完全可以根据该特化版本的需要进行定制。

当我们给一个模板传递参数后，编译器会从主模板和所有的特化版本的实现中进行选择，简单来说选择的规则和函数重载的选择顺序类似，就是选择最多匹配的那个版本。

如上例中如论是`Stack<int, Array>`还是`Stack<double, Array>`都会匹配`template<typename T> struct Stack<T, Array>`版本的实现，而`Stack<int, std::list>`则会匹配主模板的实现。

关于特化最后再提一个我们后面会用到的知识点，那就是模板可以被嵌套地定义在一个类中或模板中，但是模板的特化不可以。

### 模板的非类型参数

前面的例子中，我们分别使用了类型和模板作为类模板的参数。除此之外，模板还支持其它非类型模板参数。

如下用数组实现Stack模板，第二个模板参数是一个int型常量，用于定义数组的最大长度。

~~~cpp
template<typename T, int MAX_SIZE>
struct Stack
{
	void push(const T&);
    T pop();
    
private:
	T elems[MAX_SIZE];
    int size;
};
~~~

一般来说，模板的非类型参数只能是整型常量（包括enum），或者指向外部链接的指针（包括函数指针，类的成员函数指针）。到目前为止还不支持浮点数，对于字符串常量也不支持，但是可以支持具有外部链接的字符串常量指针。

例如对于下面的模板定义：

~~~cpp
template<const char* MyName>
struct Token
{
    std::string name{MyName};
};
~~~

下面的用法都产生编译错误：

~~~cpp
	Token<“Hello”> tocken；
~~~

~~~cpp
    const char* str = "Hello";
    Token<str> tocken;
~~~

而如下是可以正确编译通过的：

~~~cpp
extern const char str[] = "Hello";

Token<str> token;
std::cout << tocken.name << std::endl;
~~~

总结一下，模板的参数支持以下类型：

- 类型参数；
	使用typename或者class指示。

- 非类型参数；
	整型常量（包括enum），或者指向外部链接的指针（包括函数指针、类的成员函数指针，以及具有外部链接的字符串常量指针）。

- 模板参数；
	使用`template<...> class XXX`的形式指示。

### 模板的编译期计算

和函数求值类似，当模板的形参被实参替换时，模板会进行编译期计算。由于模板的参数支持类型参数和非类型参数，所以模板在编译期可以进行两类计算：类型计算和数值计算。

#### 数值计算

模板的数值计算发生在编译期，计算的参数一般由模板参数输入，计算的结果由模板内部的enum定义或者static const的整形成员保存。

如下我们实现编译期的整数加法：

~~~cpp
template<int X, int Y>
struct Plus
{
    enum { Value = X + Y };
};
~~~

如下我们使用这个类模板进行加法运算：

~~~cpp
int main()
{
	std::cout << Plus<3, 4>::Value << std::endl;
    return 0;
}
~~~

上面代码会打印出7。注意这里对7的计算发生在编译期，当我们在main函数中打印的时候结果其实已经是计算好了的。

为了验证我们的说法，我们想办法让结果在C\++的编译过程中就打印出来。

~~~cpp
template<int Value>
struct Print
{
    operator char()
    {
        return Value + 0xFF; // INVOKE OVERFLOW WARNNING LOG !
    }
};

#define __print(token, ...) char print_value_##tocken = Print<__VA_ARGS__>()
~~~

由于C\++的编译期计算无法直接操作IO，我们只能想办法通过C\++的编译器将计算结果在编译信息中打印出来。如上`__print`宏定义中将一个`Print<Value>`的对象赋值给一个临时的char变量，从而导致调用Print中定义的char类型隐式转换函数`operator char()`。该隐式转换函数中将Value和0xFF进行相加，这将会导致编译器会产生一个char类型值溢出告警，从而将Value的值打印出来。

我们这时可以删除main函数，然后在任一cpp文件中包含上述Plus和Print模板的头文件，然后写下如下语句

~~~cpp
// TestPrint.cpp
// should include the header files of Plus and Print
__print(Plus_3_4, Plus<3, 4>::Value);
~~~

在gcc4.8.4上，编译器编译到该文件时打印如下：

~~~bash
TestPrint.cpp: In instantiation of 'Print<Value>::operator char()[with int value = 7]'：
TestPrint.cpp: required form here
TestPrint.cpp: warning: overflow in implicit constant conversion [-Woverflow]
~~~

可以看到计算结果是在编译告警`Print<Value>::operator char()[with int value = 7]`中打印出来的。

由于一个文件中`__print`可能会被使用多次，所以它的第一个参数token是为了让每个临时的char变量的名字不重复。我们可以优化`__print`的定义，避免让用户传递一个token，而让编译器帮我们产生一个不会重复的名字。如下：

~~~cpp
#define __print(...) char UNIQUE_NAME(print_value_) = Print<__VA_ARGS__>()
~~~

我们使用了`UNIQUE_NAME`宏来为临时的char变量产生不重复的名字，`UNIQUE_NAME`的定义如下。这里使用了一个小技巧，将当前行号拼接到一个固定的token中产生了一个不重复的名字。

~~~cpp
#define __DO_JOIN(symbol1, symbol2) symbol1##symbol2
#define _JOIN(symbol1, symbol2) __DO_JOIN(symbol1, symbol2)

# define UNIQUE_NAME(prefix) _JOIN(prefix, __LINE__)
~~~

现在我们可以这样使用`__print`了：`__print(Plus<3, 4>::Value);`。

对于类模板Plus我们可以这样理解：它就如同一个函数，`Plus`是函数名，它声明需要两个int型的入参，分别是形参`X`和`Y`。它的返回值是内部定义的`Value`。对它的调用方式是`Plus<3, 4>::Value`，尖括号中传递实参，通过调用`Value`获得计算结果。只不过这个函数的计算发生在C\++编译期，为了和运行期函数进行区分，编译期的函数都用尖括号而非圆括号。

C\++这种编译期的函数其实是支持多返回值的，例如我们修改上例的代码，一次计算出整数加减乘除的所有结果。

~~~cpp
template<int X, int Y>
struct Caculate
{
    enum
    {
        Sum = X + Y,
        Dec = X - Y,
        Mul = X * Y,
        Div = X / Y
    };
};
~~~

可以使用`Caculate<10, 2>::Sum`，`Caculate<10, 2>::Dec`，`Caculate<10, 2>::Mul`，`Caculate<10, 2>::Div`分别获得10和2的加减乘除的结果。

这种多返回值计算在我们后续介绍元编程时使用的并不多。原因之一是当我们只想要其中一个计算结果时，所有的结果其实是一起被计算了，会存在额外的计算开销。另外一个重要的原因是，多个返回值必须每个的名字都不一样，这样就对我们后续介绍编译期的函数组合能力造成障碍。

除了用enum保存编译期的数值计算结果，还可以用 static const成员变量。上面例子修改如下效果一样。

~~~cpp
template<int X, int Y>
struct Plus
{
    static const int Value = X + Y;
};
~~~

由于有些编译器对static const在模板的计算中存在问题，需要为其分配内存，所以本文对于编译期数值计算结果的保存一律使用enum。

#### 类型计算

除了可以计算数值，编译期更具有价值的是类型计算。我们可以将编译期常量和类型都看做是编译期的可计算对象。

我们知道模板的所有形参被实参替换后，模板自身就具现化为一个具体的类型了。但是模板自身具现化的这个类型对于我们想要的编译期类型计算来说缺少抽象能力。模板的类型计算结果一般保存在模板内部定义的嵌套类型中。

模板内部定义类型的方法除了可以直接在模板内部定义嵌套类，更多的是使用typedef。

如下我们定义了一个类模板，它的入参是类型T，内部通过Type定义了T的指针类型`T*`。

~~~cpp
template<typename T>
struct PointerOf
{
    typedef T* Type;
};
~~~

我们可以像下面这样使用该模板：

~~~cpp
PointerOf<const char>::Type s = "Hello world!";
std::cout << s << std::endl;
~~~

如同前面数值计算一样，我们可以这样理解`PointerOf`：`PointerOf`是一个编译期的函数，它使用`<typename T>`声明了它有一个类型形参T。我们通过访问`Type`可以获得该函数的返回值，也是一个类型。这个函数负责在C\++编译期将一个输入类型转变为它对应的指针类型。所以调用`PointerOf<const char>::Type`其实是和`const char *`本质上一样。

我们定义的这个`PointerOf`似乎有些无聊，但这却是类型计算的基础。后面当我们把这种类型计算的小函数组合起来，会逐渐看到它们的威力。

最后，C\++11标准使用using关键字来专门定义类型别名，它的用法和定义变量的习惯类似，且后面会看到功能也比typedef强大得多，所以我们后续类型计算统一用using关键字定义类型别名。`PointerOf`的定义修改如下：

~~~cpp
template<typename T>
struct PointerOf
{
	using Type = T*;
};
~~~

### 模板递归

模板可以被递归调用，在模板递归的过程中，可以执行前面我们提到的两种编译期计算：数值计算和类型计算。

下面我们用模板递归来做数值计算，在编译期计算N的阶乘。

~~~cpp
template<int N>
struct Factorial
{
    enum { Value = N * Factorial<N - 1>::Value };
};

template<>
struct Factorial<1>
{
    enum { Value = 1 };
};

~~~

可以看到，我们在主模板`template<int N> struct Factorial`的定义中，使用了模板自身`Factorial<N - 1>::Value`。编译器会一直用不同的`N - 1`的值来具现化主模板，一直到N变为1，这时选择Factorial的特化版本`template<> struct Factorial<1>`，内部的Value变为1，递归终止了。

我们可以在编译期运行这个函数`__print(Factorial<5>::Value)`，可以看到编译器会打印出120。

对于上面的例子，我们看到是通过模板特化来终止递归的。事实上我们对比一下Haskell语言中计算阶乘的函数实现：

~~~haskell
factorial :: Int -> Int
factorial n = n * factorial (n - 1)
factorial 1 = 1
~~~

Haskell是一门纯函数式语言，它通过模式匹配还进行条件选择，通过递归来进行循环控制。对于上面的factorial定义，当入参是1的时候模式匹配会选择到`factorial 1 = 1`实现，否则匹配到`factorial n = n * factorial (n - 1)`的递归实现。

可以看到上面我们使用C\++中模板的方式和Haskell中定义函数是如此的类似。编译器对模板的特化版本选择就相当是Haskell在做模式匹配，而两者的循环控制都是通过递归来完成。已经证明模板的这种编译时计算能力就是一种纯函数式编程范式，是图灵完备的！

不同的是，C\++这种编译时计算支持的计算对象主要是整形和类型。

C\++这种编译期函数式计算就是本文要介绍的C\++模板元编程，类模板在里面充当了函数的角色。本文后面用到关于类模板的知识基本就是前文所述这些。后面我们将会对类模板进行规范化，让其能够和函数式计算更加地一致，最大程度发挥编译期函数式计算的威力。

## C\++模板元编程

### 元函数

我们通过继续演进前面那个无聊的类型计算的例子，来得出元函数的定义。

前面我们实现了PointerOf，它对于传进的任意类型T可以计算出T的指针类型。

~~~cpp
template<typename T>
struct PointerOf
{
	using Result = T*;
};
~~~

现在我们想要实现一个能够计算T的指针的指针类型的模板，怎么做？

一种做法是直接定义一个新的模板：

~~~cpp
template<typename T>
struct Pointer2Of
{
	using Result = T**;
};
~~~

为了让类型计算结果更像是出自函数的返回值，我们将计算结果的类型别名后续统一叫做`Result`。上述类模板本质上是一个对类型进行计算的函数:

> `Pointer2Of :: (typename T) => T -> T**`

可以这样使用该函数：

~~~cpp
int* pi;
Pointer2Of<int>::Result ppi = &pi;
~~~

上述代码中`Pointer2Of<int>::Result`计算发生在编译期，当在C\++运行期它已经得到计算结果`int**`了。所以上述代码在编译期计算完成后，和如下代码本质上相同：

~~~cpp
int* pi;
int** ppi = &pi;
~~~

虽然我们把类模板当做编译期函数来看，但是这种函数语法看起来和我们熟悉的函数相差较大，但究其本质和函数调用并无差异，都是为函数传入符合要求的实参，获得函数返回结果。

我们可以认为由于圆括号已经优先给了运行时C\++函数，所以这种编译期C\++函数的定义和调用都使用尖括号。并且需要显示调用Result才对函数进行运算求值。当使用这种编译期函数但并不调用Result时，可以将其类比为在运行期C\++中使用一个函数指针，仅做传递用，但并不求值。

编译期函数计算，可以调用已有的其它编译期函数。如下通过嵌套调用PointerOf，也可以实现Pointer2Of：

~~~cpp
template<typename T>
struct Pointer2Of
{
	using Result = typename PointerOf<typename PointerOf<T>::Result>::Result;
};
~~~

上面我们通过嵌套调用两次PointerOf来完成Pointer2Of的实现。在Pointer2Of中我们每次使用`PointerOf<...>::Result`时前面都用了typename关键字。原因是C\++标准要求一旦PointerOf后面的尖括号中存在非具体类型的话，那么使用`::`访问PointerOf的内部类型Result时必须使用typename显示指明`PointerOf<...>::Result`是一个类型。所以我们在Pointer2Of中使用PointerOf完整的方式是这样的：`typename PointerOf<...>::Result`。

和Haskell相比，我们必须得承认C\++的这种函数式编程的书写确实太繁琐了。为了简化对元函数的使用，我们可以用宏封装一下PointerOf：

~~~cpp
#define __pointer(...) typename PointerOf<__VA_ARGS__>::Result
~~~

这样Pointer2Of的定义可以简化如下：

~~~cpp
template<typename T>
struct Pointer2Of
{
	using Result = __pointer(__pointer(T));
};
~~~

这样看起来好看多了，`__pointer(T)`的写法更像是在调用一个函数。

现在看到我们对类模板进行约束，固定用Result保存计算结果，且只返回单一结果，可以使我们将模板当做函数使用时的写法得到统一，这对于我们进行函数组合简直是必须的。

后续我们将一直把这种在编译期进行计算，靠Result返回计算结果的类模板看作是编译期的函数，它的目的是为了支持C\++模板元编程。为了和C\++运行时函数进行区分，后文中我们统一将其称作**元函数**。

如同函数是函数式编程的构成基础一样，元函数是C\++模板元编程的构成基础。

### 高阶函数

接着上面的例子，此刻我们想要定义指向指针的指针的指针的指针类型，怎么办？或者说我们想要一种能够任意指定指针层数的元函数。

我们手里已经有了一个PointerOf元函数，我们需要一个能够将其对一个指定类型反复施展指定次数的元函数。

下面我们实现了一个通用的Times元函数，它可以对一个指定类型T反复调用另一个元函数N次。

~~~cpp
template<int N, typename T, template<typename> class Func>
struct Times
{
    using Result = typename Func<typename Times<N - 1, T, Func>::Result>::Result;
};

template<typename T, template<typename> class Func>
struct Times<1, T, Func>
{
    using Result = typename Func<T>::Result;
};
~~~

上面的代码中，Times有三个参数，第一个参数是次数N，第二个参数是类型T，第三个参数是可以接受一个类型参数的元函数Func。Times采用了递归实现，当N为1时，Result就是元函数Func的结果，否则就递归调用`Func<typename Times<N - 1, T, Func>::Result>::Result`。

最终我们通过两个元函数的组合，实现了通过编译期计算获得四层指针的类型，如下：

~~~cpp
int*** pppi;
Times<4, int, PointerOf>::Result ppppi = &pppi;
~~~

上面的Times元函数是一个可以接收一个元函数做参数的元函数，在函数式编程里面这称作**高阶函数**。高阶函数可以让代码在更高的抽象层次上进行组合复用。

比如我们同样可以可以将Pointer2Of和Times组合起来，实现四重指针类型计算：

~~~cpp
int*** pppi;
Times<2, int, Pointer2Of>::Result ppppi = &pppi;
~~~

事实上有了Times元函数，我们可以轻易得到任意层数的指针类型。

~~~cpp
using Pointer3OfInt = typename Times<3, int, PointerOf>::Result;

int** ppi;
Pointer3OfInt pppi = &ppi;
~~~

### 柯理函数

现在，我们想实现一个元函数，可以固定返回char类型的指定层数的指针类型。

~~~cpp
template<int N>
struct CharPointer
{
	using Result = typename Times<N, char, PointerOf>::Result;
};
~~~

如上，我们定义了元函数CharPointer，它是一个int型单参元函数。它的实现调用了Times，将其第二和第三个参数分别固定位char和PointerOf。

借助于继承的特性，上面的代码可以简化为：

~~~cpp
template<int N>
struct CharPointer ：Times<N, char, PointerOf>
{
};
~~~

上面这种定义元函数的方式叫做**元函数转发**。

如果借助using关键字，可以实现得更加简单：

~~~cpp
template<int N> using CharPointer = Times<N, char, PointerOf>;
~~~

这里我们直接对Times绑定第二和第三个参数后为其起了别名CharPointer。

在函数式编程里面，有个概念叫做函数柯里化(currying)。是指一个函数接收部分参数后，并不立即求值，而是继续返回另一个函数。

如下Haskell代码定义了一个三数相乘的函数multiThree，它接收三个Int型参数返回它们的乘积：

~~~haskell
multiThree :: Int -> Int -> Int -> Int
multiThree x y z = x * y * z
~~~

当我们将multiThree其中一个参数固定后，它就变成了一个二参函数。

~~~bash
ghci > let multiTwoWithNine = multiThree 9
ghci > multiTwoWithNine 2 3
~~~

我们使用using关键字实现元函数转发，可以达到类似函数柯里化的效果。这对于我们最大化的复用函数有很多好处。

> 函数柯里化在函数式编程语言里的意义非常重要，和C\++模板元编程里面的其实还是有区别的。例如在Haskell中，可以不用为柯里化函数定义别名，就直接将其作为另一个函数的参数传递，而在C\++模板元编程里目前还做不到。

现在借助柯里化，我们重新实现Pointer2Of如下：

~~~cpp
template<typename T> using Pointer2Of = Times<2, T, PointerOf>;
~~~

可以看到，所谓的Pointer2Of，其实就是把Times的第一个和第三个参数固定后，得到的单参柯里化函数。

### 一切都是类型

下面我们实现一个在编译期判断两个类型是否相等的元函数：

~~~cpp
template<typename T, typename U>
struct IsEqual
{
    enum {Result = false};
};

template<typename T>
struct IsEqual<T, T>
{
    enum {Result = true};
};
~~~

上面的实现中使用了模式匹配，当两个类型相等时，选择下面的特化版本，否则选择非特化版本。

接下来我们实现一个在编译期判断两个整数是否相等的元函数：

~~~cpp
template<int N, int M>
struct IsNumEqual
{
    enum {Result = false};
};

template<int N>
struct IsNumEqual<N, N>
{
    enum {Result = true};
};
~~~

我们看到，判断整数是否相等的元函数的实现和前面对类型进行判断的元函数实现完全一样，唯独入参类型不同，但却必须为这两个元函数起不同的函数名称。

另外，前面我们用Result表示返回类型，这里又用它返回数值。这种返回类型上的差异，会让我们在函数组合的时候碰到不少问题。

如果我们能有一个方法，让所有的元函数的入参类型和返回值类型都能一致化，那将对元函数的复用和组合带来极大的好处。

有一个办法可以让我们把数值也变成一个类型。

~~~cpp
template<int V>
struct IntType
{
    enum { Value = V };
    using Result = IntType<V>;
};
~~~

有了IntType，那么`IntType<3>`，`IntType<4>`就是不同的类型了。可以使用`IntType<3>::Value`获得它的数值，但是一般情况下，在元编程中我们只使用它的类型。

同理，对于bool值，也可以如此封装：

~~~cpp
template<bool V> struct BoolType;

template<>
struct BoolType<true>
{
    enum { Value = true };
    using Result = BoolType<true>;
};

template<>
struct BoolType<false>
{
    enum { Value = false };
    using Result = BoolType<false>;
};

using TrueType = BoolType<true>;
using FalseType = BoolType<false>;
~~~

这样，后续所有的元函数的入参和返回值就都只有类型，再没有数值。如此归一化后，将会避免很多重复，也会让元函数的组合能力威力大增。

最后IsEqual只有一份统一的实现：

~~~cpp
template<typename T, typename U>
struct IsEqual
{
    using Result = FalseType;
};

template<typename T>
struct IsEqual<T, T>
{
    using Result = TrueType;
};
~~~

### 一切都是函数




### 不可变性


### 模式匹配和递归

### 总结：不同阶段的C\++

编译期C\++可以看做是一门解释型语言，这时编译期充当着解释器，直接针对C\++源码进行计算。我们知道代码的元信息最全的地方就在于源码中，所以解释性语言往往拥有比较强大的反射能力。同样编译期C\++也具有非常强大的反射能力，这就是C\++ traits技术的力量来源。正式这种编译期反射的能力，是的基于类型计算的模板技术，是C\++构建框架和库的必备武器。

反射能力的来源

## 测试

## 基本构建

## TypeList

## 和运行期结合

### traits

### policy

### 类型推断

## 应用

### 内存分配自动分派

### Dates：类型判断

### Visitor

### FSM DSL

## 总结


