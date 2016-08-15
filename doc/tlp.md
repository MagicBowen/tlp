# TLP: learning template meta programming by C++11

## Foreword

熟悉C\++的程序员都知道，C\++是一门多范式编程语言，支持面向过程、面向对象、泛型编程以及函数式编程范式。然而提到C\++模板元编程，在很多人心里这却似乎是C\++里的一种黑魔法：它很难学习，一旦进入这个领域曾经那些熟悉的东西（if，for...）都不再灵验；它很强大，但现实中却鲜见有人用它来解决实际问题，除过偶尔在一些编码练习中被某些C\++狂热粉作为奇淫巧技拿出来秀肌肉。

其实模板元编程是C\++所支持的一种非常强大的计算能力，它是使用C\++开发高质量库和框架所离不开的一项武器。

掌握C\++模板元编程，可以帮助你做到：

- 实现高扩展性，并且兼具高性能的库
- 实现更加灵活且易于使用的框架
- 实现基于C\++的内部DSL（Domain Special Language）
- 帮助更好地理解并使用模板和泛型编程，更深入地使用C\++ STL库的一些高级特性

如果你是一个C\++的库或框架的开发者，了解和掌握一些模板元编程的知识，可能会让你的作品更易于扩展、拥有更易用的接口，甚至更高的运行时效率。而即使你只使用C\++设计和开发应用程序，了解模板元编程也会帮助你更好的去使用STL库的各种特性，甚至帮助你的局部设计做的更加漂亮。

实际上C\++模板元编程技术已经渗透在我们日常使用的各种库和框架中，例如STL库以及各种xUnit测试框架和mock框架。可以说，模板元编程是中级C\++程序员迈向高级的必经之路！

然而现实中，C\++模板元编程的学习之旅却并不平坦。

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

C\++模板元编程当年被提出来的时候，函数式编程还没有像今天这样被更多的人所了解和接受，当时的C\++标准和编译器对模板和编译期类型计算的支持也非常有限。然而到了今天，很多事情发生了变化！本文希望读者最好能够有一些函数式编程的基础，了解C\++模板的基本用法，熟悉一些C\++11标准的内容。当然文中所有用的到模板技术、C\++11标准和涉及到的函数式编程概念也都会专门介绍和说明。希望通过这一系列文章，可以让更多的人掌握C\++模板元编程这一设计利器，在适合的场合下以更酷、更有效的方式去解决问题。

## Basic Concepts

### 模板的基本知识

模板最开始被作为一种更加安全的宏而引入C\++，用来解决代码在不同类型间复用的问题。
下面我们以类模板举例，介绍一些我们后面会用到的模板基本概念。

#### 类型参数

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

如同把具体的实参传递给一个函数，函数就会计算求值一样，当我们把具体的类型当做实参传递给类模板时，类模板会在编译期进行计算，返回一个具体的类型。类模板的传参和函数类似，只不过仍旧使用尖括号。

如上例中我们分别将int和char当做实参，传递给类模板Stack。Stack得到实参后变成具体的类型`Stack<int>`和`Stack<char>`。根据运行期C\++的要求，只有具体类型才能产生对象，所以我们分别用`Stack<int>`和`Stack<char>`生成了两个对象`intStack`和`charStack`。

类模板中可以再嵌套使用类模板。上例中Stack的实现中使用了标准库中的类模板`std::vector`，一旦我们用具体类型替换形参T传递给Stack，那么`std::vector<T>`也会被传递参数从而变成一个具体类型，使得可以产生`elems`对象。

上面我们虽然用编译期函数来类比类模板，但是这时的类模板还远未达到模板元编程的要求，我们继续！

#### 默认模板参数

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

现在我们还可以像之前一样使用该类模板，例如仍然可以使用`Stack<int>`定义`intStack`，这时Container使用默认的`std::vector<T>`。同时我们可以显示指定Container为别的容器类，例如`Stack<int, std::deque<int>> intStack;`。

每个用于替换模板形参Container的具体类型，必须满足Stack使用Container时的隐式约束。例如上例中Stack使用了Container的无参构造函数，调用了Container的`push_back`，`back`，`pop_back`，`empty`接口，并且对每个接口的参数和返回值都有一定预期。上面使用的`std::vector<T>`和`std::deque<T>`都满足如上约束。一旦不满足，会出现编译错误。

模板这种对参数特征的约束，目前在C\++中只能通过参数被使用的情况隐式推断出来，后续的标准后可能会引进concept对其显示化。

#### 模板的模板参数

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

如上Stack类模板的第二个参数变为`template<typename> class Container`，它的名字仍旧是Container，但是类型是一个有具有一个类型参数的模板。由于Container自己中的那个模板形参名字没有被使用，所以我们可以省略。按照标准这里声明Container前的关键字只能是class，不能是typename。最后，模板的模板参数也可以有默认值，这里我们设置为`std::vector`。

有了上面的定义，我们期望可以这样使用Stack：`Stack<int, std::deque> intStack`，但编译器却给了我们一个教训。

