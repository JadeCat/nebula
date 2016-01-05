CXX=gcc
CXXFLAGS=-lncurses -Wall -zmuldefs

nebula.out: nebula.cpp drawing.cpp drawing.h
	$(CXX) $(CXXFLAGS) nebula.cpp drawing.cpp drawing.h -o nebula.out

.PHONY: clean
clean:
	rm -f nebula.out
