/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-27 17:40:45
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-27 18:15:53
 * @Description: file content
 */
#include <vector>
#include <stdio.h>

#include "Timestamp.h"

using muduo::Timestamp;

void passByConstReference(const Timestamp& ts)
{
    printf("Timestamp: %s\n", ts.toString().c_str());
}

void passByValue(Timestamp ts)
{
    printf("Timestamp: %s\n", ts.toString().c_str());
}

void benchmark()
{
    const int kNumer = 1000*1000;

    std::vector<Timestamp> stamps;

    stamps.reserve(kNumer);

    for (int i = 0; i < kNumer; ++i)
    {
        stamps.push_back(Timestamp::now());
    }

    printf("%s\n", stamps.front().toString().c_str());
    printf("%s\n", stamps.back().toString().c_str());
    printf("%f\n", timeDifference(stamps.back(), stamps.front()));

    int increments[100] = {0};
    int64_t start = stamps.front().microSecondsSinceEpoch();
    for (int i = 0; i < kNumer; ++i)
    {
        int64_t next = stamps[i].microSecondsSinceEpoch();
        int inc = next - start;
        start = next;
        if (inc < 0)
        {
            printf("reverse\n");
        }
        else if (inc < 100)
        {
            ++increments[inc];
        }
        else
        {
            printf("big gap: %d\n", inc);
        }
    }

    for (int i = 0; i < 100; ++i)
    {
        printf("%2d: %d\n", i, increments[i]);
    }
}

int main()
{
    Timestamp ts = Timestamp::now();
    printf("Timestamp: %s\n", ts.toString().c_str());
    benchmark();

    return 0;
}
