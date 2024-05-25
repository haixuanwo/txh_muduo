/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-25 09:27:42
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-25 14:48:10
 * @Description: file content
 */

#include "Common.h"
#include <sys/time.h>

/**
 * @brief Get current time in us.
 */
int64_t now_us()
{
    struct timeval tv = {0, 0};
    gettimeofday(&tv, nullptr);
    return tv.tv_sec*int64_t(1000000) + tv.tv_usec;
}


/**
 * @brief Get current time in seconds.
 */
double now_seconds()
{
    struct timeval tv = {0, 0};
    gettimeofday(&tv, nullptr);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}
