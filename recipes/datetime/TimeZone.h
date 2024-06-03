
#pragma once

#include <time.h>
#include <boost/shared_ptr.hpp>

#include "copyable.h"

namespace muduo {

class TimeZone : public muduo::Copyable
{
public:
    explicit TimeZone(const char *zonefile);

    bool valid() const { return data_; }

    struct tm localtime(time_t t) const;
    time_t fromLocalTime(const struct tm& tm) const;

    static struct tm toUtcTime(time_t t, bool yday = false);

    static time_t fromLocalTime(const struct tm&);

    static time_t fromLocalTime(int year, int month, int day, int hour, int min, int sec);

    struct Data;

private:
    boost::shared_ptr<Data> data_;
};

}
