#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef __CALC_H__
#include "calc.h"
#endif

/* Las operaciones logicas */
char or_log(char op1, char op2){
	return (op1 | op2);
}

char and_log(char op1, char op2){
	return (op1 & op2);
}

char xor_log(char op1, char op2){
	return (op1 ^ op2);
}

char shl_log(char op, char num){
	return (op << num);
}

char shr_log(char op, char num){
	return (op >> num);
}

/* Cambio de formato (2 binario, 16 hexadecimal, 10 decimal). */
char * format_change(char* num, char from_base, char to_base){
	/* Allocamos una string en la memoria dinamica */
	char *res = (char *)malloc(sizeof(char)*10);
	/* la inicializamos a "" */
	strcpy(res, "");
	/* variables auxiliares */
	char cnt = 0;
	unsigned aux = 0;
	unsigned char var;

	/* rutinas de cambio de base. Cada una esta implementada de su forma peculiar,
	 * con el objetivo de ahorrar el espacio. (muchas veces utilizando la tabla ASSCI)
	 */
	if(from_base == 10){
		var = atoi(num);
		cnt = log(var)/log(to_base); /* needed to get not inversed version of a binary number (eg 100 instead of 001)*/
		if(to_base == 2){
			while(var != 0){
				res[cnt--] = '0' + (var % 2);
				var = var / 2;
			}
		} else if(to_base == 16){
			while(var != 0){
				res[cnt--] = (var % 16) <= 9? '0'+(var % 16) : 'A'+((var % 16) - 10);
				var = var / 16;
			}
		}
	} else if (from_base == 2){
		if(to_base == 10){
			while(num[cnt] != '\0'){
				aux += (num[cnt] - '0')*pow(2, strlen(num)-cnt-1);
				cnt++;
			}
			sprintf(res, "%u", aux);
		} else if(to_base == 16){
			while(num[cnt] != '\0'){
				aux += (num[cnt] - '0')*pow(2, strlen(num)-cnt-1);
				cnt++;
			}
			sprintf(res, "%lX", aux);
		}
	} else if (from_base == 16){
		if(to_base == 2){
			while(num[cnt] != '\0'){
				if(num[cnt] >= 'A' && num[cnt] <= 'F'){
					aux += (num[cnt] - 'A' + 10)*pow(16, strlen(num)-cnt-1);
				} else if(num[cnt] >= '0' && num[cnt] <= '9') {
					aux += (num[cnt] - '0')*pow(16, strlen(num)-cnt-1);
				}
				cnt++;
			}
			sprintf(res, "%02x", aux);
		} else if(to_base == 10){
			while(num[cnt] != '\0'){
				if(num[cnt] >= 'A' && num[cnt] <= 'F'){
					aux += (num[cnt] - 'A' + 10)*pow(16, strlen(num)-cnt-1);
				} else if(num[cnt] >= '0' && num[cnt] <= '9') {
					aux += (num[cnt] - '0')*pow(16, strlen(num)-cnt-1);
				}
				cnt++;
			}
			sprintf(res, "%d", aux);
		}
	} else 
		perror("Wrong format base.");
	return res;
}

/* La funcion de llenar la memoria con la operacion entera */ 
void fill_mem(char *opt, char *op1, char *op2, char *res, node **memoria, char format_code){
	node *mem = *memoria;
	if(!strcmp(opt, "base")){
		/* Si la operacion es un cambio de base, se llena de su forma. Lo mismo pasa para
		 * la base decimal y el resto de bases.
		 */
		strcpy(mem -> contenido.operacion, opt);
		mem -> siguiente = alloc_mem();
		mem = mem -> siguiente;
		mem -> contenido.dato = format_code;
		mem -> siguiente = alloc_mem();
		mem = mem -> siguiente;
		*memoria = mem;
	} else {
		if(format_code == 10){
			/* first operand */
			mem -> contenido.dato = *op1;
			mem -> siguiente = alloc_mem();

			/* operation */
			mem = mem -> siguiente;
			strcpy(mem -> contenido.operacion, opt);
			mem -> siguiente = alloc_mem();

			/* second operand */
			mem = mem -> siguiente;
			mem -> contenido.dato = *op2;
			mem -> siguiente = alloc_mem();

			/* result */
			mem = mem -> siguiente;
			mem -> contenido.dato = *res;
			mem -> siguiente = alloc_mem();
		} else {
			/* first operand */
			strcpy(mem -> contenido.operacion, op1);
			mem -> siguiente = alloc_mem();

			/* operation */
			mem = mem -> siguiente;
			strcpy(mem -> contenido.operacion, opt);
			mem -> siguiente = alloc_mem();

			/* second operand */
			mem = mem -> siguiente;
			strcpy(mem -> contenido.operacion, op2);
			mem -> siguiente = alloc_mem();

			/* result */
			mem = mem -> siguiente;
			strcpy(mem -> contenido.operacion, res);
			mem -> siguiente = alloc_mem();
		}
		/* keep pointer on the next node */
		mem = mem -> siguiente;
		/* update current mem position */
		*memoria = mem;
	}
}

