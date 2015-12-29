DEBUGFLAGS   := -Wall -Wextra -ansi -std=c99 -g -DDEBUG
COMPILEFLAGS := -Wall -Wextra -ansi -std=c99
SOURCE       := airline_reservation_system.c
BINARY       := airline_reservation_system
SYMBOLDIR    := airline_reservation_system.dSYM
GCC := gcc

airline_reservation_system: airline_reservation_system.c
	$(GCC) $(COMPILEFLAGS) $(SOURCE) -o $(BINARY)	

debug: 
	$(GCC) $(DEBUGFLAGS) $(SOURCE) -o $(BINARY)

.PHONY: all clean

all: $(BINARY)

clean: 
	@rm -f  $(BINARY) 
	@rm -rf $(SYMBOLDIR)
