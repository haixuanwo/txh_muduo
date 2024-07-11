
CXXFLAGS = -O0 -g -Wall -I ../../ -pthread
LDFLAGS = -lpthread
BASE_SRCS = ../../logging/Logging.cc \
            ../../logging/LogStream.cc \
            ../../thread/Thread.cc \
			../../datetime/Timestamp.cc

$(BINARIES):
	g++ $(CXXFLAGS) $(LDFLAGS) $(BASE_SRCS) $(LIB_SRC) $(filter %.cc,$^) -o $@

clean:
	rm -f $(BINARIES) core
