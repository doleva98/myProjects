CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
DEBUG = -g

#write here all the c files
SRC = priority_queue.c test_priority_queue.c
#####

#write here all the obj files in the obj directory that you need
PROTECTEDOBJ = ../obj/sorted_list.o ../obj/doubly_linked_list.o
##########

OBJ = $(filter %.o, $(SRC:%.c=../obj/%.o))
OBJ_DEBUG = $(SRC:.c=.dbg.o)

#write here the target name
TARGET = priority_queue.out
######

$(TARGET) :$(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) $(PROTECTEDOBJ) -o $(TARGET)

../obj/%.o: %.c 
	@$(CC) $(CFLAGS) -c -o $(@D)/$(*F).o $< 

%.dbg.o: %.c 
	@$(CC) $(CFLAGS) $(DEBUG) $< -c 



.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all
all: $(SRC) $(PROTECTEDOBJ)
	@$(CC) $(CFLAGS) $(DEBUG) $(SRC) 

debug :$(OBJ_DEBUG) 
	@$(CC) $(CFLAGS) $(DEBUG) $(OBJ) $(PROTECTEDOBJ) -o  debug.out


queue.ar: $(OBJ)
	ar -r archive $(OBJ) $(PROTECTEDOBJ)

#write here the o files that you will be compiled here and its prerequisites
priority_queue.o : priority_queue.h
test_priority_queue.o : priority_queue.h


######







