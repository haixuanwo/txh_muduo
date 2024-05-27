

#include "Date"
#include "TimeZone.h"
#include <boost/noncopyable.hpp>

#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>
#include <endian.h>
#include <stdint.h>
#include <stdio.h>

namespace muduo {

namespace detail {

struct Transition {
    time_t gmttime;
    time_t localtime;
    int localtimeIdx;

    Transition(time_t gmttime, time_t localtime, int localtimeIdx)
        : gmttime(gmttime), localtime(localtime), localtimeIdx(localtimeIdx)
    {

    }
};

struct Comp
{
    bool compareGmt;
    Comp(bool compareGmt) : compareGmt(compareGmt) {}

    bool operator()(const Transition& t1, const Transition& t2) const
    {
        if (compareGmt)
        {
            return t1.gmttime < t2.gmttime;
        }
        else
        {
            return t1.localtime < t2.localtime;
        }
    }

    bool equal(const Transition& t1, const Transition& t2) const
    {
        if (compareGmt)
        {
            return t1.gmttime == t2.gmttime;
        }
        else
        {
            return t1.localtime == t2.localtime;
        }
    }
};

struct LocalTime {
    time_t gmtoffset;
    bool isdst;
    int arrbIdx;

    LocalTime(time_t offset, bool dst, int arrb)
        : gmtoffset(offset), isdst(dst), arrbIdx(arrb)
    {

    }
};

inline void fillHMS(unsigned seconds, struct tm* utc)
{
    utc->tm_sec = seconds % 60;
    unsigned minutes = seconds /= 60;
    utc->tm_min = minutes % 60;
    utc->tm_hour = minutes / 60;
}

}

const int kSecondsPerDay = 24 * 60 * 60;
}

using namespace muduo;
using namespace std;

