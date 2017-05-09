#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

int main(int argc, char **argv){
	unsigned char res, elem, on = 1;
	char buffer[256], *operation, operand[4][10], op1[10], op2[10];
	unsigned format_code, memory_on;

	node *mem = alloc_mem();
	node *ptr_mem = mem;
	char delimerters[] = {'\n',EOF,' '};

	printf("Bienvenido a la calculadora binaria!\nElija la base en cual va a trabajar (2, 10 o 16):\n");
	
	fscanf(stdin, "%u", &format_code);
	printf("%s : %u\n", "El formato eligido es ", format_code);
	//fflush(stdin);  /* no influye */
	printf("Habilitar el uso de la memoria? (1-si, 0-no)\n");

	//printf("antes de scan %d\n", format_code);   /* valor correcto */
	fscanf(stdin, "%u", &memory_on);
	//printf("despues de scan %d\n", format_code);   /* valor 0 (incorrecto) */
	

	/* fill info about the chosen base to work in*/
	strcpy(ptr_mem -> contenido.operacion, "base");
	ptr_mem -> siguiente = alloc_mem();
	ptr_mem = ptr_mem -> siguiente;
	ptr_mem -> contenido.dato = format_code;
	ptr_mem -> siguiente = alloc_mem();
	ptr_mem = ptr_mem -> siguiente;

	welcome();

	/* clean rubish from the stdin ('\n') */
	fgets(buffer, sizeof(buffer), stdin);

	/* the main working loop */
	while(on) {
		printf("> ");
		//fflush(stdout);
		//fflush(stdin);

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

		/* start preprocessing and computing*/
		if(!strcasecmp(operand[0],"OR")){
			if(format_code == 10){
				op1[0] = atoi(operand[1]);
				op2[0] = atoi(operand[2]);
				res = or_log(op1[0], op2[0]);
			} else {
				strcpy(op1, format_change(operand[1], format_code, 10));
				strcpy(op2, format_change(operand[2], format_code, 10));
				res = or_log(atoi(op1), atoi(op2));
				sprintf(operand[3], "%u", res);
				strcpy(operand[3], format_change(operand[3], 10, format_code));
			}
		} else if(!strcasecmp(operand[0],"AND")){
			if(format_code == 10){
				op1[0] = atoi(operand[1]);
				op2[0] = atoi(operand[2]);
				res = and_log(op1[0], op2[0]);
			} else {
				strcpy(op1, format_change(operand[1], format_code, 10));
				strcpy(op2, format_change(operand[2], format_code, 10));
				res = and_log(atoi(op1), atoi(op2));
				sprintf(operand[3], "%u", res);
				strcpy(operand[3], format_change(operand[3], 10, format_code));
			} 
		} else if(!strcasecmp(operand[0],"XOR")){
			if(format_code == 10){
				op1[0] = atoi(operand[1]);
				op2[0] = atoi(operand[2]);
				res = xor_log(op1[0], op2[0]);
			} else {
				strcpy(op1, format_change(operand[1], format_code, 10));
				strcpy(op2, format_change(operand[2], format_code, 10));
				res = xor_log(atoi(op1), atoi(op2));
				sprintf(operand[3], "%u", res);
				strcpy(operand[3], format_change(operand[3], 10, format_code));
			}
		} else if(!strcmp(operand[0],">>")){
			if(format_code == 10){
				op1[0] = atoi(operand[1]);
				op2[0] = atoi(operand[2]);
				res = shr_log(op1[0], op2[0]);
			} else {
				strcpy(op1, format_change(operand[1], format_code, 10));
				strcpy(op2, format_change(operand[2], format_code, 10));
				res = shr_log(atoi(op1), atoi(op2));
				sprintf(operand[3], "%u", res);
				strcpy(operand[3], format_change(operand[3], 10, format_code));
			}
		} else if(!strcmp(operand[0],"<<")){
			if(format_code == 10){
				op1[0] = atoi(operand[1]);
				op2[0] = atoi(operand[2]);
				res = shl_log(op1[0], op2[0]);
			} else {
				strcpy(op1, format_change(operand[1], format_code, 10));
				strcpy(op2, format_change(operand[2], format_code, 10));
				res = shl_log(atoi(op1), atoi(op2));
				sprintf(operand[3], "%u", res);
				strcpy(operand[3], format_change(operand[3], 10, format_code));
			}
		} else if(!strcasecmp(operand[0],"base")){
			res = atoi(operand[1]);
			if(res == 2 || res == 10 || res == 16){
				printf("Ha cambiado la base de %d a %s.\n", format_code, operand[1]);
				format_code = res;
			} else {
				printf("La base no soportada. Introduce 2, 10 o 16.\n");
			}
		} else if(!strcasecmp(operand[0],"memory")){
			if(memory_on && !atoi(operand[1])){
				printf("Se ha deshabilitado la memoria.\n");
				memory_on = 0;
			} else if(!memory_on && atoi(operand[1])){
				printf("Se ha habilitado la memoria.\n");
				memory_on = 1;
			}
		} else if(!strcasecmp(operand[0],"show\n")){
			printf("Mostrar la memoria.\n");
			show_mem(&mem);
		} else if(!strcasecmp(operand[0],"exit\n")){
			on = 0;
		}
		fflush(stdout);

		/* print out the operation */
		if(strcasecmp(operand[0], "show\n") && strcasecmp(operand[0], "base") && 
			strcasecmp(operand[0], "memory") && strcasecmp(operand[0], "exit")){
			if(format_code != 10)
				//printf("\n%s %s %s => %s\n", operand[1], operand[0], operand[2], operand[3]);
				printf("%s\n", operand[3]);
			else
				//printf("\n%u %s %u => %u\n", op1[0], operand[0], op2[0], res);
				printf("%u\n", res);
		}

		/* memory management */
		if(memory_on && strcasecmp(operand[0],"show\n") && strcasecmp(operand[0],"memory") &&
			strcasecmp(operand[0], "exit\n")){
			if(format_code == 10){
				char unsigned op1 = atoi(operand[1]);
				char unsigned op2 = atoi(operand[2]);
				fill_mem(operand[0], &op1, &op2, &res, &ptr_mem, format_code);
			}
			else
				fill_mem(operand[0], operand[1], operand[2], operand[3], &ptr_mem, format_code);
		}
		fflush(stdout);
		elem = 0;
	}
	printf("Adios.\n");

	return 0;
}