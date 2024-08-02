// array_realize.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<vector>
//#include<array>
#include<cstdio>
#include<string>
#include<cstddef>
#include<cstdint>
#include"Array.hpp" 

template<class __Tp, size_t _N>
void func(Array<__Tp, _N>& __arr) {

    //这里可以复用引用的数组的大小
    Array < int8_t, std::decay_t<decltype(__arr)>::size()> __arrnew;
    //注意用size_t来定义循环体变量来保证循环不崩溃
    //且该类型在加arr下标上有天然优势，避免编译器内部执行movezx等操作

    //使用循环体测试size功能
    for (size_t i = 0; i < __arr.size(); i++) {
        __arr.at(i) = i;
    }

    //迭代器实现，这里注释的语句与size_t* 同理，在Array内部使用using来自定义出iterator
    //for (/*Array < uintptr_t, 32>::iterator*/ /*size_t**/  auto it = a.begin(); it != a.end(); ++it) {
    //    *it = it - a.begin();
    //}

    /*size_t count = 0;
    for (auto& ai : __arr) {
        ai = count++;
    }*/
}

int main()
{
    //Array<class __Tp,size_t _N>
    Array<uintptr_t, 3> arr{ 1,2,3 };
   
    try {
        size_t count = 0;
        for (auto& ai : arr) {
            std::cout << ai << "  ";
        }
        std::cout << std::endl;
        func(arr);
        //arr.fill(10);
        arr.swap_two_ele(1,2);
    }
    catch (const std::runtime_error& errorstatement) {
        std::cerr << errorstatement.what() << std::endl;
        return 0;
    }
    /*for (size_t i = 0; i <arr.size(); i++) {
        std::cout << arr[i] << std::endl;
    }*/
    size_t count = 0;
    for (auto& ai : arr) {
        std::cout << ai << "  ";
    }
    std::cout << std::endl;

    //测试front，back函数
    std::cout << arr.front() << "  " << arr.back() << std::endl;
    
    return 0;
}

//Long  2024.8.2实现Array标准库一

