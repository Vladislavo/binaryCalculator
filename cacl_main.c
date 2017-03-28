#include <stdio.h>
#ifndef __CALC_H__
#include "calc.h"
#endif

int main(int argc, char **argv){
	char format_code, operation, op1, op2, num, exit = 0;
	node *mem = alloc_mem();

	printf("%s\n", "Bienvenido a la calculadora binaria!\n
		Elige el formato numerico con cual va a trabajar a continuacion:\n
		(0-binario, 1-hexadeciamal, 2-decimal\n");
	format_code = getc();
	printf("%s %s\n", "El formado eligido es ", format_str[format_code]);

	do {
		printf("%s\n", "Que operacion desea realizar?\n 
			(0-Salir, 1-OR, 2-AND, 3-XOR, 4-SHLL, 5-SHRL, 6-Cambiar el formato, 7-Mostrar la memoria)\n");
		operation = getc();
		printf("%s\n", "Introduce el primer operando");
		op1 = getc();

		

		switch (operation){
			case(0):
				delete_mem(mem);
				exit = 0;
			break;
			case(1):

			break;
			case(2):

			break;
			case(3):

			break;
			case(4):

			break;
			case(5):

			break;
			case(6):

			break;
			case(7):

			break;
		}
	} while(!exit)
	return 0;
}