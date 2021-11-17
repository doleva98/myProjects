
TARGET = dynnamic_vector.out
OBJS = dynamic_vector.o test_dynamic_vector.o

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
	
dynamic_vector.o : dynamic_vector.c dynamic_vector.h	
	$(CC) $(CFLAGS) -c dynamic_vector.c
	
test_dynamic_vector.o : test_dynamic_vector.c dynamic_vector.h	
	$(CC) $(CFLAGS) -c test_dynamic_vector.c
	
	
.PHONY : clean
clean : 
	rm $(TARGET) $(OBJS)
