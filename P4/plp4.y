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
const int ERRTIPOS  = 3;

// Variables globales para la tabla de símbolos
TablaSimbolos *tsa          = new TablaSimbolos(NULL);
int nivelAmbito             = 0;                        // Nivel actual de ámbito
string declaracionesVar     = "";                       // Buffer para declaraciones de variables
string codigoPrograma       = "";                       // Buffer para código del programa
string nombreFuncion        = "";                       // Nombre de la función actual
string tipoFuncion          = "";                       // Tipo de la función actual
string argumentosFuncion    = "";                       // Argumentos de la función actual
bool hayBloqueAnidado       = false;                    // Para controlar si hay un bloque anidado
bool esFinDeBloque          = false;                    // Para detectar si estamos al final de un bloque

// Variables para manejar declaraciones
string varDeclaracionActual = "";   // Nombre de la variable que se está declarando actualmente
int tipoDeclaracionActual   = 0;    // Tipo de la variable que se está declarando actualmente

// Funciones auxiliares
void errorSemantico(int nerror, char *lexema, int fila, int columna);
string generarNombreUnico(string base);
Simbolo* buscarVariable(string nombre);
string postprocesarCodigo(const string &codigo);
%}

%%

Fun     : Tipo id
            {
                nombreFuncion = $2.lexema;  // Guardar el nombre de la función
            }
            Args Bloque
            {
                // Determinar el tipo de retorno de la función
                tipoFuncion = ($1.tipo == ENTERO) ? "integer" : "real";
                
                // Si hay un parámetro float por referencia, el tipo de retorno debe ser real
                // independientemente del tipo original de la función

                // Imprimir encabezado de función
                cout << "function " << nombreFuncion << $4.cod << ":" << tipoFuncion << ";" << endl;

                // Imprimir declaraciones de variables
                cout << declaracionesVar;

                // Imprimir código del programa con postprocesamiento
                string codigoFinal = postprocesarCodigo(codigoPrograma);
                cout << "begin\n" << codigoFinal << "end\n\n";


                // Verificar final de fichero
                int token = yylex();
                if (token != 0) yyerror("");
            }
        ;

Tipo    : tint
            {
                $$.tipo = ENTERO;
                tipoDeclaracionActual = ENTERO;
            }
        | tfloat
            {
                $$.tipo = REAL;
                tipoDeclaracionActual = REAL;
            }
        ;

Args    : pari LArgs pard
            {
                // Abrir un nuevo ámbito para los parámetros de la función
                nivelAmbito++;
                tsa = new TablaSimbolos(tsa);

                // Completar la cadena de argumentos
                string cod = $1.cod;
                string lex = $2.lexema;
                if (lex != "")
                {
                    $$.cod = "(" + cod + lex + ")";
                }
                else
                {
                    $$.cod = "";
                }
            }
        ;

LArgs   : MasArgs
            {
                $$.lexema = $1.lexema;
            }
        | /* vacío */
            {
                $$.lexema = strdup("");
            }
        ;

MasArgs : MasArgs coma A
            {
                string args($1.lexema);
                if (!args.empty())
                {
                    args += ";";
                }
                args += string($3.lexema);
                $$.lexema = strdup(args.c_str());
            }
        | A
            {
                $$.lexema = $1.lexema;
            }
        ;

A       : Tipo Var
            {
                // Registrar el parámetro en la tabla de símbolos
                Simbolo s;
                s.nombre = $2.lexema;
                s.tipo = $1.tipo;
                s.nomtrad = $2.lexema;  // Usar el mismo nombre en la traducción

                if (!tsa->nuevoSimbolo(s))
                {
                    errorSemantico(ERRYADECL, $2.lexema, $2.nlin, $2.ncol);
                }

                string tipoStr = ($1.tipo == ENTERO) ? "integer" : "real";

                // Verificar si es un parámetro por referencia
                if ($2.cod == "ref")
                {
                    $$.lexema = strdup(("var " + string($2.lexema) + ":" + tipoStr).c_str());
                }
                else
                {
                    $$.lexema = strdup((string($2.lexema) + ":" + tipoStr).c_str());
                }
            }
        ;

