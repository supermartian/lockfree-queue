CFLAGS=-ggdb -Wall -Werror
LDFLAGS=-pthread 
CC=gcc
OBJECTS=pkt_queue.o test.o
TARGET=test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

include depends

depends:
	$(CC) -MM $(OBJECTS:.o=.c) > depends

clean:
	rm ./$(TARGET) *.o
