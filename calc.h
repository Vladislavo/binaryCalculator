/* Funciones matematicas para la calculadora binaria */
#ifndef __CALC_H__
#define __CALC_H__
/* lista dinamica para manejar la memoria */
typedef struct node {
	union { 
		char dato;          // operando o resultado
    	char operacion[30]; // cadena descriptiva de la operacion
	} contenido;
	struct node * siguiente;
} node;

/* Cadenas para la representacion */
//const char** oper_str = {"OR", "AND", "XOR", "SHLL", "SHRL"};
//const char** format_str = {"Binario", "Hexadecimal", "Decimal"};

/* OR logico */
char or_log(char op1, char op2);

/* AND logico */
char and_log(char op1, char op2);

/* XOR logico */
char xor_log(char op1, char op2);

/* << (desplazamiento a la izquierda) */
char shl_log(char op, char num);

/* >> (desplazamiento a la derecha) */
char shr_log(char op, char num);

/* Cambio de formato (2 binario, 16 hexadecimal, 10 decimal). */
char * format_change(char *num, char from_base, char to_base);

/* Llenar un trozo de memoria con una operacion */
void fill_mem(char *opt, char *op1, char *op2, void *res, node *mem, char format_code);

/* Alocar la memoria para un nodo */
node * alloc_mem();

/* Deshabilitar la memoria */
void dealloc_mem(node *n);

/* Borrar la memoria */
void delete_mem(node *n);

/* Mostrar el contenido de la memoria */
void show_mem(node *n);

/* Hacer un calculo */
void* compute(char *opt, char *op1, char* op2, char format);

#endif