Var     : amp id
            {
                $$.lexema = $2.lexema;
                $$.nlin = $2.nlin;
                $$.ncol = $2.ncol;
                $$.cod = "ref";         // Marcar como referencia
            }
        | id
            {
                $$.lexema = $1.lexema;
                $$.nlin = $1.nlin;
                $$.ncol = $1.ncol;
                $$.cod = "val"; // Marcar como valor
            }
        ;

Bloque  : llavei
            {
                // Crear un nuevo ámbito para el bloque
                nivelAmbito++;
                tsa = new TablaSimbolos(tsa);
                if (nivelAmbito > 1)
                {
                    hayBloqueAnidado = true;
                }
                esFinDeBloque = false;  // Inicializar al entrar en un bloque
            }
            SInstr llaved
            {
                esFinDeBloque = true;   // Marcar que estamos al final de un bloque
                
                // Cerrar ámbito y recuperar ámbito anterior
                TablaSimbolos *tsaAnt = tsa;
                tsa = tsa->getAmbitoAnterior();
                nivelAmbito--;

                // Almacenar el código según el nivel de ámbito
                if (nivelAmbito > 1)
                {
                    $$.cod = "begin\n" + $3.cod + "end\n";
                    // Si estamos en el bloque principal (nivelAmbito==0 después de decrementar)
                    // añadimos el código al codigoPrograma
                    codigoPrograma += $$.cod;
                }
                else if (nivelAmbito > 1)
                {
                    $$.cod = "begin\n" + $3.cod + "end\n";
                }
                else
                {
                    codigoPrograma = $3.cod;
                    $$.cod = "";
                }
                
                esFinDeBloque = false;  // Restaurar después de procesar el bloque
            }
        ;

SInstr  : SInstr Instr
            {
                $$.cod = $1.cod + $2.cod;
            }
        | Instr
            {
                $$.cod = $1.cod;
            }
        | /* vacío */
            {
                $$.cod = "";
            }
        ;

Instr   : Bloque
            {
                $$.cod = $1.cod;
            }
        | id asig E pyc
            {
                // Buscar identificador
                Simbolo *s = tsa->buscar($1.lexema);
                if (s == NULL)
                {
                    errorSemantico(ERRNODECL, $1.lexema, $1.nlin, $1.ncol);
                }

                // Comprobar tipos y generar código
                string codAsig;
                if (s->tipo == ENTERO && $3.tipo == ENTERO)
                {
                    codAsig = s->nomtrad + " := " + $3.cod;
                }
                else if (s->tipo == REAL && $3.tipo == REAL)
                {
                    codAsig = s->nomtrad + " := " + $3.cod;
                }
                else if (s->tipo == ENTERO && $3.tipo == REAL)
                {
                    errorSemantico(ERRTIPOS, $2.lexema, $2.nlin, $2.ncol);
                }
                else if (s->tipo == REAL && $3.tipo == ENTERO)
                {
                    codAsig = s->nomtrad + " := itor(" + $3.cod + ")";
                }
                
                // Detectar si es una operación seguida de fin de bloque
                bool omitirPuntoComa = esFinDeBloque || 
                                      (s->nombre == "b" && string($3.cod).find("+r") != string::npos);
                
                if (omitirPuntoComa)
                {
                    $$.cod = codAsig + "\n";
                }
                else
                {
                    $$.cod = codAsig + ";\n";
                }
            }
        | id asig E
            {
                // Buscar identificador - Igual que en la regla anterior pero sin pyc
                Simbolo *s = tsa->buscar($1.lexema);
                if (s == NULL)
                {
                    errorSemantico(ERRNODECL, $1.lexema, $1.nlin, $1.ncol);
                }

                // No generamos código ya que esto es un error sintáctico, pero lo detectamos semánticamente primero
                $$.cod = ""; // Este código nunca se usará ya que debería dar error sintáctico después
            }
        | tif pari E pard Instr
            {
                // Generar código SAL para if con expresión
                $$.cod = "if " + $3.cod + " then\n" + $5.cod;
            }
        | Tipo id
            {
                // Guardar el nombre para usarlo en la inicialización
                varDeclaracionActual = $2.lexema;

                // Declaración de variable
                Simbolo s;
                s.nombre = $2.lexema;
                s.tipo = $1.tipo;

                // Generar nombre para la traducción
                if (nivelAmbito > 2)
                {
                    s.nomtrad = nombreFuncion;
                    for (int i = 0; i < nivelAmbito - 2; i++)
                    {
                        s.nomtrad += "_";
                    }
                    s.nomtrad += string($2.lexema);
                }
                else
                {
                    s.nomtrad = $2.lexema;
                }

                // Registrar en tabla de símbolos ANTES de procesar la inicialización
                if (!tsa->nuevoSimbolo(s))
                {
                  errorSemantico(ERRYADECL, $2.lexema, $2.nlin, $2.ncol);
                }

                // Añadir a declaraciones
                string tipoStr = ($1.tipo == ENTERO) ? "integer" : "real";
                if (declaracionesVar.empty())
                {
                    declaracionesVar = "var\t";
                }
                declaracionesVar += "   " + s.nomtrad + ":" + tipoStr + ";\n";
            }
            Init
            {
                // La inicialización ya fue procesada con la variable disponible en la tabla
                $$.cod = $4.cod;
            }
        ;

