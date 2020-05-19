#include <stdio.h>
#include "analizadorLexico.h"

//ANALISIS SINTACTICO --> Dende aqui chamase a funcion que devolve os componentes lexicos, para imprimilos
void analisisSintactico(){
    componenteLexico *aux=retornarCL();
    while(aux->valor!=EOF){
        printf("%d : < %s , %d >\n\n",aux->linea, aux->nome,aux->valor);
        aux=retornarCL();
    }
}

