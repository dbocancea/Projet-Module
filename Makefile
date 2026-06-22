TARGET = build/ModuleCore

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Isrc -Isrc/Core

SRCS = $(wildcard src/*.cpp) $(wildcard src/Core/*.cpp)

OBJS = $(patsubst %.cpp, build/%.o, $(notdir $(SRCS)))

vpath %.cpp src src/Core

all: build_dir $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build_dir:
	@mkdir -p build

clean:
	rm -rf build

.PHONY: all clean build_dir