APPS = assignment3


OBJECTS = parserClasses.o assignment3.o
HEADERS = parserClasses.h

CXXFLAGS += -g -Wall -std=c++11

all: $(APPS)

$(OBJECTS): $(HEADERS)
$(APPS): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	$(RM) *.o $(APPS)

tar:
	tar -cf Basic_VHDL_Parser.tar.gz Makefile *.cpp *.h


