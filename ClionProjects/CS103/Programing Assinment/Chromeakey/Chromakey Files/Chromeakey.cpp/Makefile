# Name: Mark Redekopp
# email: redekopp@usc.edu

CC = compile
CFLAGS = -g -Wall
LDFLAGS =
SRCS =  main.cpp bmplib.cpp
OBJ = $(SRCS:.cpp=.o)
TARGET = main


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

bmplib.o : bmplib.h

main.o: main.cpp bmplib.h

clean:
	rm -f *.o $(TARGET) *~

