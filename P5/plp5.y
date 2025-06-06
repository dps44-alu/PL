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

TablaSimbolos*  ts  = new TablaSimbolos(NULL);
TablaTipos      tt  = TablaTipos();

int posMemoria = 0;
int numEtiqueta = 1;
int numbloque = 0;

using namespace std;

%}

%%

S       : Fun
            {
                $$.cod = $1.cod;
                cout << $$.cod;
            }
        ;

Fun     : fn id pari pard Cod endfn
            {
                $$.cod = $5.cod;
                $$.cod += "halt\n";    // Fin de programa
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
                $$.tipo = $1.tipo;
                $$.size = 1;
                $$.arrays = false;
            }
        | array SType Dim
            {
                $$.tipo = $2.tipo;
                $$.size = $3.size;
                $$.arrays = true;
            }
        ;

Dim     : numint coma Dim
            {
                if (atoi($1.lexema) <= 0)
                    errorSemantico(ERR_DIM, $1.nlin, $1.ncol, $1.lexema);
                $$.size = atoi($1.lexema) * $3.size;
            }
        | numint
            {
                if (atoi($1.lexema) <= 0)
                    errorSemantico(ERR_DIM, $1.nlin, $1.ncol, $1.lexema);
                $$.size = atoi($1.lexema);
            }
        ;

Cod     : Cod pyc I
            {
                $$.cod = $1.cod + $3.cod;
            }
        | I
            {
                $$.cod = $1.cod;
            }
        ;

I       : Blq
            {
                $$.cod = $1.cod;
            }
        | let Ref asig E
            {
                if ($2.tipo != $4.tipo)
                {
                    if ($2.tipo == REAL && $4.tipo == ENTERO)
                    {
                        $$.cod = string($2.lexema) + " mov " + to_string($4.dir) + " A\n";   // mov E.dir A
                        $$.cod += "itor\n";                             // itor
                        $$.cod += "mov A " + to_string($2.dir) + "\n";  // mov A Ref.dir
                    }
                    else if ($2.tipo == ENTERO && $4.tipo == REAL)
                    {
                        $$.cod = "mov " + to_string($4.dir) + " A\n";   // mov E.dir A
                        $$.cod += "rtoi\n";                             // rtoi
                        $$.cod += "mov A " + to_string($2.dir) + "\n";  // mov A Ref.dir
                    }
                }
                else
                {
                    if ($4.isVar)
                    {
                        if ($4.isOp)
                        {
                            $$.cod = $4.cod;                                                        // E.cod
                            $$.cod += "mov A " + to_string($2.dir) + "\n";                          // mov E.id id
                        }
                        else
                        {
                            $$.cod = "mov " + to_string($4.dir) + " " + to_string($2.dir) + "\n";   // mov E.id id
                        }
                    }
                    else
                    {
                        if ($4.isOp)
                        {
                            $$.cod = $4.cod;                                                        // E.cod
                            $$.cod = "mov #" + $4.cod + " " + to_string($2.dir) + "\n";             // mov E.num id
                        }
                        else
                        {
                            $$.cod = "mov #" + $4.cod + " " + to_string($2.dir) + "\n";             // mov E.num id
                        }
                    }
                }
            }
        | var id IT
            {
                Simbolo newSymb;
                newSymb.nombre = $2.lexema;
                newSymb.tipo = $3.tipo;
                newSymb.dir = posMemoria;
                newSymb.tam = ($3.arrays ? $3.size : 1);


                if (!ts->newSymb(newSymb))
                {
                    errorSemantico(ERR_YADECL, $2.nlin, $2.ncol, $2.lexema);
                }

                if (posMemoria + newSymb.tam > MEM_VAR)
                {
                    errorSemantico(ERR_NOCABE, $2.nlin, $2.ncol, $2.lexema);
                }

                $$.cod = "mov #0 " + to_string(posMemoria) + "\n";     // mov #0 id

                posMemoria += newSymb.tam;
            }
        | print E
            {
                if ($2.isVar)
                {
                    $$.cod = "mov " + to_string($2.dir) + " A\n";   // mov E.id A
                }
                else
                {
                    if ($2.isOp)
                    {
                        $$.cod = $2.cod;                        // E.cod
                    }
                    else
                    {
                        if ($2.tipo == ENTERO)
                        {
                            $$.cod = "mov #" + $2.cod + " A\n";   // mov E.id A
                        }
                        else if ($2.tipo == REAL)
                        {
                            $$.cod = "mov $" + $2.cod + " A\n";   // mov E.id A
                        }
                    }
                }

                if ($2.tipo == ENTERO)
                {
                    $$.cod += "wri A\n";                        // wri A
                }
                else if ($2.tipo == REAL)
                {
                    $$.cod += "wrr A\n";                        // wrr B
                }

                $$.cod += "wrl\n";                              // wrl
            }
        | _read Ref
            {

            }
        | _while
            {
                numbloque++;
            }
             E I
            {
                numbloque--;

                string e1 = "E" + to_string(numEtiqueta);
                numEtiqueta++;
                string e2 = "E" + to_string(numEtiqueta);
                numEtiqueta++;

                $$.cod = e1 + ":\n";            // e1;
                $$.cod += $3.cod;               // E.cod
                $$.cod += "jz " + e2 + "\n";    // jz e2
                $$.cod += $4.cod;               // I.cod
                $$.cod += "jmp " + e1 + "\n";   // jmp e1
                $$.cod += e2 + ":\n";           // e2:
            }
        | loop
            {
                numbloque++;
            }
            id range Range I endloop
            {
                numbloque--;

                Simbolo* s = ts->searchSymb($3.lexema);
                if (s == NULL)
                {
                    // Error
                }

                string e1 = "E" + to_string(numEtiqueta);
                numEtiqueta++;
                string e2 = "E" + to_string(numEtiqueta);
                numEtiqueta++;

                $$.cod = string("mov #") + $5.r1 + " " + to_string(s->dir) + "\n";  // mov Range.r1 id.dir
                $$.cod += e1 + ":\n";                                               // e1:
                $$.cod += "mov " + to_string(s->dir) + " A\n";                      // mov id.dir A
                $$.cod += "muli #-1\n";                                             // muli #-1
                $$.cod += string("addi #") + $5.r2 + "\n";                          // addi Range.r2
                $$.cod += "jz " + e2 + "\n";                                        // jz e2
                $$.cod += $6.cod;                                                   // I
                $$.cod += "mov " + to_string(s->dir) + " A\n";                      // mov id.dir A
                $$.cod += "addi #1\n";                                              // addi #1
                $$.cod += "mov A " + to_string(s->dir) + "\n";                      // mov A id.dir
                $$.cod += "jmp " + e1 + "\n";                                       // jmp e1
                $$.cod += e2 + ":\n";                                               // e2:
            }
        | _if E I Ip
            {
                if ($2.tipo != ENTERO)
                {
                    errorSemantico(ERR_IFWHILE, $1.nlin, $1.ncol, "if");
                }
            }
        ;

