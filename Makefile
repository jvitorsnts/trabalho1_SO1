# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Target executable
TARGET = meu_programa

# Source directory
SRCDIR = source/cpp

# Header directory
INCDIR = source/headers

# Source files
SRCS = $(wildcard *.cpp) $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header files
HDRS = $(wildcard *.h) $(wildcard $(INCDIR)/*.h)

# Rule to compile all source files
all: $(TARGET)

# Rule to link object files into target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile each source file into object files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c -o $@ $<

# Rule to clean object files and target executable
clean:
	rm -f $(OBJS) $(TARGET)