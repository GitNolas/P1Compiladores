#define COMPONENTE_NON_RECONECIDO 2000
#define EXCESO_TAMANO_LEXEMA 2001
#define MAL_FORMADO_EXPONENCIAL 2002
#define MAL_FORMADO_FLOAT 2003
#define MAL_FORMADO_FLECHA 2004
#define APERTURA_FICHEIRO 2005
#define BLOQUE_VACIO 2006
void erroLexico(int macroErro, int linea);
void erroFicheiro(int macroErro,char *nomeFicheiro);