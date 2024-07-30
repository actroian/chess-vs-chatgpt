CXX = g++
CXXFLAGS = -std=c++14 -I/opt/X11/include -I./include -I./piece -I./player -I./move -I. -Wall -g

EXEC = chess

CCFILES = $(wildcard *.cc piece/*.cc player/*.cc move/*.cc)

OBJDIR = obj
LDFLAGS = -L/opt/homebrew/lib
LDLIBS = -lcurl -lX11

OBJECTS = $(patsubst %.cc, $(OBJDIR)/%.o, $(CCFILES))

SUBDIRS = $(OBJDIR) $(OBJDIR)/piece $(OBJDIR)/player $(OBJDIR)/move

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(EXEC) $(LDLIBS)

$(OBJDIR)/%.o: %.cc | $(SUBDIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SUBDIRS):
	mkdir -p $(SUBDIRS)

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(EXEC)
