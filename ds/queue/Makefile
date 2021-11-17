CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
DEBUG = -g
SRC = queue.c test_queue.c 
PROTECTEDOBJ = ../obj/singly_list.o
OBJ = $(filter %.o, $(SRC:%.c=../obj/%.o))
OBJ_DEBUG = $(SRC:.c=.dbg.o)


queue.out :$(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) $(PROTECTEDOBJ) -o queue.out

../obj/%.o: %.c 
	@$(CC) $(CFLAGS) -c -o $(@D)/$(*F).o $< 

%.dbg.o: %.c 
	@$(CC) $(CFLAGS) $(DEBUG) $< -c 



.PHONY: clean

clean:
	rm $(OBJ) *.out

.PHONY: all
all: $(SRC) 
	@$(CC) $(CFLAGS) $(DEBUG) $(SRC) 

debug :$(OBJ_DEBUG) 
	@$(CC) $(CFLAGS) $(DEBUG) $(OBJ) -o  debug.out


queue.ar: $(OBJ)
	ar -r archive $(OBJ)



queue.o : ../singly_list/singly_list.h queue.h
test_queue.o : queue.h
../obj/singly_list.o : ../slinkedlist/singly_list.c

