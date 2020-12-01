OBJS = *.c

OBJ_NAME = test

CC = gcc
COMPILER_FLAGS = -w
LINKER_FLAGS = -lSDL2 -lm

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean :
	-rm *.o $(OBJ_NAME)
