DEBUGFLAGS   := -Wall -Wextra -ansi -std=c99 -g -DDEBUG -DLOREM_IPSUM
COMPILEFLAGS := -Wall -Wextra -ansi -std=c99
SOURCE       := sentence_table.c
BINARY       := sentence_table
SYMBOLDIR    := sentence_table.dSYM
GCC := gcc

sentence_table: sentence_table.c
	$(GCC) $(COMPILEFLAGS) $(SOURCE) -o $(BINARY)	

debug: 
	$(GCC) $(DEBUGFLAGS) $(SOURCE) -o $(BINARY)

.PHONY: all clean

all: $(BINARY)

clean: 
	@rm -f  $(BINARY) 
	@rm -rf $(SYMBOLDIR)
