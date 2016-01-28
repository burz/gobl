CC = clang++ --std=c++11
CFLAGS = -c -g -Wall -Werror

GTEST_DIR = $(shell echo $$GTEST_DIR)
GTEST_INCL = -isystem $(GTEST_DIR)/include
GTEST_LIBS = -pthread -L$(GTEST_DIR) -lgtest
GTEST_LD = $(GTEST_INCL) $(GTEST_LIBS)

INCL = \
-Igoblb \

SRCDIRS = \
. \
goblb \

LIBS = \

FLAGS = \
$(INCL)

LDFLAGS = \
$(LIBS)

SRCS=$(shell find $(SRCDIRS) -iname '*.cpp')
OBJS=$(SRCS:%.cpp=%.o)

NOTEST_OBJS=$(filter-out %.t.o,$(OBJS))
TEST_OBJS=$(filter-out %.m.o,$(OBJS))

all: gobl gobl_gtest

gobl: $(NOTEST_OBJS)
	$(CC) -o gobl.tsk $^ $(LDFLAGS)

gobl_gtest: $(TEST_OBJS)
	$(CC) -o gobl_gtest.tsk $^ $(LDFLAGS) $(GTEST_LD)

clean:
	rm -f $(SRCDIRS:%=%/*.o)

%.t.o: %.cpp
	$(CC) $(CFLAGS) -o $*.t.o $^ $(FLAGS) $(GTEST_INCL)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $*.o $^ $(FLAGS)
