/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-27 21:17:48
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-27 21:55:18
 * @Description: file content
 */
#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>
#include <endian.h>
#include <stdint.h>
#include <stdio.h>

#include "Date"
#include "TimeZone.h"
#include <boost/noncopyable.hpp>

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

    bool operator()(const Transition& lhs, const Transition& rhs) const
    {
        if (compareGmt)
        {
            return lhs.gmttime < rhs.gmttime;
        }
        else
        {
            return lhs.localtime < rhs.localtime;
        }
    }

    bool equal(const Transition& lhs, const Transition& rhs) const
    {
        if (compareGmt)
        {
            return lhs.gmttime == rhs.gmttime;
        }
        else
        {
            return lhs.localtime == rhs.localtime;
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

struct TimeZone::Data
{
    vector<detail::Transition> transitions;
    vector<detail::LocalTime> localtimes;
    vector<string> names;
    string addreviation;
};

namespace muduo
{

namespace detail
{

class File : boost::noncopyable
{
public:
    File(const char* file)
        : fp_(::fopen(file, "rb"))
    {

    }

    ~File()
    {
        if (fp_)
        {
            ::fclose(fp_);
        }
    }

    bool valid() const
    {
        return fp_;
    }

    string readBytes(int n)
    {
        char buf[n];
        ssize_t nr = ::fread(buf, 1, n, fp_);
        if (nr != n)
        {
            throw logic_error("no enough data");
        }

        return string(buf, n);
    }

    int32_t readInt32()
    {
        int32_t x = 0;
        ssize_t nr = ::fread(&x, 1, sizeof(int32_t), fp_);
        if (nr != sizeof(int32_t))
        {
            throw logic_error("bad int32_t data");
        }

        return be32toh(x);
    }

    int8_t readInt8()
    {
        int8_t x = 0;
        ssize_t nr = ::fread(&x, 1, sizeof(int8_t), fp_);
        if (nr != sizeof(int8_t))
        {
            throw logic_error("bad int8_t data");
        }

        return x;
    }

private:
    FILE *fp_;
};

bool readTimeZoneFile(const char* zonefile, struct TimeZone::Data* data)
{
    File f(zonefile)
    if (f.valid())
    {
        try
        {
            string head = f.readBytes(4);
            if (head != "TZif")
            {
                throw logic_error("bad head");            
            }

            string version = f.readBytes()


        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

    }
}

}

}
