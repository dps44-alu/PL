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
int posTemporal = MEM_VAR;        // memoria de temporales

int nuevoTemp(int fila, int col)
{
    if (posTemporal >= MEM_TOTAL)
        errorSemantico(ERR_MAXTEMP, fila, col, "");
    return posTemporal++;
}

void liberaTemp()
{
    // Temporals are not reused to avoid overwriting active values
}

size_t dimEsperadas = 0;        // numero de dimensiones esperadas en una referencia
size_t dimActual = 0;           // contador de indices leidos
bool suprimirNodecl = false;    // para ignorar ERR_NODECL en indices sobrantes
Simbolo* simboloActual = NULL;   // simbolo de la referencia de array actual

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
                $$.dims.clear();
            }
        | array SType Dim
            {
                $$.tipo = $2.tipo;
                $$.size = $3.size;
                $$.arrays = true;
                $$.dims = $3.dims;
            }
        ;

Dim     : numint coma Dim
            {
                if (atoi($1.lexema) <= 0)
                    errorSemantico(ERR_DIM, $1.nlin, $1.ncol, $1.lexema);
                $$.size = atoi($1.lexema) * $3.size;
                $$.dims.push_back(atoi($1.lexema));
                $$.dims.insert($$.dims.end(), $3.dims.begin(), $3.dims.end());
            }
        | numint
            {
                if (atoi($1.lexema) <= 0)
                    errorSemantico(ERR_DIM, $1.nlin, $1.ncol, $1.lexema);
                $$.size = atoi($1.lexema);
                $$.dims.clear();
                $$.dims.push_back(atoi($1.lexema));
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
                auto cargaExpr = [&]() -> string {
                    if ($4.isOp)
                        return $4.cod;
                    else if ($4.isVar)
                    {
                        if ($4.isAddr)
                            return string("mov ") + to_string($4.dir) + " A\nmov @A A\n";
                        else
                            return string("mov ") + to_string($4.dir) + " A\n";
                    }
                    else
                        return string("mov ") + ($4.tipo==ENTERO?"#":"$") + $4.cod + " A\n";
                };

                string cod = $2.cod + cargaExpr();

                if ($2.tipo != $4.tipo)
                {
                    if ($2.tipo == REAL && $4.tipo == ENTERO)
                    {
                        cod += "itor\n";
                    }
                    else if ($2.tipo == ENTERO && $4.tipo == REAL)
                    {
                        errorSemantico(ERR_ASIG, $3.nlin, $3.ncol, "=");
                    }
                }

                if ($2.isAddr)
                {
                    cod += "mov A B\n";
                    cod += "mov " + to_string($2.dir) + " A\n";
                    cod += "mov B @A\n";
                    liberaTemp();
                }
                else
                {
                    cod += "mov A " + to_string($2.dir) + "\n";
                }

                if ($4.isVar && $4.isAddr)
                    liberaTemp();

                $$.cod = cod;
            }
        | var id IT
            {
                Simbolo newSymb;
                newSymb.nombre = $2.lexema;
                newSymb.tipo = $3.tipo;
                newSymb.dir = posMemoria;
                newSymb.tam = ($3.arrays ? $3.size : 1);
                newSymb.dims = $3.dims;


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
                string cod = $2.cod;

                if ($2.tipo == ENTERO)
                    cod += "rdi A\n";
                else
                    cod += "rdr A\n";

                if ($2.isAddr)
                {
                    cod += "mov A B\n";
                    cod += "mov " + to_string($2.dir) + " A\n";
                    cod += "mov B @A\n";
                    liberaTemp();
                }
                else
                {
                    cod += "mov A " + to_string($2.dir) + "\n";
                }

                $$.cod = cod;
            }
        | _while
            {
                numbloque++;
            }
             E I
            {
                numbloque--;

                string e1 = "L" + to_string(numEtiqueta);
                numEtiqueta++;
                string e2 = "L" + to_string(numEtiqueta);
                numEtiqueta++;

                $$.cod = e1 + "\n";            // e1;
                $$.cod += $3.cod;               // E.cod
                $$.cod += "jz " + e2 + "\n";    // jz e2
                $$.cod += $4.cod;               // I.cod
                $$.cod += "jmp " + e1 + "\n";   // jmp e1
                $$.cod += e2 + "\n";           // e2:
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
                    errorSemantico(ERR_NODECL, $3.nlin, $3.ncol, $3.lexema);
                }
                else if (s->tipo != ENTERO)
                {
                    errorSemantico(ERR_LOOP, $1.nlin, $1.ncol, "loop");
                }

                int inicio = atoi($5.r1);
                int fin    = atoi($5.r2);

                string e1 = "L" + to_string(numEtiqueta++);
                string e2 = "L" + to_string(numEtiqueta++);

                $$.cod = string("mov #") + $5.r1 + " " + to_string(s->dir) + "\n";  // mov Range.r1 id.dir
                $$.cod += e1 + "\n";   // e1:
                $$.cod += "mov " + to_string(s->dir) + " A\n";    // mov id.dir A
                if (inicio <= fin)
                    $$.cod += string("leqi #") + $5.r2 + "\n";   // comprobar id <= fin
                else
                    $$.cod += string("geqi #") + $5.r2 + "\n";   // comprobar id >= fin
                $$.cod += "jz " + e2 + "\n";    // jz e2 si condicion falsa
                $$.cod += $6.cod;    // I
                $$.cod += "mov " + to_string(s->dir) + " A\n";    // mov id.dir A
                if (inicio <= fin)
                    $$.cod += "addi #1\n";    // addi #1
                else
                    $$.cod += "subi #1\n";    // subi #1
                $$.cod += "mov A " + to_string(s->dir) + "\n";    // mov A id.dir
                $$.cod += "jmp " + e1 + "\n";    // jmp e1
                $$.cod += e2 + "\n";   // e2:
            }
        | _if E I Ip
            {
                if ($2.tipo != ENTERO)
                {
                    errorSemantico(ERR_IFWHILE, $1.nlin, $1.ncol, "if");
                }

                string e1 = "L" + to_string(numEtiqueta++);
                string e2 = "L" + to_string(numEtiqueta++);

                string cond;
                if ($2.isVar)
                {
                    cond = "mov " + to_string($2.dir) + " A\n";
                }
                else if ($2.isOp)
                {
                    cond = $2.cod;
                }
                else
                {
                    cond = string("mov ") + ($2.tipo==ENTERO?"#":"$") + $2.cod + " A\n";
                }

                $$.cod = cond;
                $$.cod += "jz " + e1 + "\n";
                $$.cod += $3.cod;
                $$.cod += "jmp " + e2 + "\n";
                $$.cod += e1 + "\n";
                $$.cod += $4.cod;
                $$.cod += e2 + "\n";
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
                $$.cod = $2.cod;      // else branch
            }
        | elif E I Ip
            {
                string e1 = "L" + to_string(numEtiqueta++);
                string e2 = "L" + to_string(numEtiqueta++);

                string cond;
                if ($2.isVar)
                {
                    cond = "mov " + to_string($2.dir) + " A\n";
                }
                else if ($2.isOp)
                {
                    cond = $2.cod;
                }
                else
                {
                    cond = string("mov ") + ($2.tipo==ENTERO?"#":"$") + $2.cod + " A\n";
                }

                $$.cod = cond;
                $$.cod += "jz " + e1 + "\n";
                $$.cod += $3.cod;
                $$.cod += "jmp " + e2 + "\n";
                $$.cod += e1 + "\n";
                $$.cod += $4.cod;
                $$.cod += e2 + "\n";
            }
        | fi
            {
                $$.cod = "";
            }
        | /* empty */
            {
                $$.cod = "";
            }
        ;

