CC     = clang++ --std=c++11
CFLAGS = -c -g -Wall -Werror

GTEST_INCL = -isystem $(GTEST_DIR)/include
GTEST_LD   = -pthread -L$(GTEST_DIR) -lgtest

SRCDIRS = \
. \
goblb \
gobld \
goblr \
gobls \
goblu \

INCL = $(SRCDIRS:%=-I%)

LIBS = \

FLAGS = \
$(INCL)

LDFLAGS = \
$(LIBS)

SRCS=$(shell find $(SRCDIRS) -maxdepth 1 -iname '*.cpp')
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
	./gobl_gtest.tsk --gtest_color=yes | tee $@.log

.PHONY: clean
clean:
	rm -f $(SRCDIRS:%=%/*.o)

ALL_SRCS=$(shell find $(SRCDIRS) -maxdepth 1 -iname '*.h') $(SRCS)

.PHONY: wc
wc:
	wc $(ALL_SRCS)

.PHONY: wct
wct:
	wc $(filter %.t.h %.t.cpp,$(ALL_SRCS))

%.t.o: %.t.cpp
	$(CC) $(CFLAGS) -o $*.t.o $^ $(FLAGS) $(GTEST_INCL)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $*.o $^ $(FLAGS)
