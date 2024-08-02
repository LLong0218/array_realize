#pragma once
#include <iostream>
#include<vector>
//#include<array>
#include<cstdio>
#include<string>
#include<cstddef>
#include<cstdint>

#define _LONG_CXX_THROW_OUT_OF_RANGE(__capacity,_N)  [[_UNLIKELY]] throw std::runtime_error("out of range!  index = " + std::to_string(__capacity__) + ". Array size =" + std::to_string(_N));

//优化思路，size_t自动适配32或64位处理器
template<class _Tp, size_t _N>
struct Array {

    using iterator = _Tp*;
    using const_iterator = _Tp const*;

    _Tp _M_elements[_N];
    //重载运算符呈现arr[]效果
    _Tp& operator[](int arr_flag) {
        return _M_elements[arr_flag];
    }
    _Tp const& operator[](int arr_flag) const {
        return _M_elements[arr_flag];
    }

    _Tp& front() {
        return _M_elements[0];
    }
    _Tp const& front() const {
        return _M_elements[0];
    }

    _Tp& back() {
        return _M_elements[_N - 1];
    }
    _Tp const& back() const {
        return _M_elements[_N - 1];
    }
    //优化：异常处理超限，越界问题
    _Tp& at(size_t __capacity__) {
        if (__capacity__ >= _N) {
            _LONG_CXX_THROW_OUT_OF_RANGE(__capacity__, _N);
        }
        return _M_elements[__capacity__];
    }
    //const版本，注意引用形式来避免拷贝浪费空间
    _Tp const& at(size_t __capacity__) const {
        if (__capacity__ >= _N) {
            //unlikely关键字来优化编译器，让其对该语句的执行有内部分析
            _LONG_CXX_THROW_OUT_OF_RANGE(__capacity__, _N);
        }

        return _M_elements[__capacity__];
    }

    //静态成员变量size，加上constexpr可以在编译期就初始化
    static constexpr size_t size() {
        return _N;
    }

    _Tp const* begin() const {
        return _M_elements;
    }
    _Tp const* end() const {
        return _M_elements + _N;
    }

    _Tp* begin() {
        return _M_elements;
    }
    _Tp* end() {
        return _M_elements + _N;
    }

    void fill(_Tp const& __value) noexcept(std::is_nothrow_assignable_v<_Tp>) {
        for (auto& __index : _M_elements) {
            __index = __value;
        }
    }

    //swap实现两个下标的数据交换
    void swap_two_ele(_Tp const __it1, _Tp const __it2) {
        auto __mid = 0;
        __mid = _M_elements[__it1];
        _M_elements[__it1] = _M_elements[__it2];
        _M_elements[__it2] = __mid;
    }

    void swap(Array& __that) noexcept(std::is_nothrow_assignable_v<_Tp>) {
        for (size_t __index = 0; __index < (this->size > __that.size() ? __that.size() : this->size()); __index++) {
            std::swap(_M_elements[__index], __that._M_elements[__index]);
        }
    }


    /*void fill(T const& value) {
        for (size_t i = 0; i < N; i++) {
            m_elements[i] = value;
        }
    }*/
};

//规定不同编译器的执行逻辑
#if defined(_MSC_VER)
#define _ST1W_UNREACHABLE __assume(0)//跳过不执行
#elif defined(__GNUC__)
#define ST1W_UNREACHABLE __builtin_unreachable(0)
#endif

template<class __Tp>
struct Array<__Tp, 0> {

    using iterator = __Tp*;
    using const_iterator = __Tp const*;

    //重载运算符呈现arr[]效果
    __Tp& operator[](int __arr_flag) noexcept {
        _ST1W_UNREACHABLE;
    }
    __Tp const& operator[](int __arr_flag) const {
        _ST1W_UNREACHABLE;
    }

    __Tp& front() {
        _ST1W_UNREACHABLE;
    }
    __Tp const& front() const {
        _ST1W_UNREACHABLE;
    }

    __Tp& back() {
        _ST1W_UNREACHABLE;
    }
    __Tp const& back() const {
        _ST1W_UNREACHABLE;
    }
    //优化：异常处理超限，越界问题
    __Tp& at(size_t __capacity__) {
        _LONG_CXX_THROW_OUT_OF_RANGE(__capacity__, 0);
    }
    //const版本，注意引用形式来避免拷贝浪费空间
    __Tp const& at(size_t __capacity__) const {
        _LONG_CXX_THROW_OUT_OF_RANGE(__capacity__, 0);
    }

    //静态成员变量size，加上constexpr可以在编译期就初始化
    static constexpr size_t size() {
        _ST1W_UNREACHABLE;
    }

    __Tp const* begin() const {
        return nullptr;
    }
    __Tp const* end() const {
        return nullptr;
    }

    __Tp* begin() {
        return nullptr;
    }
    __Tp* end() {
        return nullptr;
    }

    void fill(__Tp const& value) noexcept(std::is_nothrow_assignable_v<__Tp>) {

    }

    //swap实现两个下标的数据交换
    void swap_two_ele(__Tp const it1, __Tp const it2) noexcept(std::is_nothrow_assignable_v<__Tp>) {

    }

    /*void fill(T const& value) {
        for (size_t i = 0; i < N; i++) {
            m_elements[i] = value;
        }
    }*/
};


