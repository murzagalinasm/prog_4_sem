CC=g++
CFLAGS=-std=c++17 -Wall -g
PROG=sk
PROG_OBJ=game.o sk.o control.o ui.o view.o
all: $(PROG)
$(PROG):$(PROG_OBJ)
	$(CC) $(CFLAGS) -o $@ $^
.o: .cpp .cc
	$(CC) -c $^
clean: 
	rm -fv *.o $(PROG_OBJ) $(PROG)
