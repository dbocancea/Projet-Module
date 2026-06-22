TARGET = ModuleCore

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRCS = ModuleCore.cpp ModuleRegistry.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean