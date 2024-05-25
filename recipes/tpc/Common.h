/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-22 21:34:35
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-25 11:43:45
 * @Description: file content
 */

#pragma once

#include <string>
#include <assert.h>
// #define NDEBUG   // 取消assert

/*
void abort(void);

在Linux系统中，当一个进程执行 abort 函数时，会发生以下一系列事件：

1、终止信号发送：abort 函数会向调用它的进程发送一个 SIGABRT 信号。这个信号的默认行为是终止进程。

2、信号处理：如果进程没有捕获或忽略 SIGABRT 信号，或者没有为该信号设置自定义的处理函数，那么进程将按照默认行为被终止。

3、核心转储：在终止进程之前，Linux系统通常会生成一个核心转储文件（core dump），除非这个功能被系统管理员禁用或者受到资源限制。核心转储文件包含了进程终止时的内存状态，这对于调试非常有用。

4、进程终止：进程被终止后，它的所有资源（如打开的文件、内存等）会被操作系统回收。如果进程是某个进程组的成员，并且该进程组没有其他活动的进程，那么该进程组也会被终止。

5、父进程通知：进程终止后，它的父进程会通过 wait 或 waitpid 等系统调用接收到子进程终止的通知。如果父进程没有及时处理这个通知，子进程会变成一个僵尸进程，直到父进程处理了它的终止状态。

6、日志记录：系统可能会在日志文件中记录进程的异常终止信息，这取决于系统的配置和日志级别。

在实际应用中，调用 abort 通常意味着程序遇到了无法恢复的错误，需要立即终止。然而，这种做法可能会导致数据丢失或状态不一致，因此在调用 abort 之前，应该尽可能地进行错误处理和资源清理。在多线程环境中，abort 会导致整个进程的所有线程都被终止。

如果需要更精细地控制进程的终止行为，可以考虑使用其他机制，如信号处理函数、异常处理等，以便在终止进程之前执行必要的清理工作。
*/

/*
在Linux C++中，abort 和 assert 函数都可以导致进程终止，但它们的用途和行为有本质的区别：

assert：

assert 是一个宏，定义在 <cassert> 头文件中。
它的作用是在程序运行时检查一个表达式是否为真。如果表达式为假（即返回 0），assert 会输出一条错误信息，并调用 abort 来终止程序。
assert 主要用于调试阶段，用来检查程序中的条件是否应该为真，以确保程序的正确性。
在发布应用程序时，通常会定义 NDEBUG 宏来禁用 assert，以避免在发布时产生不必要的性能开销。
abort：

abort 是一个函数，定义在 <cstdlib> 头文件中。
它的作用是立即终止当前进程，不执行任何清理操作，也不会调用 exit 函数。
abort 不检查任何条件，它总是立即终止程序。
由于 abort 不执行清理操作，因此在调用 abort 前，应该确保已经释放所有必要的资源，否则可能导致资源泄漏或其他问题。
总结：

assert 用于调试目的，用于检查程序中的条件是否满足，并在条件不满足时提供错误信息。
abort 用于立即终止程序，通常在程序遇到无法恢复的错误时使用，不执行任何清理操作。
在使用这些函数时，应该根据程序的具体需求和调试阶段来选择合适的函数。在生产环境中，应该尽量避免使用 abort，以防止资源泄漏和数据不一致。
*/


class noncopyable
{
protected:
    noncopyable()
    {

    }

private:
    noncopyable(const noncopyable&) = delete;
    void operator=(const noncopyable&) = delete;
};

struct  copyable
{

};

class StringArg : copyable
{
public:
    StringArg(const char* s) : str_(s)
    {

    }

    StringArg(const std::string& s) : str_(s.c_str())
    {

    }

    const char* c_str() const
    {
        return str_;
    }

private:
    const char* str_;
};

// 隐式类型转换
template<typename To, typename From>
To implicit_cast(const From& f)
{
    return f;
}

/**
 * @brief Get current time in us.
 */
int64_t now_us();

/**
 * @brief Get current time in seconds.
 */
double now_seconds();
