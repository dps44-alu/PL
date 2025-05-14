%token tint tfloat tif
%token id numentero numreal
%token pari pard llavei llaved
%token pyc coma asig amp opas

%{
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

#include "comun.h"
#include "TablaSimbolos.h"

extern int yylex();
extern int nlin, ncol;
extern int findefichero;
extern char *yytext;
extern FILE *yyin;
int yyerror(char *s);

// Constantes para errores semánticos
const int ERRYADECL = 1;
const int ERRNODECL = 2;
const int ERRTIPOS = 3;

// Variables globales para la tabla de símbolos
TablaSimbolos *tsa = new TablaSimbolos(NULL);
string ambito;       // Para generar nombres únicos
int numVarTemp = 0;  // Contador para variables temporales

// Funciones auxiliares
void errorSemantico(int nerror, char *lexema, int fila, int columna);
string nuevaVar();
string generaCodigo(string op, int tipo1, string cod1, int tipo2, string cod2);
%}

%%

Fun     : Tipo id Args Bloque
          {
              // Verificar final de fichero
              int token = yylex();
              if (token != 0) yyerror("");
          }
        ;

Tipo    : tint    { $$.tipo = ENTERO; }
        | tfloat  { $$.tipo = REAL; }
        ;

Args    : pari LArgs pard
        ;

LArgs   : MasArgs
        |         /* vacío */
        ;

MasArgs : MasArgs coma A
        | A
        ;

A       : Tipo Var
        ;

Var     : amp id
        | id
        ;

Bloque  : llavei
          {
              // Abrir nuevo ámbito
              tsa = new TablaSimbolos(tsa);
          }
          SInstr llaved
          {
              // Cerrar ámbito
              tsa = tsa->getAmbitoAnterior();
          }
        ;

SInstr  : SInstr Instr
        | Instr
        ;

Instr   : Bloque
        | id asig E pyc
          {
              // Buscar identificador
              Simbolo *s = tsa->buscar($1.lexema);
              if (s == NULL) {
                  errorSemantico(ERRNODECL, $1.lexema, $1.nlin, $1.ncol);
              }

              // Comprobar tipos
              if (s->tipo != $3.tipo) {
                  if (s->tipo == ENTERO && $3.tipo == REAL) {
                      errorSemantico(ERRTIPOS, $1.lexema, $1.nlin, $1.ncol);
                  } else {
                      // Convertir entero a real
                      $$.cod = s->nomtrad + " = itor(" + $3.cod + ");\n";
                  }
              } else {
                  $$.cod = s->nomtrad + " = " + $3.cod + ";\n";
              }

              cout << $$.cod;
          }
        | tif pari E pard Instr
          {
              // Generación de código para if
              string etiq = nuevaVar();
              $$.cod = $3.cod + "\n" +
                     "if (" + $3.cod + " == 0) goto " + etiq + ";\n" +
                     $5.cod + "\n" +
                     etiq + ":;\n";
              cout << $$.cod;
          }
        | Tipo id Init
          {
              // Declaración de variable
              Simbolo s;
              s.nombre = $2.lexema;
              s.tipo = $1.tipo;
              s.nomtrad = ambito + $2.lexema;

              if (!tsa->nuevoSimbolo(s)) {
                  errorSemantico(ERRYADECL, $2.lexema, $2.nlin, $2.ncol);
              }

              if ($1.tipo == ENTERO) {
                  cout << "int " << s.nomtrad << ";\n";
              } else {
                  cout << "float " << s.nomtrad << ";\n";
              }

              if ($3.cod != "") {
                  cout << s.nomtrad << " = " << $3.cod << ";\n";
              }
          }
        ;

Init    : pyc
          {
              $$.cod = "";
          }
        | asig E pyc
          {
              $$.cod = $2.cod;
          }
        ;

E       : E opas T
          {
              $$.cod = generaCodigo($2.lexema, $1.tipo, $1.cod, $3.tipo, $3.cod);
              $$.tipo = ($1.tipo == REAL || $3.tipo == REAL) ? REAL : ENTERO;
          }
        | T
        ;

T       : numentero
          {
              $$.tipo = ENTERO;
              $$.cod = $1.lexema;
          }
        | numreal
          {
              $$.tipo = REAL;
              $$.cod = $1.lexema;
          }
        | id
          {
              Simbolo *s = tsa->buscar($1.lexema);
              if (s == NULL) {
                  errorSemantico(ERRNODECL, $1.lexema, $1.nlin, $1.ncol);
              }
              $$.tipo = s->tipo;
              $$.cod = s->nomtrad;
          }
        ;

%%

void errorSemantico(int nerror, char *lexema, int fila, int columna)
{
    fprintf(stderr, "Error semantico (%d,%d): '%s' ", fila, columna, lexema);
    switch (nerror) {
      case ERRYADECL: fprintf(stderr, "ya existe en este ambito\n");
         break;
      case ERRNODECL: fprintf(stderr, "no ha sido declarado\n");
         break;
      case ERRTIPOS: fprintf(stderr, "tipos incompatibles entero/real\n");
         break;
    }
    exit(-1);
}

void msgError(int nerror, int nlin, int ncol, const char *s)
{
    switch (nerror) {
        case ERRLEXICO: fprintf(stderr, "Error lexico (%d,%d): caracter '%s' incorrecto\n", nlin, ncol, s);
           break;
        case ERRSINT: fprintf(stderr, "Error sintactico (%d,%d): en '%s'\n", nlin, ncol, s);
           break;
        case ERREOF: fprintf(stderr, "Error sintactico: fin de fichero inesperado\n");
           break;
        case ERRLEXEOF: fprintf(stderr, "Error lexico: fin de fichero inesperado\n");
           break;
    }
    exit(1);
}

int yyerror(char *s)
{
    if (findefichero) {
        msgError(ERREOF, -1, -1, "");
    } else {
        msgError(ERRSINT, nlin, ncol - strlen(yytext), yytext);
    }
}

string nuevaVar()
{
    stringstream ss;
    ss << "temp" << numVarTemp++;
    return ss.str();
}

string generaCodigo(string op, int tipo1, string cod1, int tipo2, string cod2)
{
    string resultado = nuevaVar();
    string operacion;
    bool sonReales = (tipo1 == REAL || tipo2 == REAL);

    if (op == "+")
        operacion = "sum";
    else if (op == "-")
        operacion = "res";

    if (sonReales) {
        string s1 = (tipo1 == ENTERO) ? "itor(" + cod1 + ")" : cod1;
        string s2 = (tipo2 == ENTERO) ? "itor(" + cod2 + ")" : cod2;
        cout << "float " << resultado << " = " << operacion << "r(" << s1 << ", " << s2 << ");" << endl;
    } else {
        cout << "int " << resultado << " = " << operacion << "i(" << cod1 << ", " << cod2 << ");" << endl;
    }

    return resultado;
}

int main(int argc, char *argv[])
{
    FILE *fent;

    if (argc == 2) {
        fent = fopen(argv[1], "rt");
        if (fent) {
            yyin = fent;
            yyparse();
            fclose(fent);
        } else {
            fprintf(stderr, "No puedo abrir el fichero\n");
        }
    } else {
        fprintf(stderr, "Uso: plp4 <nombre de fichero>\n");
    }

    return 0;
}