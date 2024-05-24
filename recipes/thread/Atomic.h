/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-24 15:00:37
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-24 16:00:57
 * @Description: file content
 */

#pragma once

#include <stdint.h>
#include "../tpc/Common.h"

namespace muduo
{

namespace detail
{

template<typename T>
class AtomicInterT : noncopyable
{
public:
    AtomicInterT() : value_(0)
    {

    }

    T get() const
    {
        // 原子操作，无锁编程（lock-free programming）技术
        return __sync_val_compare_and_swap(const_cast<volatile T*>(&value_), 0, 0);
    }

    T getAndAdd(T x)
    {
        // 原子操作，无锁编程（lock-free programming）技术
        return __sync_fetch_and_add(&value_, x);
    }

    T addAndGet(T x)
    {
        return getAndAdd(x) + x;
    }

    T incrementAndGet()
    {
        return addAndGet(1);
    }

    void add(T x)
    {
        getAndAdd(x);
    }


    void increment()
    {
        incrementAndGet();
    }

    void decrement()
    {
        getAndAdd(-1);
    }

    T getAndSet(T newValue)
    {
        // 原子操作，无锁编程（lock-free programming）技术
        return __sync_lock_test_and_set(&value_, newValue);
    }

private:
    volatile T value_;
};

} // namespace detail


typedef detail::AtomicInterT<int32_t> AtomicInt32;
typedef detail::AtomicInterT<int64_t> AtomicInt64;

} // namespace muduo
