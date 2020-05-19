struct componenteLexico { // Tipo de datos que se emplearán en la estructura
    char *nome;
    int valor;
    int linea;
};
typedef struct componenteLexico componenteLexico;


void liberarCL(componenteLexico **nodo);
componenteLexico *crearCL (char *sym_nome, int sym_valor);
componenteLexico *retornarCL();