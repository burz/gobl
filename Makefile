CC     = clang++ --std=c++11
CFLAGS = -c -g -Wall -Werror

GTEST_DIR  = $(shell echo $$GTEST_DIR)
GTEST_INCL = -isystem $(GTEST_DIR)/include
GTEST_LD   = -pthread -L$(GTEST_DIR) -lgtest

SRCDIRS = \
. \
goblb \

INCL = $(SRCDIRS:%=-I%)

LIBS = \

FLAGS = \
$(INCL)

LDFLAGS = \
$(LIBS)

SRCS=$(shell find $(SRCDIRS) -iname '*.cpp')
OBJS=$(SRCS:%.cpp=%.o)

NOTEST_OBJS=$(filter-out %.t.o,$(OBJS))
TEST_OBJS=$(filter-out %.m.o,$(OBJS))

all: gobl.tsk gobl_gtest.tsk

gobl.tsk: $(NOTEST_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

gobl_gtest.tsk: $(TEST_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(GTEST_LD)

.PHONY: test
test:
	./gobl_gtest.tsk

.PHONY: clean
clean:
	rm -f $(SRCDIRS:%=%/*.o)

%.t.o: %.t.cpp
	$(CC) $(CFLAGS) -o $*.t.o $^ $(FLAGS) $(GTEST_INCL)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $*.o $^ $(FLAGS)
