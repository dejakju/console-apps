CC=gcc
CPP=g++
CFLAGS=-Wall -g

EXE=stack_array stack_array_multi stack_linkedlist stack_linkedlist_multi

all: $(EXE)

%: %.c
	$(CC) $(CFLAGS) $^ -o $@

%: %.cpp
	$(CPP) $(CFLAGS) $^ -o $@

clean:
	rm -r $(EXE)
