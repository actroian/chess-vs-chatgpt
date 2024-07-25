CXX = g++
CXXFLAGS = -std=c++14 -I./nlohmann-json/include -Wall -g

EXEC = chess

CCFILES = $(wildcard *.cc)
OBJDIR = obj

# Object files (in the obj directory)
OBJECTS = $(patsubst %.cc, $(OBJDIR)/%.o, $(CCFILES))

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC) -lcurl

# Rule to compile source files into object files
$(OBJDIR)/%.o: %.cc | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the object directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(EXEC)
