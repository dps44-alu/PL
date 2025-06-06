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
#include "TablaTipos.h"
#include "plp5.tab.h"

int ncol = 1;
int nlin = 1;
int findefichero = 0;

int     ret         (int token);
void    msgError    (int nerror, int nlin, int ncol, const char *s);

%}

%x COMENTARIO

%%

"//"(.)*                    { ; /* Comentarios de una línea */          }
"/*"                        { BEGIN(COMENTARIO);                        }
<COMENTARIO>[^*\n]*         { ncol += strlen(yytext);                   }
<COMENTARIO>"*"+[^*/\n]*    { ncol += strlen(yytext);                   }
<COMENTARIO>\n              { nlin++; ncol=1;                           }
<COMENTARIO>"*"+"/"         { BEGIN(INITIAL); ncol += strlen(yytext);   }

" "                 { ncol++; }
[\n]                { nlin++; ncol=1; }
[\t]                { ncol++; }
"fn"                { return ret(fn);       }
"endfn"             { return ret(endfn);    }
"int"               { return ret(_int);     }
"real"              { return ret(real);     }
"array"             { return ret(array);    }
"blq"               { return ret(blq);      }
"fblq"              { return ret(fblq);     }
"let"               { return ret(let);      }
"var"               { return ret(var);      }
"print"             { return ret(print);    }
"read"              { return ret(_read);    }
"if"                { return ret(_if);      }
"else"              { return ret(_else);    }
"elif"              { return ret(elif);    }
"fi"                { return ret(fi);       }
"while"             { return ret(_while);   }
"loop"              { return ret(loop);     }
"range"             { return ret(range);    }
"endloop"           { return ret(endloop);  }

{L}({LD})*          { return ret(id);       }
{D}+                { return ret(numint);   }
{D}+\.{D}+          { return ret(numreal);  }

","                 { return ret(coma);     }
";"                 { return ret(pyc);      }
":"                 { return ret(dosp);     }
"("                 { return ret(pari);     }
")"                 { return ret(pard);     }
"+"                 { return ret(opas);     }
"-"                 { return ret(opas);     }
"*"                 { return ret(opmd);     }
"/"                 { return ret(opmd);     }
"="                 { return ret(asig);     }
"["                 { return ret(cori);     }
"]"                 { return ret(cord);     }

.                   { msgError(ERRLEXICO, nlin, ncol, yytext); }

%%

int yywrap(void) { findefichero=1; return 1; }

int ret (int token)
{
   yylval.lexema = strdup(yytext);
   yylval.nlin = nlin;
   yylval.ncol = ncol;
   ncol += strlen(yytext);
   return token;
}