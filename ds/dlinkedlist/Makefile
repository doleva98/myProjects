CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
DEBUG = -g

#write here all the c files
SRC = doubly_linked_list.c test_doubly_linked_list.c
#####

#write here all the obj files in the obj directory that you need
PROTECTEDOBJ = 
##########

OBJ = $(filter %.o, $(SRC:%.c=../obj/%.o))
OBJ_DEBUG = $(SRC:.c=.dbg.o)

#write here the target name
TARGET = doubly_linked_list.out
######

$(TARGET) : $(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) $(PROTECTEDOBJ) -o $(TARGET)

../obj/%.o : %.c 
	@$(CC) $(CFLAGS) -c -o $(@D)/$(*F).o $< 

%.dbg.o : %.c 
	@$(CC) $(CFLAGS) $(DEBUG) $< -c 



.PHONY : clean
clean :
	rm $(OBJ) $(TARGET)

.PHONY : all
all : $(SRC) $(PROTECTEDOBJ)
	@$(CC) $(CFLAGS) $(DEBUG) $(SRC) 

debug : $(OBJ_DEBUG) 
	@$(CC) $(CFLAGS) $(DEBUG) $(OBJ) $(PROTECTEDOBJ) -o  debug.out


queue.ar : $(OBJ)
	ar -r archive $(OBJ) $(PROTECTEDOBJ)

#write here the o files that you will be compiled here and its prerequisites
test_doubly_linked_list.o : doubly_linked_list.h
doubly_linked_list.o : doubly_linked_list.h


######