IT      : dosp Type
            {
                // var id : tipo;
                $$.tipo = $2.tipo;
                $$.arrays = $2.arrays;
                $$.size = $2.size;
                $$.dims = $2.dims;
            }
        | /* Vacío */
            {
                // var id;  -> ENTERO implícito
                $$.tipo = ENTERO;
                $$.arrays = false;
                $$.size = 1;
                $$.dims.clear();
            }
        ;

E       : E opas T
            {
                $$.isOp = true;

                if ($1.tipo == REAL || $3.tipo == REAL)
                    $$.tipo = REAL;
                else
                    $$.tipo = ENTERO;

                string codigo;

                if ($1.isOp)
                    codigo = $1.cod;
                else if ($1.isVar)
                {
                    codigo = $1.cod;
                    codigo += "mov " + to_string($1.dir) + " A\n";
                    if ($1.isAddr)
                    {
                        codigo += "mov @A A\n";
                        liberaTemp();
                    }
                }
                else
                    codigo = string("mov ") + ($1.tipo==ENTERO?"#":"$") + $1.cod + " A\n";

                if ($3.isOp)
                {
                    int t = nuevoTemp($2.nlin, $2.ncol);
                    codigo += "mov A " + to_string(t) + "\n";
                    codigo += $3.cod;
                    string op = strcmp($2.lexema, "+")==0 ? ( $$.tipo==ENTERO?"addi ":"addr ")
                                                         : ( $$.tipo==ENTERO?"subi ":"subr ");
                    codigo += op + to_string(t) + "\n";
                    liberaTemp();
                }
                else if ($3.isVar)
                {
                    string op = strcmp($2.lexema, "+")==0 ? ( $$.tipo==ENTERO?"addi ":"addr ")
                                                         : ( $$.tipo==ENTERO?"subi ":"subr ");
                    if ($3.isAddr)
                    {
                        int t2 = nuevoTemp($2.nlin, $2.ncol);
                        codigo += "mov A " + to_string(t2) + "\n";  // guardar operando izquierdo
                        codigo += $3.cod;
                        codigo += "mov " + to_string($3.dir) + " A\n";
                        codigo += "mov @A A\n";
                        codigo += op + to_string(t2) + "\n";
                        liberaTemp();
                        liberaTemp();
                    }
                    else
                    {
                        codigo += op + to_string($3.dir) + "\n";
                    }
                }
                else
                {
                    string op = strcmp($2.lexema, "+")==0 ? ( $$.tipo==ENTERO?"addi ":"addr ")
                                                         : ( $$.tipo==ENTERO?"subi ":"subr ");
                    codigo += op + string(($3.tipo==ENTERO?"#":"$") ) + $3.cod + "\n";
                }

                $$.cod = codigo;
            }
        | opas T
            {
                $$.isOp = true;
                $$.tipo = $2.tipo;

                string codigo;
                if ($2.isOp)
                    codigo = $2.cod;
                else if ($2.isVar)
                {
                    codigo = $2.cod;
                    codigo += "mov " + to_string($2.dir) + " A\n";
                    if ($2.isAddr)
                    {
                        codigo += "mov @A A\n";
                        liberaTemp();
                    }
                }
                else
                    codigo = string("mov ") + ($2.tipo==ENTERO?"#":"$") + $2.cod + " A\n";

                if (strcmp($1.lexema, "-") == 0)
                {
                    codigo += ($$.tipo==ENTERO?"muli #-1\n":"mulr #-1\n");
                }

                $$.cod = codigo;
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

                if ($1.tipo == REAL || $3.tipo == REAL)
                    $$.tipo = REAL;
                else
                    $$.tipo = ENTERO;

                string codigo;
                if ($1.isOp)
                    codigo = $1.cod;
                else if ($1.isVar)
                {
                    codigo = $1.cod;
                    codigo += "mov " + to_string($1.dir) + " A\n";
                    if ($1.isAddr)
                        codigo += "mov @A A\n";
                }
                else
                    codigo = string("mov ") + ($1.tipo==ENTERO?"#":"$") + $1.cod + " A\n";

                if ($3.isOp)
                {
                    int t = nuevoTemp($2.nlin, $2.ncol);
                    codigo += "mov A " + to_string(t) + "\n";
                    codigo += $3.cod;
                    string op = strcmp($2.lexema, "*")==0 ? ( $$.tipo==ENTERO?"muli ":"mulr ")
                                                         : ( $$.tipo==ENTERO?"divi ":"divr ");
                    codigo += op + to_string(t) + "\n";
                    liberaTemp();
                }
                else if ($3.isVar)
                {
                    string op = strcmp($2.lexema, "*")==0 ? ( $$.tipo==ENTERO?"muli ":"mulr ")
                                                         : ( $$.tipo==ENTERO?"divi ":"divr ");
                    if ($3.isAddr)
                    {
                        int t2 = nuevoTemp($2.nlin, $2.ncol);
                        codigo += "mov A " + to_string(t2) + "\n";  // guardar operando izquierdo
                        codigo += $3.cod;
                        codigo += "mov " + to_string($3.dir) + " A\n";
                        codigo += "mov @A A\n";
                        codigo += op + to_string(t2) + "\n";
                        liberaTemp();
                    }
                    else
                    {
                        codigo += op + to_string($3.dir) + "\n";
                    }
                }
                else
                {
                    string op = strcmp($2.lexema, "*")==0 ? ( $$.tipo==ENTERO?"muli ":"mulr ")
                                                         : ( $$.tipo==ENTERO?"divi ":"divr ");
                    codigo += op + string(($3.tipo==ENTERO?"#":"$") ) + $3.cod + "\n";
                }

                $$.cod = codigo;
                $$.isVar = false;
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
                $$.isVar = false;
                $$.isOp = false;
                $$.isAddr = false;
            }
        | numreal
            {
                $$.tipo = REAL;
                $$.cod = $1.lexema;
                $$.isVar = false;
                $$.isOp = false;
                $$.isAddr = false;
            }
        | pari E pard
            {
                $$.tipo = $2.tipo;
                $$.cod = $2.cod;  // E.cod
                $$.isVar = false;
                $$.isOp = true;
                $$.isAddr = false;
            }
        | Ref
            {
                $$.tipo = $1.tipo;
                $$.dir = $1.dir;
                $$.isVar = $1.isVar;
                $$.cod = $1.cod;
                $$.isOp = false;
                $$.isAddr = $1.isAddr;
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
                    $$.cod = "";         // sin codigo extra por referencia simple
                    $$.dims = s->dims;
                    $$.isAddr = false;
                }
                else
                {
                    if (!suprimirNodecl)
                        errorSemantico(ERR_NODECL, $1.nlin, $1.ncol, $1.lexema);
                    $$.tipo = ENTERO;
                    $$.dir = 0;
                    $$.isVar = false;
                    $$.isAddr = false;
                }
            }
        | id {
                simboloActual = ts->searchSymb($1.lexema);
                if (simboloActual == NULL)
                    errorSemantico(ERR_NODECL, $1.nlin, $1.ncol, $1.lexema);
                dimEsperadas = simboloActual->dims.size();
                dimActual = 0;
                suprimirNodecl = false;
            } cori LExpr cord
            {
                Simbolo* s = simboloActual;
                suprimirNodecl = false;

                if (s->dims.empty())
                {
                    errorSemantico(ERR_SOBRAN, $3.nlin, $3.ncol, $1.lexema);
                }

                if ($4.nindices < s->dims.size())
                {
                    errorSemantico(ERR_FALTAN, $5.nlin, $5.ncol, $1.lexema);
                }
                if ($4.nindices > s->dims.size())
                {
                    size_t pos = s->dims.size();
                    auto p = (pos == 0) ? make_pair($3.nlin, $3.ncol) : $4.comaPos[pos-1];
                    errorSemantico(ERR_SOBRAN, p.first, p.second, $1.lexema);
                }

                for (size_t i = 0; i < $4.nindices; ++i)
                {
                    if ($4.tiposIndices[i] != ENTERO)
                    {
                        if (i == 0)
                            errorSemantico(ERR_INDICE_ENTERO, $3.nlin, $3.ncol, $1.lexema);
                        else
                        {
                            auto p = $4.comaPos[i-1];
                            errorSemantico(ERR_INDICE_ENTERO, p.first, p.second, $1.lexema);
                        }
                    }
                }

                $$.tipo = s->tipo;
                $$.isVar = true;
                $$.dir = $4.dir;
                $$.cod = $4.cod;
                $$.cod += string("mov #") + to_string(s->dir) + " A\n";
                $$.cod += "addi " + to_string($4.dir) + "\n";
                $$.cod += "mov A " + to_string($4.dir) + "\n";
                $$.isAddr = true;
            }
        ;