Range   : numint dosp numint
            {
                $$.r1 = $1.lexema;
                $$.r2 = $3.lexema;
            }
        | numint
            {
                $$.r1 = "0";
                $$.r2 = $1.lexema;
            }
        ;

Blq     : blq
            {
                ts = new TablaSimbolos(ts);
                numbloque++;
                $$.cod = "";
            }
            fblq
            {
                TablaSimbolos* tmp = ts;
                ts = ts->getPadre();
                delete tmp;
                numbloque--;
            }
        | blq
            {
                ts = new TablaSimbolos(ts);
                numbloque++;
            }
            Cod fblq
            {
                $$.cod = $3.cod;
                TablaSimbolos* tmp = ts;
                ts = ts->getPadre();
                delete tmp;
                numbloque--;
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
        | /* empty */
            {

            }
        ;

IT      : dosp Type
            {
                // var id : tipo;
                $$.tipo = $2.tipo;
                $$.arrays = $2.arrays;
                $$.size = $2.size;
            }
        | /* Vacío */
            {
                // var id;  -> ENTERO implícito
                $$.tipo = ENTERO;
                $$.arrays = false;
                $$.size = 1;
            }
        ;

E       : E opas T
            {
                $$.isOp = true;

                if ($1.tipo == ENTERO && $3.tipo == ENTERO)
                {
                    $$.tipo = ENTERO;
                }
                else if ($1.tipo == REAL && $3.tipo == REAL)
                {
                    $$.tipo = REAL;
                }
                else if ($1.tipo == ENTERO && $3.tipo == REAL)
                {
                    $$.tipo = REAL;
                }
                else if ($1.tipo == REAL && $3.tipo == ENTERO)
                {
                    $$.tipo = REAL;
                }

                if ($1.isVar)
                {
                    $$.cod = "mov " + to_string($1.dir) + " A\n";    // mov E.dir A
                }
                else
                {
                    $$.cod = "mov #" + $1.cod + " A\n";              // mov E.cod A
                }

                if (strcmp($2.lexema, "+") == 0)
                {
                    if ($$.tipo == ENTERO)
                    {
                        if ($3.isVar)
                        {
                            $$.cod += "addi " + to_string($3.dir) + "\n";   // addi T.dir
                        }
                        else
                        {
                            $$.cod += "addi #" + $3.cod + "\n";             // addi T.cod
                        }
                    }
                    else
                    {
                       if ($3.isVar)
                       {
                           $$.cod += "addr " + to_string($3.dir) + "\n";   // addr T.dir
                       }
                       else
                       {
                           $$.cod += "addr #" + $3.cod + "\n";             // addr T.cod
                       }
                    }
                }
                else
                {
                    if ($$.tipo == ENTERO)
                    {
                        if ($3.isVar)
                        {
                            $$.cod += "subi " + to_string($3.dir) + "\n";   // subi T.dir
                        }
                        else
                        {
                            $$.cod += "subi #" + $3.cod + "\n";             // subi T.dir
                        }
                    }
                    else
                    {
                        if ($3.isVar)
                        {
                            $$.cod += "subr " + to_string($3.dir) + "\n";   // subr T.dir
                        }
                        else
                        {
                            $$.cod += "subr #" + $3.cod + "\n";             // subr T.dir
                        }
                    }
                }
            }
        | opas T
            {

            }
        | T
            {
                $$.isOp = $1.isOp;
                $$.tipo = $1.tipo;
                $$.dir = $1.dir;
                $$.isVar = $1.isVar;
                $$.cod = $1.cod;
            }
        ;

T       : T opmd F
            {
                $$.isOp = true;
                $1.isVar = false;

                if ($1.tipo == ENTERO && $3.tipo == ENTERO)
                {
                    $$.tipo = ENTERO;
                }
                else if ($1.tipo == REAL && $3.tipo == REAL)
                {
                    $$.tipo = REAL;
                }
                else if ($1.tipo == ENTERO && $3.tipo == REAL)
                {
                    $$.tipo = REAL;
                }
                else if ($1.tipo == REAL && $3.tipo == ENTERO)
                {
                    $$.tipo = REAL;
                }

                if ($1.isVar)
                {
                    $$.cod = "mov " + to_string($1.dir) + " A\n";    // mov E.dir A
                }
                else
                {
                    $$.cod = "mov #" + $1.cod + " A\n";              // mov E.cod A
                }

                if (strcmp($2.lexema, "*") == 0)
                {
                    if ($$.tipo == ENTERO)
                    {
                        if ($3.isVar)
                        {
                            $$.cod += "muli " + to_string($3.dir) + "\n";   // muli T.dir
                        }
                        else
                        {
                            $$.cod += "muli #" + $3.cod + "\n";             // muli T.cod
                        }
                    }
                    else
                    {
                        if ($3.isVar)
                        {
                            $$.cod += "mulr " + to_string($3.dir) + "\n";   // mulr T.dir
                        }
                        else
                        {
                            $$.cod += "mulr #" + $3.cod + "\n";             // mulr T.cod
                        }
                    }
                }
                else
                {
                    if ($$.tipo == ENTERO)
                    {
                        if ($3.isVar)
                        {
                            $$.cod += "subi " + to_string($3.dir) + "\n";   // divi T.dir
                        }
                        else
                        {
                            $$.cod += "subi #" + $3.cod + "\n";             // divi T.cod
                        }
                    }
                    else
                    {
                        if ($3.isVar)
                        {
                            $$.cod += "divr " + to_string($3.dir) + "\n";   // divr T.dir
                        }
                        else
                        {
                            $$.cod += "divr #" + $3.cod + "\n";             // divr T.cod
                        }
                    }
                }
            }
        | F
            {
                $$.tipo = $1.tipo;
                $$.dir = $1.dir;
                $$.isVar = $1.isVar;
                $$.cod = $1.cod;
            }
        ;

F       : numint
            {
                $$.tipo = ENTERO;
                $$.cod = $1.lexema;
            }
        | numreal
            {
                $$.tipo = REAL;
                $$.cod = $1.lexema;
            }
        | pari E pard
            {
                $$.cod = $2.cod;  // E.cod
            }
        | Ref
            {
                $$.tipo = $1.tipo;
                $$.dir = $1.dir;
                $$.isVar = $1.isVar;
                $$.cod = $1.cod;
            }
        ;

Ref     : id
            {
                Simbolo* s = ts->searchSymb($1.lexema);

                if (s != NULL)
                {
                    $$.tipo = s->tipo;
                    $$.dir = s->dir;
                    $$.isVar = true;
                    $$.cod = s->dir;
                }
                else
                {
                    errorSemantico(ERR_NODECL, $1.nlin, $1.ncol, $1.lexema);
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
    FILE *fent;

        if (argc == 2)
        {
            fent = fopen(argv[1], "rt");
            if (fent)
            {
                yyin = fent;
                yyparse();
                fclose(fent);
            }
            else
            {
                fprintf(stderr, "No puedo abrir el fichero\n");
            }
        }
        else
        {
            fprintf(stderr, "Uso: plp5 <nombre de fichero>\n");
        }

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
