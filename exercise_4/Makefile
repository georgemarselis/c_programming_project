DEBUGFLAGS   := -Wall -Wextra -ansi -std=c99 -g -DDEBUG
COMPILEFLAGS := -Wall -Wextra -ansi -std=c99
SOURCE       := rational_manipulation.c
BINARY       := rational_manipulation
SYMBOLDIR    := rational_manipulation.dSYM
GCC := gcc

rock_paper_scissors: rock_paper_scissors.c
	$(GCC) $(COMPILEFLAGS) $(SOURCE) -o $(BINARY)	

debug: 
	$(GCC) $(DEBUGFLAGS) $(SOURCE) -o $(BINARY)

.PHONY: all clean

all: $(BINARY)

clean: 
	@rm -f  $(BINARY) 
	@rm -rf $(SYMBOLDIR)
