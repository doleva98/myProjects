CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
DEBUG = -g
SRC = singly_list.c test_singly_list.c
OBJ = $(filter %.o, $(SRC:%.c=../obj/%.o))
OBJ_DEBUG = $(SRC:.c=.dbg.o)

TARGET = singly_list.out

$(TARGET) :$(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

../obj/%.o: %.c 
	@$(CC) $(CFLAGS) -c -o $(@D)/$(*F).o $< 

%.dbg.o: %.c 
	@$(CC) $(CFLAGS) $(DEBUG) $< -c 



.PHONY: clean

clean:
	rm $(TARGET) $(OBJ) 

.PHONY: all
all: $(SRC) 
	@$(CC) $(CFLAGS) $(DEBUG) $(SRC) 

debug :$(OBJ_DEBUG) 
	@$(CC) $(CFLAGS) $(DEBUG) $(OBJ) -o  debug.out


queue.ar: $(OBJ)
	ar -r archive $(OBJ)



singly_list.o : singly_list.h
test_singly_list.o : singly_list.h


