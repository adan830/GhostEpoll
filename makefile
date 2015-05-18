CXX := g++
CFLAGS := -g
TARGET := epolld
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %cpp,%o,$(SRCS))
all:$(TARGET)
%.o:%.cpp
	$(CXX) $(CFLAGS) -c $<
$(TARGET):$(OBJS)
	$(CXX) $(CFLAGS) -o $@ $^
clean:
	rm -rf $(TARGET) *.o
