#include <stdio.h>
#include <stdlib.h>
#include "sistemaErros.h"
void erroLexico(int macroErro, int linea){
    switch(macroErro){
        case COMPONENTE_NON_RECONECIDO:
            printf("[ERRO->Linea:%d]: Non se pode recoñecer a compoñente pasada\n", linea);
            exit(1);
        break;
        case MAL_FORMADO_EXPONENCIAL:
            printf("[ERRO->Linea:%d]: O numero exponencial analizado está lexicamente mal formado\n", linea);
            exit(1);
            break;
        case MAL_FORMADO_FLECHA:
            printf("[ERRO->Linea:%d]: Este simbolo non existe na gramatica da linguaxe\n", linea);
            exit(1);
            break;
        case MAL_FORMADO_FLOAT:
            printf("[ERRO->Linea:%d]: O numero en punto flotante analizado está lexicamente mal formado\n", linea);
            exit(1);
            break;
    }
}

void erroFicheiro(int macroErro, char *nomeFicheiro){
    switch(macroErro) {
        case APERTURA_FICHEIRO:
            printf("[ERRO->Nome ficheiro:%s]: Non se pode abrir o ficheiro pedido\n", nomeFicheiro);
            exit(1);
            break;
        case BLOQUE_VACIO:
            printf("[ERRO->Nome ficheiro:%s]: Houbo un proble a hora de introducir caracteres nos bloques do sistema de entrada\n", nomeFicheiro);
            exit(1);
            break;
        case EXCESO_TAMANO_LEXEMA:
            printf("[ERRO->Nome ficheiro:%s]: O lexema excede do tamaño de bloque\n", nomeFicheiro);
            //exit(1);
            break;
    }
}