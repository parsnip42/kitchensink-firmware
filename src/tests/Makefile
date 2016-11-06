AR = ar
CPP = clang++
CPP_FLAGS = -g -std=c++11 -Wall -Werror -I. -I..
CPP_FILES = $(wildcard *.cpp)
O_FILES = $(CPP_FILES:.cpp=.o)
TARGET = tests
GTEST_DIR = /usr/src/gtest
GTEST_SRCS = $(GTEST_DIR)/src/*.cc

all: $(TARGET)

%.o: %.cpp
	$(CPP) $(CPP_FLAGS) -o $@ -c $<

gtest-all.o: $(GTEST_SRCS)
	$(CPP) $(CPP_FLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o: $(GTEST_SRCS)
	$(CPP) $(CPP_FLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a: gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a: gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

$(TARGET): $(O_FILES) gtest_main.a
	$(CPP) -o $(TARGET) $(O_FILES) gtest_main.a -lpthread

clean:
	rm -f $(TARGET) $(O_FILES) gtest.a gtest_main.a *.o
