# TLP : Learnning template meta programming by C++11!

***

## Introduction

TLP is a C\++ template programming package including below:

- Compile-time base type `IntType`, `BoolType` and algorithms on them;

- Compile-time data structure `TypeList`;

- Base algorithms on `TypeList` such as  `Length`, `Append`, `Erase`, `Replace`...

- Advanced algorithms on `TypeList` such as  `Any`, `All`, `Filter`, `Map`, `Fold`, `Sort`...

- Template meta programming utils such as `IsEqual`, `IfThenElse`, `IsConvertible`, `IsBaseOf`...

- A pure compile-time test framework for C\++ template meta programming;

To learn more about tlp and how to do C\++ template meta programming,  please visit the doc folder and view the  tests of tlp!

## Install and Test

### Get TLP

~~~ bash
git clone git@github.com:magicbowen/tlp.git
~~~

### Install TLP

~~~bash
cd tlp
mkdir build
cd build
cmake ..
make
sudo make install
~~~

### Test TLP

Tlp use its own test framework for testing.  

Just compile the testcases for testing. If all tests are compiled ok, it means that all tests pass.

~~~ bash
cd tlp
mkdir build
cd build
cmake -DENABLE_TEST=1 ..
make
./test/tlp-test
~~~

### Supported Platform:

- [MAC OS X] supported
- [Linux] supported
- [Windows] not supported

### Supported Compilers:

- [CLANG] 3.4 or later.
- [GCC] 4.8 or later.
- [MSVC] not supported.