std::deque类模板在stl库中的定义需要两个类型参数，第一个参数是元素类型，第二个参数是分配器allocator的类型，虽然std::deque的第二个类型参数有默认值，但是当编译器使用std::deque替换Container时却会严格匹配参数，默认值被忽略了。

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

可以看到模板的模板参数特性，可以让类模板之间互相组合。如果我们将类模板比作函数，那么可以接受模板作为参数的类模板，就相当于一个函数的入参仍旧可以是函数，这就是高阶函数的概念。

#### 模板特化

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

在Stack特化版本的声明`template<typename T> struct Stack<T, Array>`中，Stack名字后面的尖括号中`Stack<T, Array>`传递的参数可以是具体类型，也可以不是具体类型，但是至少要比Stack主模板（非特化版本）的参数更加特殊一些，而且和主模板的参数声明顺序的约束必须一致。

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

注意，主模板的template关键字后面定义了该模板的基本原型特征，特化模板的**模板名称关键字后面的尖括号**中的模板参数必须和**主模板template关键字后面尖括号**中的参数顺序和约束一致。上例中由于主模板声明第一个模板参数是类型，第二个模板参数是模板，所以特化版本`Stack<T, Array>`尖括号中的参数不能多也不能少，且顺序不能颠倒，而且第二个参数Array声明必须和主模板中对Container的模板约束一致。

特化版本的template后面紧跟的尖括号中仅是声明特化版本中还在使用的非具体类型参数，和主模板template后面紧跟的尖括号中的参数没有任何关系。

上例中，我们修改了`Stack<T, Array>`中`push`、`pop`、`empty`成员方法的实现，并且增加了`size`数据成员。我们甚至还可以修改`Stack<T, Array>`中的接口名称，不再叫push和pop，或者删掉empty的实现，只要`Stack<T, Array>`的客户正确地使用该特化版本的接口即可。可见对于模板的特化，只需要其签名（模板名和模板参数）和主模板保持一致，而对于其实现，和主模板以及其它特化版本的实现没有任何关系，完全可以根据该特化版本的需要进行定制。

当我们给一个模板传递参数后，编译器会从主模板和所有的特化版本的实现中进行选择，简单来说选择的规则和函数重载的选择顺序类似，就是从最多匹配的那个开始选择。

例如上例中如论是`Stack<int, Array>`还是`Stack<double, Array>`都会匹配`template<typename T> struct Stack<T, Array>`版本的实现，而`Stack<int, std::list>`则会匹配主模板的实现。

关于特化最后再提一个我们后面会用到的知识点，那就是模板也可以定义在一个类中，但是模板的特化不能出现在类中。

#### 模板的非类型参数

前面的例子中，我们分别使用了类型和模板作为类模板的参数。事实上，模板还支持非类型模板参数。

如下用数组实现Stack的模板定义中，模板的第二个参数是一个int型常量，用于定义数组的最大长度。

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

一般来说，模板的非类型参数只能是整型常量（包括enum），或者指向外部链接的指针（包括函数指针，成员函数指针）。到目前为止还不支持浮点数，对于字符串常量也不支持，但是可以支持具有外部链接的字符串常量指针。

例如对于下面的模板定义：

~~~cpp
template<const char* MyName>
struct Token
{
    std::string name{MyName};
};
~~~

如下使用都会编译错误：

~~~cpp
	Token<“Hello”> tocken；
~~~

~~~cpp
    const char* s = "Hello";
    Token<s> tocken;
~~~

而如下是可以正确编译通过的：

~~~cpp
extern const char s[] = "Hello";

Token<s> token;
std::cout << tocken.name << std::endl;
~~~

总结一下，模板的参数支持一下类型：

- 类型参数；
	使用typename或者class指示。

- 非类型参数；
	整型常量，或者指向外部链接的指针。

- 模板参数；
	使用`template<...> class XXX`的形式指示。



#### 利用模板做编译期计算

当模板的形参被实参替换时，模板会进行编译期计算。由于模板的参数支持类型参数和非类型参数，所以模板在编译期可以进行两类计算：类型计算和数值计算

##### 类型计算
typedef
using

##### 数值计算
enum
static const

### 递归模板

计算阶乘

### 和函数式对比

不可变性

enum and using

模式匹配和递归

高阶函数

一切都是类型

一切都是函数

柯理化

### 总结：不同阶段的C\++

编译期C\++可以看做是一门解释型语言，这时编译期充当着解释器，直接针对C\++源码进行计算。我们知道代码的元信息最全的地方就在于源码中，所以解释性语言往往拥有比较强大的反射能力。同样编译期C\++也具有非常强大的反射能力，这就是C\++ traits技术的力量来源。正式这种编译期反射的能力，是的基于类型计算的模板技术，是C\++构建框架和库的必备武器。

反射能力的来源

## Test

## Type List

## 连接编译期和运行期

### traits

### policy

### 类型推断

## Samples

### 内存分配自动分派

### Dates：类型判断

### Visitor

### FSM DSL

## 总结


