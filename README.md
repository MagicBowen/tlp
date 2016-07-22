# TLP : C\++ Template Programming on Type List

***

## Introduction

TLP is a C\++ template programming package which implement the compile-time data structure `TypeList` and the related algorithms. 

To learn more, visit the doc folder! View the  tests of tlp to learn how to use it and aquire C\++ template programming!

## Install and Test

### Get TLP

~~~ bash
git clone git@github.com:magicbowen/tlp.git
~~~

### Test TLP

To test CUB, you need install [cut](https://github.com:ccup/cut) which is an elegant C\++ xUnit framework. Try to intall cut by following the [cut tutoral](https://github.com:ccup/cut/blob/master/README.md)!

Following the below instructions to test TLP:

~~~ bash
cd tlp
mkdir build
cd build
cmake -DENABLE_TEST=1 ..
make
./test/tlp-test
~~~

### Install TLP

~~~bash
cd build
cmake ..
make
sudo make install
~~~

### Supported Platform:

- [MAC OS X] supported
- [Linux] supported
- [Windows] not supported

### Supported Compilers:

- [CLANG] 3.4 or later.
- [GCC] 4.8 or later.
- [MSVC] not supported.