/* Allocar la memoria de un nodo */
node * alloc_mem(){
	return (node *)malloc(sizeof(node));
}
/* Liberar la memoria de un nodo */
void dealloc_mem(node *n){
	free(n);
}
/* Limpiar toda la memoria */
void delete_mem(node *n){
	node *ptr = n;
	while(ptr != NULL){
		free(ptr);
		ptr = ptr -> siguiente;
	}
}

/* Mostrar la memoria */
void show_mem(node **n){
	node *ptr = *n;
	char base;
	/* Hay su forma de representacion para cambios de base y operaciones logicas.
	 * Cambios de base marcan nueva linea en la impresion de la memoria de tal modo
	 * manteniendo la claridad de las operaciones.
	 */
	printf("Contenido de la memoria: |~| ");
	while(ptr -> siguiente != NULL){
		if(!strcmp(ptr -> contenido.operacion, "base")){
			base = (ptr -> siguiente) -> contenido.dato;
			printf("%s %u \n|~| ", ptr -> contenido.operacion, base);
			ptr = (ptr -> siguiente) -> siguiente;
		} else {
			/* Juego de punteros en cada caso */
			if(base == 10){
				printf("%u %s %u => %u |~| ", ptr -> contenido.dato, 
					(ptr -> siguiente) -> contenido.operacion, ((ptr -> siguiente) -> siguiente) -> contenido.dato,
					(((ptr -> siguiente) -> siguiente) -> siguiente) -> contenido.dato);
			} else {
				printf("%s %s %s => %s |~| ", ptr -> contenido.operacion, 
					(ptr -> siguiente) -> contenido.operacion, ((ptr -> siguiente) -> siguiente) -> contenido.operacion,
					(((ptr -> siguiente) -> siguiente) -> siguiente) -> contenido.operacion);
			}
			ptr = (((ptr -> siguiente) -> siguiente) -> siguiente) -> siguiente;
		}
	}
	printf("\n");
}

/* La funcion informativa de bienvenida */
void welcome(){
	printf("----------------------------------------------------------\n");
	printf("   Operaciones disponibles en la calculadora :            \n");
	printf("    													  \n");
	printf("     . OR   		el OR logico						  \n");
	printf("     . AND  		el AND logico						  \n");
	printf("     . XOR  		el XOR logico					 	  \n");
	printf("     . <<   		desplazamiento a la izqierda 		  \n");
	printf("     . >>   		desplazamiento a la derecha			  \n");
	printf("     . base 		cambio de base numerica 			  \n");
	printf("     . memory 		gestion de la memoria				  \n");
	printf("     . show 		mostrar el contenido de la memoria	  \n");
	printf("     . exit 		salir de la calculadora				  \n");
	printf("														  \n");
	printf("  * Las operaciones se puede itroducir en minusculas      \n");
	printf("		tal como en mayusculas.							  \n");
	printf("														  \n");
	printf("    Introduce la operacion en siguiente forma:			  \n");
	printf("			> operacion operando1 operando2				  \n");
	printf(" 		ej. > or 100 001								  \n");
	printf(" 		ej. > << 1 5								  	  \n");
	printf("----------------------------------------------------------\n");
}