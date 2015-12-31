DEBUGFLAGS   := -Wall -Wextra -ansi -std=c99 -g -DDEBUG  -Wall -Wextra -Wpedantic -Winit-self -Wshadow -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -ansi -std=c99
COMPILEFLAGS := -Wall -Wextra -ansi -std=c99 -g -Wall -Wextra -Wpedantic -Winit-self -Wshadow -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -ansi -std=c99
SOURCE       := queue.c
BINARY       := queue
SYMBOLDIR    := queue.dSYM
GCC := gcc

queue: queue.c
	$(GCC) $(COMPILEFLAGS) $(SOURCE) -o $(BINARY)	

debug: 
	$(GCC) $(DEBUGFLAGS) $(SOURCE) -o $(BINARY)

.PHONY: all clean

all: $(BINARY)

clean: 
	@rm -f  $(BINARY) 
	@rm -rf $(SYMBOLDIR)
