#include "tablaSimbolos.h"
#include "sistemaEntrada.h"
#include "analizadorSintactico.h"
#include "valoresAuxiliares.h"
#include <ctype.h>
int main(int argc, char *argv[]) {
    //Fase de inicializacion
    inicializarTaboaSimbolos();
    imprimirTaboa();

    iniciarSistemaEntrada(argv[1]);

    //Fase de analisis
    analisisSintactico();

    //Fase final de liberacion
    imprimirTaboa();
    liberarTaboaSimbolos();
    liberarSistemaEntrada();
    return 0;
}
