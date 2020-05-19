#include <stdio.h>
#include <string.h>
#include "rbtree.h"
#include "tablaSimbolos.h"
#include "palabrasReservadas.h"
#include "valoresAuxiliares.h"

struct rbtree *taboa;
void inicializarTaboaSimbolos(){
    taboa=rb_create(RB_KEY_STRING);
    for(int i=0;i<NPALABRASRESERVADAS;i++){
        rb_insert(taboa, pReservadas[i], cLexicos[i]);
    }
}

void liberarTaboaSimbolos(){
    rb_destroy(taboa);
}
void _imprimirTaboa(struct rbnode *node){
    if(node!=NULL) {
        _imprimirTaboa(node->left);
        printf("################################\n");
        printf("Key->%s         Value->%d\n", node->key, node->data);
        _imprimirTaboa(node->right);
    }
}

void imprimirTaboa(){
    struct rbnode *raiz=rb_root(taboa);
    printf("\033[32m--------INICIO TÁBOA DE SÍMBOLOS--------\n");
    _imprimirTaboa(raiz);
    printf("--------FIN TÁBOA DE SÍMBOLOS--------\n\033[0m");
}
int obterValorTaboa (char *sym_nome){
    struct rbnode *resultado=rb_find(taboa,sym_nome);
    return resultado->data;
}