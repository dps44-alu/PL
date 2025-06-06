#ifndef _COMUN_H_
#define _COMUN_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//temp: variable temporal donde se ha guardado un Factor o resultado de operacion
struct MITIPO
{
    char *lexema, *r1, *r2;
    string cod, temp, aux_lexema;
    int nlin, ncol;
    int tipo;
    int dir;
    int size;
    bool isVar, isOp;
    bool arrays;
    std::vector<int> dims;      // tamaños de cada dimensión
    std::vector<MITIPO> *lista; // para listas de expresiones
};

typedef struct MITIPO MITIPO;

#define YYSTYPE MITIPO

const int   ERRLEXICO           = 1,
            ERRSINT             = 2,
            ERREOF              = 3,
            ERRLEXEOF           = 4,

            ERR_YADECL          = 5,
            ERR_NODECL          = 6,
            ERR_NOCABE          = 7,

            ERR_IFWHILE         = 8,
            ERR_LOOP            = 9,

            ERR_DIM             = 10,
            ERR_FALTAN          = 11,
            ERR_SOBRAN          = 12,
            ERR_INDICE_ENTERO   = 13,

            ERR_ASIG            = 14,
            ERR_MAXTEMP         = 15;

void errorSemantico (int nerror, int fila, int columna, const char *s);
void msgError       (int nerror, int nlin, int ncol, const char *s);

#endif
