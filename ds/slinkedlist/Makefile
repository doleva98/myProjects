
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))

TARGET = singly_list.out


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
	
singly_list.o : singly_list.h
test_singly_list.o : singly_list.h
