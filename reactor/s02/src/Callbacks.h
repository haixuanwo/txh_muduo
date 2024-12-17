
#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include "Timestamp.h"

namespace muduo
{

typedef boost::function<void()> TimerCallback;

}
