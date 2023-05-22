CC=gcc
CPP=g++
CFLAGS=-Wall -g

EXE=credits

all: $(EXE)

%: %.c
	$(CC) $(CFLAGS) $^ -o $@

%: %.cpp
	$(CPP) $(CFLAGS) $^ -o $@

clean:
	rm -r $(EXE)
