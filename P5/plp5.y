%token fn endfn
%token numint numreal id
%token _int real array var
%token _if _else elif fi
%token range _while loop endloop
%token pari pard cori cord
%token coma let asig pyc
%token print _read opas opmd
%token dosp blq fblq

%{

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

#include "comun.h"
#include "TablaSimbolos.h"
#include "TablaTipos.h"

extern int ncol, nlin, findefichero;
extern int yylex();
extern char *yytext;
extern FILE *yyin;
void yyerror(char *s);

const int MEM_TOTAL = 16384;
const int MEM_VAR   = 16000;

TablaSimbolos   ts  = new TablaSimbolos(NULL);
TablaTipos      tt  = TablaTipos();

using namespace std;

%}

%%

S       : Fun
            {
                cout << $$.cod;
            }
        ;

Fun     : fn id pari pard Cod endfn
            {

            }
    ;

SType   : _int
            {
                $$.tipo = ENTERO;
            }
        | real
            {
                $$.tipo = REAL;
            }
        ;

Type    : SType
            {

            }
        | array SType Dim
            {

            }
        ;

Dim     : numint coma Dim
            {

            }
        | numint
            {

            }
        ;

Cod     : Cod pyc I
            {

            }
        | I
            {

            }
        ;

I       : Blq
            {

            }
        | let Ref asig E
            {

            }
        | var id IT
            {

            }
        | print E
            {

            }
        | _read Ref
            {

            }
        | _while E I
            {

            }
        | loop id range Range I endloop
            {

            }
        | _if E I Ip
            {

            }
        ;

Range   : numint dosp numint
            {

            }
        | numint
            {

            }
        ;

Blq     : blq
            {

            }
        | blq Cod fblq
            {

            }
        ;

Ip      : _else I fi
            {

            }
        | elif E I Ip
            {

            }
        | fi
            {

            }
        ;

IT      : dosp Type
            {

            }
        | /* Vacío */
            {

            }
        ;

E       : E opas T
            {
                int tipoE = $1.tipo;
                int tipoT = $3.tipo;
                if (tipoE == ENTERO && tipoT == ENTERO)
                {
                    $$.tipo = ENTERO;
                }
                else if (tipoE == REAL && tipoT == REAL)
                {
                    $$.tipo = REAL;
                }
                else if (tipoE == ENTERO && tipoT == REAL)
                {
                    $$.cod = "mov B A\n";                  // mov B A
                    $$.cod = "itor\n";                     // itor
                    $$.cod = "mov A B\n";                  // mov A B
                    $$.tipo = REAL;
                }
                else if (tipoE == REAL && tipoT == ENTERO)
                {
                    $$.cod = "mov " + $3.cod + " A\n";     // mov T A
                    $$.cod = "itor\n";                     // itor
                    $$.cod = "mov A B\n";                  // mov A B
                    $$.tipo = REAL;
                }



                if (strcmp($2.lexema, "+") == 0)
                {
                    if ($$.tipo == ENTERO)
                    {
                        $$.cod = "addi B\n";         // addi B
                    }
                    else
                    {
                        $$.cod = "addr B\n";       // addr B
                    }
                }
                else
                {
                    $$.cod = "sub " + $3.cod;
                }
            }
        | opas T
            {

            }
        | T
            {

            }
        ;

T       : T opmd F
            {

            }
        | F
            {

            }
        ;

F       : numint
            {

            }
        | numreal
            {

            }
        | pari E pard
            {

            }
        | Ref
            {

            }
        ;

Ref     : id
            {
                Simbolo* s = ts.searchSymb($1.lexema);

                if (s == NULL)
                {
                    Simbolo newSymb;
                    newSymb.nombre = $1.lexema;
                    newSymb.tipo = idTipo;
                    newSymb.dir = 0;
                    newSymb.tam = 0;

                    ts.newSymb(newSymb);
                }
            }
        | id cori LExpr cord
            {

            }
        ;

LExpr   : LExpr coma E
            {

            }
        | E
            {

            }
        ;

%%

int main (int argc, char *argv[])
{
    return 0;
}

void yyerror (char *s)
{
	extern int findefichero;
	if (findefichero)
	{
	   msgError(ERREOF,-1,-1,"");
	}
	msgError(ERRSINT, nlin, ncol-strlen(yytext), yytext);
}

void errorSemantico (int nerror, int fila, int columna, const char *s)
{
    fprintf(stderr,"Error semantico (%d,%d): ",fila,columna);
    switch (nerror) {
        case ERR_YADECL: fprintf(stderr,"variable '%s' ya declarada\n",s);
               // fila,columna de la variable
               break;
        case ERR_NODECL: fprintf(stderr,"variable '%s' no declarada\n",s);
               // fila,columna de la variable
               break;
        case ERR_NOCABE:fprintf(stderr,"la variable '%s' ya no cabe en memoria\n",s);
               // fila,columna de la variable
               break;

        case ERR_IFWHILE:fprintf(stderr,"la expresion del '%s' debe ser de tipo entero",s);
               // fila,columna del 'if' o 'while'
               break;
        case ERR_LOOP:fprintf(stderr,"la variable del '%s' debe ser de tipo entero",s);
               // fila,columna del 'loop'
               break;

        case ERR_DIM: fprintf(stderr,"la dimension debe ser mayor que 0\n");
               // fila,columna de la dimension (numint)
               break;
        case ERR_FALTAN: fprintf(stderr,"faltan indices\n");
               // fila,columna del id (si no hay ningún índice) o del último ']'
               break;
        case ERR_SOBRAN: fprintf(stderr,"sobran indices\n");
               // fila,columna del '[' si no es array, o de la ',' que sobra
               break;
        case ERR_INDICE_ENTERO: fprintf(stderr,"el indice de un array debe ser de tipo entero\n");
               // fila,columna del '[' si es el primero, o de la ',' inmediatamente anterior
               break;

        case ERR_ASIG: fprintf(stderr,"tipos incompatibles en la asignacion\n");
               // fila,columna del '='
               break;
        case ERR_MAXTEMP:fprintf(stderr,"no hay espacio para variables temporales\n");
               // fila,columna da igual
               break;
    }
    exit(-1);
}

void msgError (int nerror, int nlin, int ncol, const char *s)
{
     switch (nerror) {
         case ERRLEXICO: fprintf(stderr,"Error lexico (%d,%d): caracter '%s' incorrecto\n",nlin,ncol,s);
            break;
         case ERRSINT: fprintf(stderr,"Error sintactico (%d,%d): en '%s'\n",nlin,ncol,s);
            break;
         case ERREOF: fprintf(stderr,"Error sintactico: fin de fichero inesperado\n");
            break;
         case ERRLEXEOF: fprintf(stderr,"Error lexico: fin de fichero inesperado\n");
            break;
     }

     exit(1);
}
