DEBUGFLAGS := -Wall -Wextra -ansi -std=c99 -g -DDEBUG
COMPILEFLAGS := -Wall -Wextra -ansi -std=c99
SOURCE := rock_paper_scissors.c
BINARY := rock_paper_scissors
GCC := gcc

rock_paper_scissors: rock_paper_scissors.c
	$(GCC) $(COMPILEFLAGS) $(SOURCE) -o $(BINARY)	

debug: 
	$(GCC) $(DEBUGFLAGS) $(SOURCE) -o $(BINARY)

.PHONY: all clean

all: $(BINARY)

clean: 
	@rm -f $(BINARY)
