CC = gcc

sources = calc_main1.c calc_functions.c
dependencies = calc.h

calc: $(sources) $(dependencies)
	$(CC) $(sources) -lm -o $@