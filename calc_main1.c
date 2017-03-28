#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

int main(int argc, char **argv){
	unsigned char format_code=2	, res, elem, memory_on = 1;
	char buffer[256], *operation, operand[4][9], op1[9], op2[9];
	char test = 0;
	node *mem = alloc_mem();
	node *ptr_mem = mem;
	char delimerters[] = {'\n',EOF,' '};

	//printf("%s\n", "Bienvenido a la calculadora binaria!\nElija la base en cual va a trabajar:\n(2-binario, 16-hexadeciamal, 10-decimal)\n");
	//scanf("%u", &format_code);
	//printf("%s : %u\n", "El formato eligido es ", format_code);
	//printf("Habilitar el uso de la memoria? (1-si, 0-no)\n");
	//scanf("%u", &memory_on);

	//printf("Hex %02x\n", 255);
	do {
		printf("Introduce la operacion en forma [operacion operando1 operando2] :  ");
		fflush(stdout);
		/* get string */
		if(fgets(buffer, sizeof(buffer), stdin) == NULL){
			printf("Error de lectura. Se admite la expresion entre 1 y 256 caracteres.\n");
		}
		/* tokenize it into operands */
		operation = strtok(buffer, " ");
		while(operation != NULL){
			strcpy(operand[elem], operation);
			operation = strtok(NULL, delimerters);
			elem++;
		}
		fflush(stdout);
		/* start preprocessing  and computing*/
		if(!strcmp(operand[0],"OR")){
			printf("%s\n", "It is OR");
			if(format_code == 10){
				res = or_log(atoi(operand[1]), atoi(operand[2]));
				sprintf(operand[3], "%u", res);
			} else {
				printf("Before calling format b = %u\n", format_code);
				strcpy(op1, format_change(operand[1], format_code, 10));
				strcpy(op2, format_change(operand[2], format_code, 10));
				res = or_log(atoi(op1), atoi(op2));
				sprintf(operand[3], "%u", res);
				strcpy(operand[3], format_change(operand[3], 10, format_code));

			}
			printf("%s %s %s => %s\n", operand[1], operand[0], operand[2], operand[3]);
		} else if(!strcmp(operand[0],"AND")){
			printf("%s\n", "It is AND");
			if(format_code == 10){
				res = and_log(atoi(operand[1]), atoi(operand[2]));
				sprintf(operand[3], "%u", res);
			} else {
				strcpy(op1, format_change(operand[1], format_code, 10));
				strcpy(op2, format_change(operand[2], format_code, 10));
				res = and_log(atoi(op1), atoi(op2));
				sprintf(operand[3], "%u", res);
				strcpy(operand[3], format_change(operand[3], 10, format_code));

			} 
			printf("%s %s %s => %s\n", operand[1], operand[0], operand[2], operand[3]);
		} else if(!strcmp(operand[0],"XOR")){
			printf("%s\n", "It is XOR");
			if(format_code == 10){
				res = xor_log(atoi(operand[1]), atoi(operand[2]));
				sprintf(operand[3], "%u", res);
			} else {
				strcpy(op1, format_change(operand[1], format_code, 10));
				strcpy(op2, format_change(operand[2], format_code, 10));
				res = xor_log(atoi(op1), atoi(op2));
				sprintf(operand[3], "%u", res);
				strcpy(operand[3], format_change(operand[3], 10, format_code));

			}
			printf("%s %s %s => %s\n", operand[1], operand[0], operand[2], operand[3]);
		} else if(!strcmp(operand[0],">>")){
			if(format_code == 10){
				res = shr_log(atoi(operand[1]), atoi(operand[2]));
				sprintf(operand[3], "%u", res);
			} else {
				strcpy(op1, format_change(operand[1], format_code, 10));
				strcpy(op2, format_change(operand[2], format_code, 10));
				res = shr_log(atoi(op1), atoi(op2));
				sprintf(operand[3], "%u", res);
				strcpy(operand[3], format_change(operand[3], 10, format_code));

			}
			printf("%s %s %s => %s\n", operand[1], operand[0], operand[2], operand[3]);
		} else if(!strcmp(operand[0],"<<")){
			if(format_code == 10){
				res = shl_log(atoi(operand[1]), atoi(operand[2]));
				sprintf(operand[3], "%u", res);
			} else {
				strcpy(op1, format_change(operand[1], format_code, 10));
				strcpy(op2, format_change(operand[2], format_code, 10));
				res = shl_log(atoi(op1), atoi(op2));
				sprintf(operand[3], "%u", res);
				strcpy(operand[3], format_change(operand[3], 10, format_code));

			}
			printf("%s %s %s => %s\n", operand[1], operand[0], operand[2], operand[3]);
		} else if(!strcmp(operand[0],"base")){
			res = atoi(operand[1]);
			if(res == 2 || res == 10 || res == 16){
				printf("Ha cambiado la base de %d a %s.\n", format_code, operand[1]);
				format_code = atoi(operand[1]);
			} else {
				printf("La base no soportada. Introduce 2, 10 o 16.\n");
			}
		} else if(!strcmp(operand[0],"memory")){
			if(memory_on && !atoi(operand[1])){
				printf("Se ha deshabilitado la memoria.");
				memory_on = 0;
			} else if(!memory_on && atoi(operand[1])){
				printf("Se ha habilitado la memoria.");
				memory_on = 1;
			}
		} else if(!strcmp(operand[0],"show\n")){
			printf("Mostrar la memoria.\n");
			show_mem(mem);
		}
		fflush(stdout);
		/* memory management */
		if(memory_on & strcmp(operand[0],"show")){
			fill_mem(operand[0], operand[1], operand[2], operand[3], ptr_mem, format_code);
			printf("Se ha guardado la opercaion\n");
		}
		fflush(stdout);
		elem = 0;
	} while(1);

	return 0;
}