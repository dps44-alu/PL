D    [0-9]
L    [a-zA-Z]
LD   [0-9a-zA-Z]

%{
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

#include "comun.h"
#include "TablaSimbolos.h"
#include "plp4.tab.h"

int ncol = 1;
int nlin = 1;
int findefichero = 0;

int ret(int token);
%}

%x COMENTARIO

%%

[ \t]              { ncol++; }
[\n]               { nlin++; ncol=1; }
"//"(.)*           { ; /* comentarios de una linea */ }

"int"              { return ret(tint); }
"float"            { return ret(tfloat); }
"if"               { return ret(tif); }

"("                { return ret(pari); }
")"                { return ret(pard); }
"{"                { return ret(llavei); }
"}"                { return ret(llaved); }
";"                { return ret(pyc); }
","                { return ret(coma); }
"="                { return ret(asig); }
"&"                { return ret(amp); }
"+"                { return ret(opas); }
"-"                { return ret(opas); }

{D}+               { return ret(numentero); }
{D}+\.{D}+         { return ret(numreal); }
{L}({LD})*         { return ret(id); }

.                  { msgError(ERRLEXICO, nlin, ncol, yytext); }

%%

int yywrap(void) { findefichero=1; return 1; }

int ret(int token)
{
   yylval.lexema = strdup(yytext);
   yylval.nlin = nlin;
   yylval.ncol = ncol;
   ncol += strlen(yytext);
   return token;
}