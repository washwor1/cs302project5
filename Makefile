CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash

all:		worddice

worddice:	worddice.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^


