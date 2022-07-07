CXX	 = clang++
CXXFLAGS = -O2 -Wall -g

all: pearson.cc
	$(CXX) $(CXXFLAGS) pearson.cc -o pearson

clean:
	rm pearson

.PHONY: all clean
