CXX=g++
CXXFLAGS=-g -Wall -O0 -std=c++11

# BINARIES=date_test date_unittest timestamp_unittest timezone_dump timezone_unittest
BINARIES=date_test date_unittest timestamp_unittest

all: $(BINARIES)

$(BINARIES):
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@

date_test: Date.h Date.cpp Date_test.cpp

date_unittest: Date.h Date.cpp Date_unittest.cpp

timestamp_unittest: Timestamp.h Timestamp.cpp Timestamp_unittest.cpp

# timezone_dump: TimeZone.h TimeZone.cpp Date.cpp TimeZone_dump.cpp

# timezone_unittest: TimeZone.h TimeZone.cpp Date.cpp TimeZone_unittest.cpp

test: date_unittest
	./date_unittest

clean:
	rm -f *.o $(BINARIES)
