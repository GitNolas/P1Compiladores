#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistemaEntrada.h"
#include "sistemaErros.h"
char *A, *B, *inicio, *fin;
FILE *arquivo;
char seguinteBuffer='A'; //Indica cal sera o seguinte buffer utilizado, como comezamos con A, inicializamos a A.
char inicioBloque='A';
char finBloque='A';
int unePunteiros=0;
int tamanoLexema=0;
char *fileName;
//CARGAR BUFFER --> Carga datos no buffer que indique a variable ***seguinteBuffer***
void cargarBuffer(){
    int leidos=0;
    if(seguinteBuffer=='A'){ //Cargamos datos en A
        leidos=fread(A, sizeof(char), T_BUFFER, arquivo);
        if(leidos<0){
            erroFicheiro(BLOQUE_VACIO, fileName);
        }
        A[leidos]=EOF;
        fin=A;
        finBloque='A';
        seguinteBuffer='B';
    }else{ //Cargamos datos en B
        leidos=fread(B, sizeof(char), T_BUFFER, arquivo);
        if(leidos<0){
            erroFicheiro(BLOQUE_VACIO, fileName);
        }
        B[leidos]=EOF;
        fin=B;
        finBloque='B';
        seguinteBuffer='A';
    }
}

//VOLVE EMPEZAR --> Retrasa o punteiro ***FIN*** ata a posicion do punteiro ***INICIO***.
// E util para volver a comezar o analise lexico. Tratase dunha funcion privada
void volveEmpezar(){
    tamanoLexema=0;
    finBloque=inicioBloque;
    fin=inicio;
}

//DESPLAZAR INICIO --> Iguala ***INICIO*** a ***FIN***, para asi comezar a analizar unha nova cadena de 0.
//Tratase dunha funcion privada
void desplazarInicio(){
    inicioBloque=finBloque;
    inicio=fin;
}
//AVANZA INICIO -> Pon unePunteiros a 1 para que o pedir o seguinte caracter se iguale inico a fin
void igualarPunteiros(){
    tamanoLexema=0;
    unePunteiros=1;
}
//VOLVER ATRAS --> Retrasa unha posicion do punteiro **FIN***
// Tratase dunha funcion privada.
void volverAtras(){
    if(fin==A){
        finBloque='B';
        fin=B+T_BUFFER-1;
    }else if(fin==B){
        finBloque='A';
        fin=A+T_BUFFER-1;
    }else{
        fin--;
    }
}
//LIBERAR SISTEMA DE ENTRADA --> Limpa a memoria ocupada polo sistema de entrada
void liberarSistemaEntrada(){
    free(A);
    free(B);
    free(arquivo);
}
//INICIAR SISTEMA DE ENTRADA --> Abre o ficheiro e inicializa as variables globais
void iniciarSistemaEntrada(char *ficheiro){
    fileName=ficheiro;
    arquivo=fopen(fileName, "r");
    if(arquivo==NULL){
        erroFicheiro(APERTURA_FICHEIRO, fileName);
    }
    A=(char *)malloc(sizeof(char)*(T_BUFFER+1)); //Reservase memoria para os buffer
    B=(char *)malloc(sizeof(char)*(T_BUFFER+1));
    inicio=A;
    inicioBloque='A';
    A[T_BUFFER]=EOF; //Indicamos o final do buffer con ***EOF***
    B[T_BUFFER]=EOF;
    cargarBuffer();
}

//SEGUINTE CHAR --> Devolve o caracter correspondente. Comproba se ten que cargar un bloque o comezo do metodo
char seguinteChar(int aumentaLexema){
    if(*fin==EOF){ //Se e o fin de ficheiro, enchemos o seguinte bloque
        cargarBuffer();
    }
    if(*fin==EOF){ //Se sigue sendo o EOF despois de cambiar de buffer, daquela o arquivo acabouse, polo que devolvemos EOF
        return EOF;
    }
    char sChar=*fin;
    if(unePunteiros){
        desplazarInicio();
        unePunteiros=0;
    }
    if(aumentaLexema){
        tamanoLexema++;
    }
    fin++;
    return sChar;
}

//LEXEMA DETECTADO --> Invocarase dende o analizador lexico no momento no que se atope un lexema. Movera os punteiros
//inicio e fin para obter o seguinte lexema e devolvera unha cadea de caracteres co lexema correspondente.
//O argumento indica se e necesario retrasar o punteiro fin unha posicion.
char *lexemaDetectado(int volver){
    if(tamanoLexema>T_BUFFER){ //Tamano lexema
        erroFicheiro(EXCESO_TAMANO_LEXEMA,fileName);
        inicioBloque=finBloque;
        tamanoLexema=0;
        if(finBloque=='A'){ //En caso de que o sistema de entrada detecte un lexema mais grande do permitido, devolve o lexema que se atopa entre fin e o inicio do bloque no que se atopa fin
            inicio=A;
        }else{
            inicio=B;
        }
        return lexemaDetectado(volver);
    }
    if(volver){
        volverAtras();
    }
    char *resultado, *aux;
    int tamano=0;
    if(inicioBloque==finBloque){ //Os punteiros inicio e fin estan contidos no mesmo bloque
        tamano=fin-inicio;
        resultado=(char *)malloc(sizeof(char)*(tamano));
        for(int i=0;i<tamano;i++){
            resultado[i]=*(inicio+i);
        }
        unePunteiros=1;
        tamanoLexema=0;
        return resultado;
    }else{ //Os punteiros atopanse en distintos bloques
        aux=inicio;
        resultado=(char *)malloc(sizeof(char)*(2*T_BUFFER)); //Reservamos memoria para o largo dos dous bloques, por que non sabemos o largo do lexema
        while(tamano<(2*T_BUFFER) && aux!=fin){
            if(*aux==EOF){
                if(inicioBloque=='A'){
                    aux=B;
                }else{
                    aux=A;
                }
            }else {
                resultado[tamano]=*aux;
                aux++;
                tamano++;
            }
        }
        resultado=realloc(resultado, strlen(resultado)+1);
        resultado[strlen(resultado)]='\0';
        unePunteiros=1;
        tamanoLexema=0;
        return resultado;
    }
}