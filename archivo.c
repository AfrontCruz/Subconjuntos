#include "transicion.h"

void liberarEspacio( transicion *inicio ){
	transicion *aux, *borrar = inicio;
	do{
		aux = borrar->next;
		free( borrar );
		borrar = aux;
	}while( borrar != NULL );
	printf("Se libero el espacio\n");
}

void imprimirTransiciones(transicion *inicio){
	transicion *aux = inicio;
	do{
		printf("Transicion %i %i %c\n", aux->src, aux->dst, aux->step );
		aux = aux->next;
	}while( aux != NULL );
}

listaEstados* cerradura( int estado, listaEstados *lista, transicion *ini ){
	if( lista == NULL ){
		lista = (listaEstados*) malloc( 1*sizeof(listaEstados) );
		lista->element = estado;
		lista->next = NULL;
		printf("La lista es nula\n");
	}else{
		printf("La lista no es nula\n");
	}

	listaEstados *auxState = lista;
	transicion *aux = ini;

	while( aux != NULL ){
		if( aux->src == estado && aux->step == '%' ){
			listaEstados *nuevo = (listaEstados*) malloc( 1*sizeof(listaEstados) );
			nuevo->element = aux->dst;
			nuevo->next = NULL;
			while( auxState->next != NULL){
				auxState = auxState->next;
			}
			auxState->next = nuevo;
			printf("Se agrego un nuevo element\n");
			lista = cerradura( aux->dst, lista, ini );
		}
		aux = aux->next;
	}
	return lista;
}

listaEstados* mover(int estado, listaEstados *lista, transicion *ini){

}

int main(){
	FILE *archivo;
	archivo = fopen("test.txt", "r");	

	if( archivo == NULL){
		printf("No se pudo abrir :c\n");
	}
	else{
		printf("El archivo se abrio:\n");

		int states, ini, nmbfin, src, dst, i, alfabeto;
		char step;

		fscanf(archivo, "%i\n", &states);
		fscanf(archivo, "%i\n", &ini);
		fscanf(archivo, "%i\n", &nmbfin);

		printf("Son %i estados\n", states);
		printf("El estado inicial es: %i\n", ini);
		printf("Hay %i estados finales\n", nmbfin);

		int finales[nmbfin];

		for( i = 0; i < nmbfin; i++ ){
			int aux;
			fscanf(archivo, "%i\n", &aux);
			finales[i] = aux;
			printf("%i. Estado final: %i\n", i+1, finales[i]);
		}

		fscanf(archivo, "%i\n", &alfabeto);
		char alfa[alfabeto];
		printf("Hay %i elementos en el alfabeto\n", alfabeto);

		for( i = 0; i < alfabeto; i++ ){
			fscanf(archivo, "%c\n", &alfa[i] );
			printf("%c\n", alfa[i]);
		}

		transicion *first = (transicion*) malloc( 1*sizeof(transicion) );
		fscanf(archivo, "%i %i %c\n", &src, &dst, &step  );
		first->src = src;
		first->dst = dst;
		first->step = step;
		first->next = NULL;

		transicion *run;
		run = first;

		while( fscanf(archivo, "%i %i %c\n", &src, &dst, &step  ) != EOF ){
			transicion *aux = (transicion*) malloc( 1*sizeof(transicion) );
			aux->src = src;
			aux->dst = dst;
			aux->step = step;
			aux->next = NULL;
			run->next = aux;
			run = aux;
		}
		//first apunta a la primer transicion

		imprimirTransiciones( first );

		listaEstados *lista = cerradura( 1, NULL, first );
		estadoAFD *iniAFD = (estadoAFD*)malloc(sizeof(estadoAFD)*1);
		iniAFD->estado = 1;
		iniAFD->lista = lista;

		
		/*
		printf("\n\n\n\n");
		while(lista != NULL){
			printf("Element: %i\n", lista->element);
			lista = lista->next;
		}*/

		liberarEspacio(first);
		//printf("Estado inicial: %i %i %c\n", stateini.src, stateini.dst, stateini.step );
	}
	fclose(archivo);

	return 0;
}