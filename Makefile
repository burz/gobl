CC     = clang++ --std=c++11
CFLAGS = -c -g -Wall -Werror

GTEST_INCL = -isystem $(GTEST_DIR)/include
GTEST_LD   = -pthread -L$(GTEST_DIR) -lgtest

SRCDIRS = \
. \
goblb \
gobld \
gobll \
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

all: lib

.PHONY: lib
lib: libgobl.a

.PHONY: gtest
gtest: gobl_gtest.tsk

.PHONY: main
main: gobl.tsk

.PHONY: clean
clean:
	rm -f $(SRCDIRS:%=%/*.o)

libgobl.a: $(NOTEST_OBJS)
	ar -rs $@ $^
	mkdir -p include
	for file in $$(find $(SRCDIRS) -maxdepth 1 -name '*.h'); do \
      ln -sf $$file include/$$(basename $$file); \
	done

gobl.tsk: $(NOTEST_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

gobl_gtest.tsk: $(TEST_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(GTEST_LD)

%.t.o: %.t.cpp
	$(CC) $(CFLAGS) -o $*.t.o $^ $(FLAGS) $(GTEST_INCL)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $*.o $^ $(FLAGS)
