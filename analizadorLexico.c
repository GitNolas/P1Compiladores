#include "palabrasReservadas.h"
#include "valoresAuxiliares.h"
#include "sistemaEntrada.h"
#include "sistemaErros.h"
#include "tablaSimbolos.h"
#include "analizadorLexico.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
int nLineas=1;

//....::::FUNCIONS DE UTILIDADE PARA O SISTEMA::::....

//E SEPARADOR -> Esta funcion detecta se un caracter e un separador e polo tanto o analizador lexico ten que skipealo
int eSeparador(char caracter){
    for(int i=0;i<strlen(separadores);i++){
        if(caracter==separadores[i]){
            return 1;
        }
    }
    return 0;
}

//E SIMBOLO -> Esta funcion detecta se un caracter e un dos simbolos simples que se listan no ficheiro valoresAuxiliares.h
//Se se trata dun simbolo, devolve o seu componente lexico, noutro caso devolve -1.
int eSimbolo(char caracter){
    for(int i=0;i<strlen(simbolosSimples);i++){
        if(caracter==simbolosSimples[i]){
            return 1;
        }
    }
    return -1;
}
///////////////////////////////////////////////////////////////////////////////////////////////

//....::::FUNCIONS QUE TRATAN COA ESTRUTURA CORRESPONDENTE OS COMPONENTES LEXICOS::::....

//CREAR COMPONENTE LEXICO -> Inicializa unha estrutura correspondente a un componenete lexico
//En caso de crear un CL, o tamano do lexema igualase a 0 para o seguinte lexema
componenteLexico *crearCL (char *sym_nome, int sym_valor) {
    componenteLexico *ptr = (componenteLexico *) malloc (sizeof (componenteLexico));
    ptr->nome = (char *) malloc (strlen (sym_nome) + 1);
    strcpy (ptr->nome,sym_nome);
    ptr->valor = sym_valor;
    ptr->linea=nLineas;
    return ptr;
}

//LIBERAR COMPONENTE LEXICO -> Libera a memoria do componente lexico pasado
void liberarCL(componenteLexico **nodo){
    free((*nodo)->nome);
    free(*nodo);
}
///////////////////////////////////////////////////////////////////////////////////////////

//....::::DECLARACION DAS FUNCIONS EMPREGADAS POLO ANALIZADOR LEXICO::::....
componenteLexico *analizadorSimbolos();
componenteLexico *analizadorNumeros();
//////////////////////////////////////////////////////////////////////////

//....::::AUTOMATAS PARA O RECONECEMENTO DE COMPONENTES LEXICOS::::....

//RETORNAR COMPONENTE LEXICO -> Parte principal do analizador lexico,
// lanza os demais automatas para detectar un componente lexico.
// Devolve un componente lexico o analizador sintactico
componenteLexico *retornarCL(){
    char caracter=seguinteChar(1);
    componenteLexico *resultado;
    while(eSeparador(caracter)){ //Pasamos de todos os separadores
        if(caracter=='\n'){
            nLineas++; //Se se atopa un salto de linea, aumentamos a linea na que nos atopamos
        }
        igualarPunteiros();
        caracter=seguinteChar(0);
    }
    if (eSimbolo(caracter)!=-1){ //En caso de que se atope un simbolo chamase o automata de simbolos
        volveEmpezar();
        return analizadorSimbolos();
    }else if(isalpha(caracter) || caracter=='_'){ //Neste caso a componente lexica sera ou unha palabra reservada ou un id
        caracter=seguinteChar(1);
        while(isalnum(caracter)){
            caracter=seguinteChar(1);
        }
        char *r=lexemaDetectado(1);
        resultado=crearCL(r, obterValorTaboa(r));
        return resultado;
    }else if(isdigit(caracter)){ //Se e un digito chamase o automata de reconecemento de tipos numericos
        volveEmpezar();
        return analizadorNumeros();
    }else if(caracter==EOF){ //Se atopamos o fin de ficheiro devolvemolo, e o analizador sintactico encargarase de rematar o programa
        resultado=crearCL("EOF", EOF);
        return resultado;
    }else{ //Se o caracter obtido non e nada do anterior, lanzase un erro
        erroLexico(COMPONENTE_NON_RECONECIDO, nLineas);
    }
}

