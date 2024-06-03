/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-27 21:17:48
 * @LastEditors: Clark
 * @LastEditTime: 2024-06-03 22:18:26
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

    Transition(time_t gmttime_, time_t localtime_, int localtimeIdx_)
        : gmttime(gmttime_), localtime(localtime_), localtimeIdx(localtimeIdx_)
    {

    }
};

struct Comp
{
    bool compareGmt;
    Comp(bool gmt) : compareGmt(gmt)
    {

    }

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

            string version = f.readBytes(1);
            f.readBytes(15)

            int32_t isgmtcnt = f.readInt32();
            int32_t isstdcnt = f.readInt32();
            int32_t leapcnt = f.readInt32();
            int32_t timecnt = f.readInt32();
            int32_t typecnt = f.readInt32();
            int32_t charcnt = f.readInt32();

            vector<int32_t> trans;
            vector<int32_t> localtimes;
            trans.reserve(timecnt);
            for (ssize_t i = 0; i < timecnt; i++)
            {
                trans.push_back(f.readInt32());
            }

            for (ssize_t i = 0; i < timecnt; i++)
            {
                uint8_t local = f.readUInt8();
                trans.push_back(f.readInt32());
            }

            for (ssize_t i = 0; i < typecnt; i++)
            {
                int32_t gmtoff = f.readInt32();
                uint8_t isdst = f.readUInt8();
                uint8_t abbrind = f.readUInt8();

                data->push_back(Localtime(gmtoff, isdst, abbrind));
            }

            for (ssize_t i = 0; i < timecnt; i++)
            {
                int localIdx = localtimes[i];
                time_t localtime = trans[i] + data->localtimes[localIdx].gmtoffset;
                data->transitions.push_back(Transition(trans[i], localtime, localIdx));
            }

            data->abbreviation = f.readBytes(charcnt);

            for (ssize_t i = 0; i < leapcnt; i++)
            {
                int32_t leaptime = f.readInt32();
                int32_t cumleap = f.readInt32();
            }
        }
        catch(logic_error& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    return true;
}

const Localtime* findLocaltime(const TimeZone::Data& data, Transition sentry, Comp comp)
{
    const LocalTime* local = nullptr;

    if (data.transitions.empty() || comp(sentry, data.transitions.front()))
    {
        local = &data.localtimes.front();
    }
    else
    {
        vector<Transition>::const_iterator it =
            std::lower_bound(data.transitions.begin(),
                             data.transitions.end(),
                             sentry,
                             comp);

        if (it != data.transitions.end())
        {
            if (!comp.equal(sentry, *it))
            {
                assert(it!= data.transitions.begin());
                --it;
            }

            local = &data.localtimes[it->localtimeIdx];
        }
        else
        {
            local = &data.localtimes[data.transitions.back().localtimeIdx];
        }
    }

    return local;
}


} // namespace detail

} // namespace muduo


TimeZone::TimeZone(const char* zonefile)
    : data_(new TimeZone::Data)
{
    if (!detail::readTimeZoneFile(zonefile, data_.get()))
    {
        data_.reset();
    }
}

struct tm TimeZone::toLocalTime(time_t seconds) const
{
    struct tm locaTime = {0, 0};
    assert(data_ != nullptr);
    const Data& data(*data_);

    detail::Transition* sentry(seconds, 0, 0);
    const detail::LocalTime* local = findLocaltime(data, seconds, detail::Comp(true));

    if (local)
    {
        time_t localSeconds = seconds - local->gmtoffset;
        ::gmtime_r(&localSeconds, &localtime);
        localTime.tm_isdst = local->isdst;
        localTime.tm_gmtoff = local->gmtoffset;
        localTime.tm_zone = data.abbreviation[local->arrbIdx];
    }

    return localTime;
}

time_t TimeZone::fromLocalTime(struct tm* localTime) const
{
    assert(data_ != nullptr);
    const Data& data(*data_);

    struct tm tmp = localTime;
    time_t seconds = ::timegm(&tmp);
    detail::Transition sentry(0, seconds, 0);
    if (localTime->tm_isdst)
    {
        struct tm tryT
        m = toLocalTime(seconds - local->gmtoffset);


        const detail::LocalTime* local = findLocaltime(data, localSeconds, detail::Comp(false));
        if (local)
        {
            seconds = localSeconds + local->gmtoffset;
        }
    }

    return seconds;
}

