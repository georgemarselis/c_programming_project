DIRS := exercise_1 exercise_2 exercise_3 exercise_4 exercise_5 exercise_6 exercise_7


.PHONY: all clean


all: 


clean:
	@for directory in $(DIRS); do echo "Cleaning in directory $${directory}"; \
		$(MAKE) --directory=$${directory} clean; done