//ANALIZADOR NUMEROS -> Analizas os tipos numericos presentes no programa
//Basea o seu funcionamento nun switch case continuo ata que se atopa un simbolo
componenteLexico *analizadorNumeros(){
    char caracter=seguinteChar(1);
    componenteLexico *resultado;
    int estado=0;
    int imaginario=0;
    while(1){
        switch(estado){
            case 0:
                if(isdigit(caracter)){
                    estado=1;
                    caracter=seguinteChar(1);
                }else if(caracter=='.'){
                    estado=5;
                    caracter=seguinteChar(1);
                }
            break;
            case 1:
                if(isdigit(caracter)){
                    estado=1;
                    caracter=seguinteChar(1);
                }else if(caracter=='i'){
                    resultado=crearCL(lexemaDetectado(0), COMPLEJO);
                    return resultado;
                }else if(caracter=='.'){
                    estado=2;
                    caracter=seguinteChar(1);
                }else if(caracter=='x'){
                    estado=3;
                    caracter=seguinteChar(1);
                }else if(caracter=='e'){
                    estado=4;
                    caracter=seguinteChar(1);
                }else if(eSimbolo(caracter)){
                    resultado=crearCL(lexemaDetectado(1), ENTERO);
                    return resultado;
                }
            break;
            case 2:
                if(caracter=='e'){
                    caracter=seguinteChar(1);
                }else{ //Flotante mal formado
                    erroLexico(MAL_FORMADO_FLOAT,nLineas);
                }
                if(isdigit(caracter)){
                    while(isdigit(caracter)){
                        caracter=seguinteChar(1);
                    }
                    resultado=crearCL(lexemaDetectado(1), FLOTANTE);
                    return resultado;
                }else if(caracter=='+'){
                    caracter=seguinteChar(1);
                    while(isdigit(caracter)){
                        caracter=seguinteChar(1);
                        if(caracter=='i'){
                            imaginario=1;
                        }
                    }
                    if(imaginario){
                        resultado=crearCL(lexemaDetectado(0), COMPLEJO);
                        imaginario=0;
                        return resultado;
                    }else{
                        resultado=crearCL(lexemaDetectado(1), FLOTANTE);
                        imaginario=0;
                        return resultado;
                    }
                }
            break;
            case 3:
                while(isalnum(caracter)){
                    caracter=seguinteChar(1);
                }
                resultado=crearCL(lexemaDetectado(1), HEXADECIMAL);
                return resultado;
            break;
            case 4:
                if(caracter=='+' || caracter=='-'){
                    caracter=seguinteChar(1);
                    while(isdigit(caracter)){
                        caracter=seguinteChar(1);
                    }
                    resultado=crearCL(lexemaDetectado(1), FLOTANTE);
                    return resultado;
            }else { //Exponencial malformado
                    erroLexico(MAL_FORMADO_EXPONENCIAL,nLineas);
                }
            break;
            case 5:
                while(isdigit(caracter) || caracter=='E'){
                     caracter=seguinteChar(1);
                }
                resultado=crearCL(lexemaDetectado(1), FLOTANTE);
                return resultado;
            break;
        }
    }
}

