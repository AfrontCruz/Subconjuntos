#ifndef TRANSICION
#define TRANSICION

#include <stdio.h>
#include <stdlib.h>

typedef struct transicion transicion;
typedef struct estadoAFD estadoAFD;
typedef struct listaEstados listaEstados;
typedef struct  AFD afd;

struct transicion
{
	int src;
	int dst;
	char step;
	transicion *next;
};

struct estadoAFD
{
	int estado;
	listaEstados *lista;
};

struct AFD
{
	estadoAFD *estado;
	int marca;
	estadoAFD *next;
};

struct listaEstados{
	int element;
	listaEstados *next;
};

#endif