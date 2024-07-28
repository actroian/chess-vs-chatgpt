CXX = g++
CXXFLAGS = -std=c++14 -I./nlohmann-json/include -I/opt/homebrew/include -Wall -g

EXEC = chess

CCFILES = $(wildcard *.cc)
OBJDIR = obj
LDFLAGS = -L/opt/homebrew/lib
LDLIBS = -lcurl -lX11

# Object files (in the obj directory)
OBJECTS = $(patsubst %.cc, $(OBJDIR)/%.o, $(CCFILES))

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(EXEC) $(LDLIBS)

# Rule to compile source files into object files
$(OBJDIR)/%.o: %.cc | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the object directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(EXEC)
