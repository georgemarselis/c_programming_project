DEBUGFLAGS   := -Wall -Wextra -ansi -std=c99 -g -DDEBUG  -Wall -Wextra -Wpedantic -Winit-self -Wshadow -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -ansi -std=c99
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
