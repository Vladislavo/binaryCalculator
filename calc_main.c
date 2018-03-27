#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

int main(int argc, char **argv){
	/* Inicializacion de variables :
	 *  res - resultado de la operacion en el modo decimal
	 *  elem - controla numero de 'palabras' itroducidas por el usuario
	 *  on - calculadora esta encendida por defecto
	 *  buffer - el buffer de entrada
	 *  operation - variable auxiliar para el string tockenizer
	 *  operand - array de strings para los operandos y operaciones
	 *  op1, op2 - strings para operandos
	 *  format_code - la base en la cual trabajamos
	 *  memory_on - el flag de habilitacion de la memoria
	*/
	unsigned char res, elem, on = 1;
	char buffer[256], *operation, operand[4][10], op1[10], op2[10];
	unsigned format_code, memory_on;

	/* Inicializacion de la estructura de la memoria */
	node *mem = NULL;
	node *ptr_mem = NULL;

	/* Delimeters para el tokenizer */
	char delimerters[] = {'\n',EOF,' '};

	printf("Bienvenido a la calculadora binaria!\nElija la base en cual va a trabajar (2, 10 o 16):\n");
	fscanf(stdin, "%u", &format_code);
	printf("%s : %u\n", "El formato eligido es ", format_code);

	printf("Habilitar el uso de la memoria? (1-si, 0-no)\n");
	fscanf(stdin, "%u", &memory_on);
	

	/* Llenar la info en la memoria sobre la base en la que trabajamos */
	if(memory_on){
		mem = alloc_mem();
		ptr_mem = mem;

		strcpy(ptr_mem -> contenido.operacion, "base");
		ptr_mem -> siguiente = alloc_mem();
		ptr_mem = ptr_mem -> siguiente;
		ptr_mem -> contenido.dato = format_code;
		ptr_mem -> siguiente = alloc_mem();
		ptr_mem = ptr_mem -> siguiente;
	}

	/* El mensaje informativo de bienvenida */ 
	welcome();

	/* limpiar de la basura el stdin ('\n') */
	fgets(buffer, sizeof(buffer), stdin);

	/* el bucle principal */
	while(on) {
		printf("> ");

		/* get string */
		if(fgets(buffer, sizeof(buffer), stdin) == NULL){
			printf("Error de lectura. Se admite la expresion entre 1 y 256 caracteres.\n");
		}

		/* separarla en operandos */
		operation = strtok(buffer, " ");
		while(operation != NULL){
			strcpy(operand[elem], operation);
			operation = strtok(NULL, delimerters);
			elem++;
		}

		/* empezar el preprocesamiento y computacion */
		if(!strcasecmp(operand[0],"OR")){
			if(format_code == 10){
				/* Si la base es decimal utilizo solo el primer caracter de op1 y op2
				 * Es la forma mas facil para mantener la compatibilidad con la funcion fill_mem(...)
				 */
				op1[0] = atoi(operand[1]);
				op2[0] = atoi(operand[2]);
				res = or_log(op1[0], op2[0]);
			} else {
				/* Si la base no es decimal, trabajamos con strings.
				 * 1) Cambiamos el formato de string a decimal
				 * 2) Hacemos la operacion
				 * 3) Volvemos el resultado en string
				 * 4) y lo cambiamos en base original
				 */
				strcpy(op1, format_change(operand[1], format_code, 10));
				strcpy(op2, format_change(operand[2], format_code, 10));
				res = or_log(atoi(op1), atoi(op2));
				sprintf(operand[3], "%u", res);
				strcpy(operand[3], format_change(operand[3], 10, format_code));
			}
		} else if(!strcasecmp(operand[0],"AND")){
			/* Mira OR */
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
			/* Mira OR */
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
			/* Mira OR */
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
			/* Mira OR */
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
			/* Cambiamos la base solo si se ha introducido la base soportada */
			if(res == 2 || res == 10 || res == 16){
				printf("Ha cambiado la base de %d a %s.\n", format_code, operand[1]);
				format_code = res;
			} else {
				printf("La base no soportada. Introduce 2, 10 o 16.\n");
			}
		} else if(!strcasecmp(operand[0],"memory")){
			/* Desabilito la memoria solo en caso si estaba habilitada. Se habilita de forma similar */
			if(memory_on && !atoi(operand[1])){
				printf("Se ha deshabilitado la memoria.\n");
				memory_on = 0;
			} else if(!memory_on && atoi(operand[1])){
				printf("Se ha habilitado la memoria.\n");
				memory_on = 1;
				if(mem == NULL){
					/* Si se habilita por primera vez la memoria, la inicializamos */
					mem = alloc_mem();
					ptr_mem = mem;

					strcpy(ptr_mem -> contenido.operacion, "base");
					ptr_mem -> siguiente = alloc_mem();
					ptr_mem = ptr_mem -> siguiente;
					ptr_mem -> contenido.dato = format_code;
					ptr_mem -> siguiente = alloc_mem();
					ptr_mem = ptr_mem -> siguiente;
				}
			}
		} else if(!strcasecmp(operand[0],"show\n")){
			/* Mostrar el contenido de la memoria */
			show_mem(&mem);
		} else if(!strcasecmp(operand[0],"exit\n")){
			/* En caso de salida solo salimos del bucle principal */
			on = 0;
		}

		/* Imprimir el resultado de la operacion realizada.
		 * Se imprime solo si es una operacion logica
		 */
		if(strcasecmp(operand[0], "show\n") && strcasecmp(operand[0], "base") && 
			strcasecmp(operand[0], "memory") && strcasecmp(operand[0], "exit\n")){
			if(format_code != 10)
				//printf("\n%s %s %s => %s\n", operand[1], operand[0], operand[2], operand[3]);
				printf("%s\n", operand[3]);
			else
				//printf("\n%u %s %u => %u\n", op1[0], operand[0], op2[0], res);
				printf("%u\n", res);
		}

		/* memory management 
		 * La memoria se llena solo en caso de una operacion logica y un cambio de base.
		 */
		if(memory_on && strcasecmp(operand[0],"show\n") && strcasecmp(operand[0],"memory") &&
			strcasecmp(operand[0], "exit\n")){
			if(format_code == 10){
				/* El objetivo es ahorrar el espacio en nuestra estructura de la memoria.
				 * Por tanto en modo decimal metemos valiores en un caracter y los enviamos para guardar. 
				 */
				char unsigned op1 = atoi(operand[1]);
				char unsigned op2 = atoi(operand[2]);
				fill_mem(operand[0], &op1, &op2, &res, &ptr_mem, format_code);
			}
			else /* en otro caso los enviamos tal como cual (en forma de string) */
				fill_mem(operand[0], operand[1], operand[2], operand[3], &ptr_mem, format_code);
		}

		/* Limpiamos cada vez el numero de elementos introducidos */
		elem = 0;
	}
	/* limpiar la memoria */
	delete_mem(mem);

	printf("Adios.\n");

	return 0;
}
