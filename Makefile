# Eric Chun - jc2ppp - 11/10/20 - Makefile                                      

goal: encoder decoder

CXX = clang++ $(CXXFLAGS)
CXXFLAGS = -Wall
DEBUG = -g
EOBJECTS = node.o heap.o huffmanenc.o
DOBJECTS = node.o heap.o huffmandec.o

encoder: $(EOBJECTS)
	$(CXX) $(DEBUG) $(EOBJECTS) -o encoder

decoder: $(DOBJECTS)
	$(CXX) $(DEBUG) $(DOBJECTS) -o decoder

heap.o: heap.cpp heap.h node.h
huffmandec.o: huffmandec.cpp heap.h node.h
huffmanenc.o: huffmanenc.cpp heap.h node.h
node.o: node.cpp node.h

.PHONY: clean
clean:
	-rm -f *.o *~ encoder decoder
