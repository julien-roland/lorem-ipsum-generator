CC=g++
CFLAGS=-c -std=c++14

SOURCES=generator.cpp counter.cpp
TARGETS=generator counter
OBJECTS=$(SOURCES:.cpp=.o)

all: $(TARGETS)

$(TARGETS): %: %.o
	$(CC) $^ -o $@

%.o: %.cpp token.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGETS)
