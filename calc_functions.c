#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifndef __CALC_H__
#include "calc.h"
#endif

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
	printf("Come in %s\n", num);
	char res[8] = "", cnt = 0, rem;// aux = 0;
	unsigned aux = 0;
	unsigned char var;

	printf("from b = %u\n", from_base);
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
			/*var = atoi(num);
			printf("var = %d\n", var);
			while(var != 0){
				rem = var % 10;
				aux += rem*pow(2,cnt);
				cnt++;
				var = var / 10;
			}*/
			while(num[cnt] != '\0'){
				aux += (num[cnt] - '0')*pow(2, strlen(num)-cnt-1);
				cnt++;
			}
			printf("%u\n", aux);
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
		printf("Come out %s\n", res);
	return res;
}

void fill_mem(char *opt, char *op1, char *op2, void *res, node *mem, char format_code){
	printf("FILLMEM IN\n");
	strcpy(mem -> contenido.operacion, op1);

	mem -> siguiente = alloc_mem();
	mem = mem -> siguiente;
	strcpy(mem -> contenido.operacion, opt);
	mem -> siguiente = alloc_mem();

	mem = mem -> siguiente;
	strcpy(mem -> contenido.operacion, op2);
	mem -> siguiente = alloc_mem();

	mem = mem -> siguiente;
	strcpy(mem -> contenido.operacion, "=>");
	mem -> siguiente = alloc_mem();

	mem = mem -> siguiente;
	strcpy(mem -> contenido.operacion, res);
	mem -> siguiente = alloc_mem();

	mem = mem -> siguiente;
	strcpy(mem -> contenido.operacion, "|~|");
	mem -> siguiente = alloc_mem();

	mem = mem -> siguiente;
}

node * alloc_mem(){
	return (node *)malloc(sizeof(node));
}

void dealloc_mem(node *n){
	free(n);
}

void delete_mem(node *n){
	node *ptr = n;
	while(ptr != NULL){
		free(ptr);
		ptr = ptr -> siguiente;
	}
}

void show_mem(node *n){
	node *ptr = n;
	while(ptr != NULL){
		//printf("SHOWMEM IN\n");
		printf("%s ", ptr -> contenido);
		ptr = ptr -> siguiente;
	}
}