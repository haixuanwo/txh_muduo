
#pragma once

#include <string>

#include "copyable.h"

struct tm;

namespace muduo {

class Date : public muduo::Copyable {
public:
    struct YearMonthDay {
        int year;   // [1900, 2500]
        int month;  // [1, 12]
        int day;    // [1, 31]
    };

    static const int kDayPerWeek = 7;
    static const int kJulianDayOf1970_01_01;

    Date() : julianDayNumber_(0)
    {

    }

    Date(int year, int month, int day);

    explicit Date(int julianDayNum) : julianDayNumber_(julianDayNum)
    {

    }

    explicit Date(const struct tm&);

    void swap(Date& that)
    {
        std::swap(julianDayNumber_, that.julianDayNumber_);
    }

    bool valid() const
    {
        return julianDayNumber_ > 0;
    }

    std::string toIsoString() const;

    struct YearMonthDay yearMonthDay() const;

    int year() const
    {
        return yearMonthDay().year;
    }

    int month() const
    {
        return yearMonthDay().month;
    }

    int day() const
    {
        return yearMonthDay().day;
    }

    int weekDay() const
    {
        return (julianDayNumber_ + 1) % kDayPerWeek;
    }

    int julianDayNumber() const
    {
        return julianDayNumber_;
    }

private:
    int julianDayNumber_;
};

inline bool operator<(const Date& lhs, const Date& rhs)
{
    return lhs.julianDayNumber() < rhs.julianDayNumber();
}

inline bool operator==(const Date& lhs, const Date& rhs)
{
    return lhs.julianDayNumber() == rhs.julianDayNumber();
}

}
