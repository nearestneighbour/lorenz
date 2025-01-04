# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra

# Linker flags
LDFLAGS = -lsfml-system -lsfml-graphics -lsfml-window

# Source files
SRCS = main.cpp Attractor.cpp Params.cpp

# Object files
OBJS = $(addprefix build/, $(SRCS:.cpp=.o))

# Executable name
TARGET = main.out

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to build object files from source files
build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)
