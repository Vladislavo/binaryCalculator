CC = gcc

sources = calc_main.c calc_functions.c
dependencies = calc.h

calc: $(sources) $(dependencies)
	$(CC) $(sources) -lm -o $@

clean:
	rm calc
