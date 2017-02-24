# contact: Mark Redekopp, David Pritchard

CC = compile
# if needed, install from http://bits.usc.edu/cs103/compile/ or use g++ or clang++
LDFLAGS =

#main
MARCS = main.cpp bmplib.cpp
OBJ = $(MARCS:.cpp=.o)

#shapes
SHARCS = shapes.cpp bmplib.cpp
SHAOBJ = $(SHARCS:.cpp=.o)

#demo
DEMOSRC = demo.cpp bmplib.cpp
DEMOOBJ = $(DEMOSRC:.cpp=.o)

all: main demo shapes

main: $(OBJ)
	$(CC) $(OBJ) -o main

shapes: $(SHAOBJ)
	$(CC) $(SHAOBJ) -o shapes
	
demo: $(DEMOOBJ)
	$(CC) $(DEMOOBJ) -o demo



.cpp.o:
	$(CC) -g -c $<

bmplib.o : bmplib.h

clean:
	rm -f *.o main *~

