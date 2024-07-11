/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-10 15:59:47
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-10 15:59:53
 * @Description: file content
 */
#pragma once

#include <boost/noncopyable.hpp>

namespace muduo
{

template<typename T>
class ThreadLocalSingleton : boost::noncopyable
{
 public:

  static T& instance()
  {
    if (!t_value_)
    {
      t_value_ = new T();
    }
    return *t_value_;
  }

  // See muduo/base/ThreadLocalSingleton.h for how to delete it automatically.
  static void destroy()
  {
    delete t_value_;
    t_value_ = 0;
  }

 private:
  ThreadLocalSingleton();
  ~ThreadLocalSingleton();

  static __thread T* t_value_;
};

template<typename T>
__thread T* ThreadLocalSingleton<T>::t_value_ = 0;

}
