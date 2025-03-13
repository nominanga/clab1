CC = gcc
CFLAGS = -Wall -g

SRCS = main.c complex.c matrix.c types.c
OBJS = $(SRCS:.c=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

rebuild: clean all