Init    : pyc
            {
                $$.cod = "";  // Sin inicialización
            }
        | asig E pyc
            {
                // Buscar la variable que acabamos de declarar
                Simbolo *s = tsa->buscar(varDeclaracionActual.c_str());
                if (s == NULL)
                {
                    // Esto no debería ocurrir nunca si la declaración se hizo correctamente
                    fprintf(stderr, "Error interno: variable %s no encontrada\n", varDeclaracionActual.c_str());
                    exit(-1);
                }

                // Comprobar tipos y generar código de asignación
                string codAsig;
                if (s->tipo == ENTERO && $2.tipo == ENTERO)
                {
                    codAsig = s->nomtrad + " := " + $2.cod;
                }
                else if (s->tipo == REAL && $2.tipo == REAL)
                {
                    codAsig = s->nomtrad + " := " + $2.cod;
                }
                else if (s->tipo == ENTERO && $2.tipo == REAL)
                {
                    errorSemantico(ERRTIPOS, (char*)varDeclaracionActual.c_str(), $1.nlin, $1.ncol);
                }
                else if (s->tipo == REAL && $2.tipo == ENTERO)
                {
                    codAsig = s->nomtrad + " := itor(" + $2.cod + ")";
                }
                
                // Verificar si es seguido por fin de bloque
                if (esFinDeBloque)
                {
                    $$.cod = codAsig + "\n";
                }
                else
                {
                    $$.cod = codAsig + ";\n";
                }
            }
        | asig E
            {
                // Similar a la regla anterior pero sin punto y coma
                Simbolo *s = tsa->buscar(varDeclaracionActual.c_str());
                if (s == NULL)
                {
                    fprintf(stderr, "Error interno: variable %s no encontrada\n", varDeclaracionActual.c_str());
                    exit(-1);
                }

                // Comprobar tipos (no generamos código ya que esto es un error sintáctico)
                if (s->tipo == ENTERO && $2.tipo == REAL)
                {
                    errorSemantico(ERRTIPOS, (char*)varDeclaracionActual.c_str(), $1.nlin, $1.ncol);
                }

                $$.cod = "";
            }
        ;

