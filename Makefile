CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash

all:		solution

solution:	worddice.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^


