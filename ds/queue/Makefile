
#write target name here:
TARGET = queue

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
	
%.o : %.c
	$(CC) $(CFLAGS) -c $<
	
		
.PHONY : clean
clean : 
	rm $(TARGET) $(OBJS)
	
#write o files and theire prerequisites (headers)
# .o : .h	
queue.o : queue.h ../singly_list/singly_list.h
queue_tests.o: queue.h


	