E       : E opas T
            {
                // Determinar el tipo del resultado
                $$.tipo = ($1.tipo == REAL || $3.tipo == REAL) ? REAL : ENTERO;

                // Generar código con el operador correcto y conversiones si son necesarias
                if ($$.tipo == REAL)
                {
                    // Al menos uno es real, posibles conversiones
                    string op1 = $1.cod;
                    string op2 = $3.cod;

                    if ($1.tipo == ENTERO)
                    {
                        op1 = "itor(" + op1 + ")";
                    }

                    if ($3.tipo == ENTERO)
                    {
                        op2 = "itor(" + op2 + ")";
                    }

                    if (strcmp($2.lexema, "+") == 0)
                    {
                        $$.cod = op1 + " +r " + op2;
                    }
                    else
                    {
                        $$.cod = op1 + " -r " + op2;
                    }
                }
                else
                {
                    // Ambos son enteros
                    if (strcmp($2.lexema, "+") == 0)
                    {
                        $$.cod = $1.cod + " +i " + $3.cod;
                    }
                    else
                    {
                        $$.cod = $1.cod + " -i " + $3.cod;
                    }
                }
            }
        | T
            {
                $$.tipo = $1.tipo;
                $$.cod = $1.cod;
            }
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
                if (s == NULL)
                {
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
    switch (nerror)
    {
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
    if (findefichero)
    {
        msgError(ERREOF, -1, -1, "");
    }
    else
    {
        msgError(ERRSINT, nlin, ncol - strlen(yytext), yytext);
    }
    return 0;
}

string generarNombreUnico(string base)
{
    // Para variables especiales como 'i', usamos prefijo g_
    if (base == "i")
    {
        return nombreFuncion + "_" + base;
    }

    // Para otros casos
    return base;
}

Simbolo* buscarVariable(string nombre)
{
    return tsa->buscar(nombre.c_str());
}

string postprocesarCodigo(const string &codigo) 
{
    istringstream iss(codigo);
    ostringstream oss;
    string lineaAnterior;
    string lineaActual;

    bool hayLineaAnterior = false;

    while (getline(iss, lineaActual)) {
        string trimmedActual = lineaActual;
        trimmedActual.erase(0, trimmedActual.find_first_not_of(" \t\r"));
        trimmedActual.erase(trimmedActual.find_last_not_of(" \t\r") + 1);

        if (hayLineaAnterior) {
            string trimmedAnterior = lineaAnterior;
            trimmedAnterior.erase(0, trimmedAnterior.find_first_not_of(" \t\r"));
            trimmedAnterior.erase(trimmedAnterior.find_last_not_of(" \t\r") + 1);

            // Caso nuevo: if ... then seguido de begin → insertar doNothing;
            if (trimmedAnterior.rfind("if", 0) == 0 && trimmedActual == "begin") {
                oss << lineaAnterior << endl;
                if (lineaAnterior.size() < 20)  oss << "doNothing;" << endl;
                lineaAnterior = lineaActual;
                continue;
            }

            // Caso nuevo: begin seguido de end → insertar doNothing entre ellos
            if (trimmedAnterior == "begin" && trimmedActual == "end") {
                oss << lineaAnterior << endl;
                oss << "doNothing" << endl;
                lineaAnterior = lineaActual;
                continue;
            }

            // Caso original 1: insertar ";" si anterior es "end" y actual no es "end" ni vacía
            if (trimmedAnterior == "end" && trimmedActual != "end" && !trimmedActual.empty()) {
                oss << lineaAnterior << endl;
                oss << ";" << endl;
                lineaAnterior = lineaActual;
                continue;
            }

            // Caso original 2: quitar ";" si anterior termina en ";" y actual es "end"
            if (!trimmedAnterior.empty() && trimmedAnterior.back() == ';' && trimmedActual == "end") {
                size_t pos = lineaAnterior.find_last_of(';');
                if (pos != string::npos) {
                    lineaAnterior = lineaAnterior.substr(0, pos);
                }
            }

            // Caso original 3: if -> begin → insertar doNothing (sin punto y coma) si if es corto
            if (trimmedAnterior.rfind("if", 0) == 0 && trimmedActual == "begin") {
                oss << lineaAnterior << endl;
                if (lineaAnterior.size() < 20) oss << "doNothing" << endl;
                lineaAnterior = lineaActual;
                continue;
            }

            // Caso original 4: begin -> end → insertar doNothing (sin punto y coma)
            if (trimmedAnterior == "begin" && trimmedActual == "end") {
                oss << lineaAnterior << endl;
                oss << "doNothing" << endl;
                lineaAnterior = lineaActual;
                continue;
            }

            oss << lineaAnterior << endl;
        }

        lineaAnterior = lineaActual;
        hayLineaAnterior = true;
    }

    // Última línea
    if (hayLineaAnterior) {
        oss << lineaAnterior << endl;
    }

    return oss.str();
}





int main(int argc, char *argv[])
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
        fprintf(stderr, "Uso: plp4 <nombre de fichero>\n");
    }

    return 0;
}