//ANALIZADOR SIMBOLOS -> E chamado condo o analizador principal atopa un simbolo
//Dependendo de cales sexan os seguintes caracteres obtidos podria chamar a outros automatas
componenteLexico *analizadorSimbolos(){
    char caracter=seguinteChar(1);
    int identificador;
    componenteLexico *resultado;
    switch(caracter){
//...:::CONTENEDORES:::...
        case '(':
            resultado=crearCL(lexemaDetectado(0), PARENTESISI);
            return resultado;
        break;
        case ')':
            resultado=crearCL(lexemaDetectado(0), PARENTESISD);
            return resultado;
        break;
        case '[':
            resultado=crearCL(lexemaDetectado(0), CORCHETEI);
            return resultado;
        break;
        case ']':
            resultado=crearCL(lexemaDetectado(0), CORCHETED);
            return resultado;
        break;
        case '{':
            resultado=crearCL(lexemaDetectado(0), LLAVEI);
            return resultado;
        break;
        case '}':
            resultado=crearCL(lexemaDetectado(0), LLAVED);
            return resultado;
        break;
        case '\"':
            caracter=seguinteChar(0);
            while(caracter!='\"'){ //Agarda ata que atopa outras comillas
                if(caracter=='\n'){
                    nLineas++;
                }
                if(caracter=='\\'){//Se se encontra co caracter \, omite o seguinte que apareza
                    seguinteChar(0);
                }
                igualarPunteiros();
                caracter=seguinteChar(0);
            }
            igualarPunteiros();
            resultado=crearCL("Cadena de caracteres", STRING);
            return resultado;
        break;
//...:::SIGNOS PUNTUACION:::...
        case ',':
            resultado=crearCL(lexemaDetectado(0), COMA);
            return resultado;
        break;
        case ';':
            resultado=crearCL(lexemaDetectado(0), PUNTOCOMA);
            return resultado;
        break;
        case ':':
            caracter=seguinteChar(1);
            if(caracter=='='){ //Comproba o caso de que se atope :=
                resultado=crearCL(lexemaDetectado(0), DOSPUNTOSIGUAL);
                return resultado;
            }else{
                resultado=crearCL(lexemaDetectado(1), DOUSPUNTOS);
                return resultado;
            }
        break;
        case '.': //Existe opcion de float e de . normal
            caracter=seguinteChar(1);
            if(isdigit(caracter)){ //Comproba o caso de que se atope :=
                volveEmpezar();
                return analizadorNumeros();
            }else{
                resultado=crearCL(lexemaDetectado(1), PUNTO);
                return resultado;
            }
        break;
//...:::OPERADORES:::...
        case '-':
            resultado=crearCL(lexemaDetectado(0), MENOS);
            return resultado;
        break;
        case '=':
            resultado=crearCL(lexemaDetectado(0), IGUAL);
            return resultado;
        break;
        case '*':
            resultado=crearCL(lexemaDetectado(0), MULT);
            return resultado;
        break;
        case '+':
            caracter=seguinteChar(1);
            if(caracter=='='){ //Comproba o caso de que se atope +=
                resultado=crearCL(lexemaDetectado(0), MASIGUAL);
                return resultado;
            }else{
                resultado=crearCL(lexemaDetectado(1), MAS);
                return resultado;
            }
        break;
        case '<':
            caracter=seguinteChar(1);
            if(caracter=='-'){ //Comproba o caso de que se atope +=
                resultado=crearCL(lexemaDetectado(0), FLECHA);
                return resultado;
            }else{
                erroLexico(MAL_FORMADO_FLECHA, nLineas);
            }
            break;
        case '/': //Pode ser division, ou comentario(simple/multilinea)
            caracter=seguinteChar(0);
            if(caracter=='/'){ //Se nos atopamos con // tratase dun comentario simple.
                while(caracter!='\n'){ //Recorremos ata o \n
                    igualarPunteiros();
                    caracter=seguinteChar(0);
                }
                igualarPunteiros();
                resultado=crearCL("Linea de comentario", COMENTARIO);
                nLineas++;
                return resultado;
            }else if(caracter=='*'){ //Se nos atopamos con un /*, tratase dun comentario multilinea
                while(1){ //Recorremos ata atopar un */
                    if(caracter=='\n'){
                        nLineas++;
                    }
                    igualarPunteiros();
                    caracter=seguinteChar(0);
                    if(caracter=='*'){
                        caracter=seguinteChar(0);
                        igualarPunteiros();
                        if(caracter=='/'){
                            igualarPunteiros();
                            resultado=crearCL("Bloque comentario", BLOQUECOMENTARIO);
                            return resultado;
                        }
                    }
                }
            }else{
                resultado=crearCL(lexemaDetectado(1), SLASH);
                return resultado;
            }

        break;
    }
}