LExpr   : LExpr coma
            {
                dimActual++;
                if (dimActual > dimEsperadas) suprimirNodecl = true;
            }
            E
            {
                suprimirNodecl = false;
                $$.nindices = $1.nindices + 1;
                $$.tiposIndices = $1.tiposIndices;
                $$.tiposIndices.push_back($4.tipo);
                $$.comaPos = $1.comaPos;
                $$.comaPos.push_back(make_pair($2.nlin, $2.ncol));
                int factor = 1;
                for (size_t j = dimActual; j < simboloActual->dims.size(); ++j)
                    factor *= simboloActual->dims[j];

                string codigo = $1.cod;
                if ($4.isOp)
                    codigo += $4.cod;
                else if ($4.isVar)
                    codigo += "mov " + to_string($4.dir) + " A\n";
                else
                    codigo += string("mov ") + ($4.tipo==ENTERO?"#":"$") + $4.cod + " A\n";

                if (factor != 1)
                    codigo += "muli #" + to_string(factor) + "\n";
                codigo += "addi " + to_string($1.dir) + "\n";
                codigo += "mov A " + to_string($1.dir) + "\n";

                $$.cod = codigo;
                $$.dir = $1.dir;
            }
        |
            {
                dimActual++;
                if (dimActual > dimEsperadas) suprimirNodecl = true;
            }
            E
            {
                suprimirNodecl = false;
                $$.nindices = 1;
                $$.tiposIndices.clear();
                $$.tiposIndices.push_back($2.tipo);
                $$.comaPos.clear();
                int factor = 1;
                for (size_t j = dimActual; j < simboloActual->dims.size(); ++j)
                    factor *= simboloActual->dims[j];

                int t = nuevoTemp($2.nlin, $2.ncol);
                string codigo;
                if ($2.isOp)
                    codigo = $2.cod;
                else if ($2.isVar)
                    codigo = "mov " + to_string($2.dir) + " A\n";
                else
                    codigo = string("mov ") + ($2.tipo==ENTERO?"#":"$") + $2.cod + " A\n";

                if (factor != 1)
                    codigo += "muli #" + to_string(factor) + "\n";
                codigo += "mov A " + to_string(t) + "\n";

                $$.cod = codigo;
                $$.dir = t;
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
