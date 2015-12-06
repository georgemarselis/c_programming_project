DIRS := exercise_1 exercise_2 exercise_3 exercise_4 exercise_5 exercise_6 exercise_7


.PHONY: all clean


all: 
	@for directory in $(DIRS); do $(MAKE) --directory=$${directory} all; done

clean:
	@for directory in $(DIRS); do echo "Cleaning in directory $${directory}"; \
		$(MAKE) --directory=$${directory} clean; done
