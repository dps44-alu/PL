import java.io.IOException;

public class TraductorDR {
    private AnalizadorLexico lexico;
    private Token token;
    private TablaSimbolos tabla;
    private String nomFuncion;
    private int nivelAmbito;

    public TraductorDR(AnalizadorLexico lexico) {
        this.lexico = lexico;
        this.lexico.setSintactico(true);
        tabla = new TablaSimbolos(null);
        nivelAmbito = 0;
        try {
            token = lexico.siguienteToken();
        } catch (RuntimeException e) {
            errorSintactico();
        }
    }

    // Método para reportar errores sintácticos
    private void errorSintactico() {
        if (token.tipo == Token.EOF) {
            System.err.println("Error sintactico: encontrado fin de fichero, esperaba...");
        } else {
            System.err.printf("Error sintactico (%d,%d): encontrado '%s', esperaba...\n",
                    token.fila, token.columna, token.lexema);
        }
        System.exit(-1);
    }

    // Método para reportar errores semánticos
    private void errorSemantico(int tipo, String lexema, int fila, int columna) {
        switch (tipo) {
            case 1: // Identificador ya existe en este ámbito
                System.err.printf("Error semantico (%d,%d): '%s' ya existe en este ambito\n",
                        fila, columna, lexema);
                break;
            case 2: // Identificador no declarado
                System.err.printf("Error semantico (%d,%d): '%s' no ha sido declarado\n",
                        fila, columna, lexema);
                break;
            case 3: // Tipos incompatibles en asignación
                System.err.printf("Error semantico (%d,%d): '%s' tipos incompatibles entero/real\n",
                        fila, columna, lexema);
                break;
        }
        System.exit(-1);
    }

    // Sobrecarga para mantener compatibilidad con llamadas existentes
    private void errorSemantico(int tipo, String lexema) {
        // Ajustar la columna según el tipo de error
        int columnaAjustada;
        if (tipo == 1) {
            columnaAjustada = token.columna - 1;
        } else if (tipo == 2) {
            columnaAjustada = token.columna - 1;
        } else { // tipo == 3
            columnaAjustada = token.columna;
        }
        errorSemantico(tipo, lexema, token.fila, columnaAjustada);
    }

    // Método para emparejar tokens
    private void emparejar(int tipo) {
        if (token.tipo == tipo) {
            try {
                token = lexico.siguienteToken();
            } catch (RuntimeException e) {
                errorSintactico();
            }
        } else {
            errorSintactico();
        }
    }

    // Método para verificar fin de fichero
    public void comprobarFinFichero() {
        if (token.tipo != Token.EOF) {
            errorSintactico();
        }
    }

    // Clase para manejar múltiples atributos en las producciones
    private class Atributos {
        String trad;      // traducción
        String decl;      // declaraciones
        int tipo;         // tipo (ENTERO o REAL)
        int fila;         // fila del token
        int columna;      // columna del token

        public Atributos(String trad, String decl, int tipo) {
            this.trad = trad;
            this.decl = decl;
            this.tipo = tipo;
            this.fila = token.fila;
            this.columna = token.columna;
        }

        public Atributos(String trad, String decl, int tipo, int fila, int columna) {
            this.trad = trad;
            this.decl = decl;
            this.tipo = tipo;
            this.fila = fila;
            this.columna = columna;
        }
    }

    // Método para generar el nombre traducido de una variable en función del nivel de ámbito
    private String generarNombreTraducido(String id) {
        if (nivelAmbito == 0) {
            return id;
        }

        // Para variables en un ámbito interno, necesitamos usar el prefijo adecuado
        StringBuilder prefijo = new StringBuilder();

        // Para el primer nivel anidado, usamos el nombre de la función
        prefijo.append(nomFuncion);

        // Para cada nivel de anidamiento después del primero, añadimos un guion bajo
        for (int i = 1; i < nivelAmbito; i++) {
            prefijo.append("_");
        }

        return prefijo + id;
    }

    // Implementación de las producciones gramaticales
    // Fun -> Tipo id Args Bloque
    public String Fun() {
        Atributos tipo = Tipo();

        String id = token.lexema;
        nomFuncion = id;
        emparejar(Token.ID);

        Atributos args = Args();

        Atributos bloque = Bloque();

        // Construir el resultado final
        StringBuilder resultado = new StringBuilder();
        resultado.append("function ").append(id);

        // Si hay parámetros, añadirlos
        if (!args.trad.isEmpty()) {
            resultado.append("(").append(args.trad).append(")");
        }

        // Añadir el tipo de retorno
        resultado.append(":").append(tipo.tipo == Simbolo.ENTERO ? "integer" : "real").append(";\n");

        // Añadir las declaraciones si existen
        if (!args.decl.isEmpty() || !bloque.decl.isEmpty()) {
            resultado.append("var ");
            if (!args.decl.isEmpty()) {
                resultado.append(args.decl);
                if (!bloque.decl.isEmpty()) {
                    resultado.append(";\n");
                }
            }
            if (!bloque.decl.isEmpty()) {
                resultado.append(bloque.decl);
            }
            resultado.append(";\n");
        }

        // Añadir el begin-end con el código del bloque
        resultado.append("begin\n").append(bloque.trad);

        // Añadir el end final sin salto de línea adicional
        if (resultado.charAt(resultado.length() - 1) != '\n') {
            resultado.append("\n");
        }
        resultado.append("end");

        return resultado.toString();
    }

    // Tipo -> int | float
    private Atributos Tipo() {
        if (token.tipo == Token.INT) {
            emparejar(Token.INT);
            return new Atributos("integer", "", Simbolo.ENTERO);
        } else if (token.tipo == Token.FLOAT) {
            emparejar(Token.FLOAT);
            return new Atributos("real", "", Simbolo.REAL);
        } else {
            errorSintactico();
            return null;
        }
    }

    // Args -> pari LArgs pard
    private Atributos Args() {
        Atributos resultado = new Atributos("", "", 0);

        emparejar(Token.PARI);
        Atributos largs = LArgs();
        emparejar(Token.PARD);

        resultado.trad = largs.trad;
        resultado.decl = largs.decl;

        return resultado;
    }

    // LArgs -> A MasArgs | epsilon
    private Atributos LArgs() {
        Atributos resultado = new Atributos("", "", 0);

        if (token.tipo == Token.INT || token.tipo == Token.FLOAT) {
            Atributos a = A();
            Atributos masArgs = MasArgs();

            resultado.trad = a.trad;
            resultado.decl = a.decl;

            if (!masArgs.trad.isEmpty()) {
                resultado.trad += ";" + masArgs.trad;
            }

            if (!masArgs.decl.isEmpty()) {
                resultado.decl += ";\n" + masArgs.decl;
            }
        }
        // Si es epsilon, se devuelve un objeto Atributos vacío

        return resultado;
    }

    // MasArgs -> coma A MasArgs | epsilon
    private Atributos MasArgs() {
        Atributos resultado = new Atributos("", "", 0);

        if (token.tipo == Token.COMA) {
            emparejar(Token.COMA);
            Atributos a = A();
            Atributos masArgs = MasArgs();

            resultado.trad = a.trad;
            resultado.decl = a.decl;

            if (!masArgs.trad.isEmpty()) {
                resultado.trad += ";" + masArgs.trad;
            }

            if (!masArgs.decl.isEmpty()) {
                resultado.decl += ";\n" + masArgs.decl;
            }
        }
        // Si es epsilon, se devuelve un objeto Atributos vacío

        return resultado;
    }

    // A -> Tipo Var
    private Atributos A() {
        Atributos tipo = Tipo();
        Atributos var = Var();

        String tradTipo = (tipo.tipo == Simbolo.ENTERO ? "integer" : "real");

        // Combinar la traducción para un parámetro
        String trad = var.trad + ":" + tradTipo;

        // Guardar el parámetro en la tabla de símbolos
        if (!tabla.nuevoSimbolo(new Simbolo(var.decl, tipo.tipo, var.decl))) {
            errorSemantico(1, var.decl); // Error: identificador ya existe
        }

        return new Atributos(trad, "", tipo.tipo);
    }

    // Var -> amp id | id
    private Atributos Var() {
        boolean esReferencia = false;
        String id;
        String trad;

        if (token.tipo == Token.AMP) {
            esReferencia = true;
            emparejar(Token.AMP);
        }

        id = token.lexema;
        emparejar(Token.ID);

        // Generar la traducción
        trad = esReferencia ? "var " + id : id;

        return new Atributos(trad, id, 0);
    }

    // Bloque -> llavei SInstr llaved
    private Atributos Bloque() {
        TablaSimbolos tablaAnterior = tabla;
        tabla = new TablaSimbolos(tabla);
        nivelAmbito++;

        emparejar(Token.LLAVEI);
        Atributos sInstr = SInstr();
        emparejar(Token.LLAVED);

        tabla = tablaAnterior;
        nivelAmbito--;

        // Determinar el formato correcto para la traducción del bloque
        String trad;

        // Si estamos en ámbito principal y hay traducción
        if (nivelAmbito == 0 && !sInstr.trad.isEmpty()) {
            trad = sInstr.trad;
        }
        // Si estamos en un ámbito anidado o no hay traducción
        else {
            if (sInstr.trad.isEmpty()) {
                trad = "doNothing";
            } else {
                trad = sInstr.trad;
            }
        }

        return new Atributos(trad, sInstr.decl, 0);
    }

    // SInstr -> Instr SInstrp
    private Atributos SInstr() {
        Atributos instr = Instr();
        Atributos sInstrp = SInstrp();

        String trad = instr.trad;
        String decl = instr.decl;

        if (!sInstrp.trad.isEmpty()) {
            if (!trad.isEmpty()) {
                trad += ";\n" + sInstrp.trad;
            } else {
                trad = sInstrp.trad;
            }
        }

        if (!sInstrp.decl.isEmpty()) {
            if (!decl.isEmpty()) {
                decl += ";\n" + sInstrp.decl;
            } else {
                decl = sInstrp.decl;
            }
        }

        return new Atributos(trad, decl, 0);
    }

    // SInstrp -> Instr SInstrp | epsilon
    private Atributos SInstrp() {
        Atributos resultado = new Atributos("", "", 0);

        if (token.tipo == Token.LLAVEI || token.tipo == Token.ID ||
                token.tipo == Token.IF || token.tipo == Token.INT || token.tipo == Token.FLOAT) {

            Atributos instr = Instr();
            Atributos sInstrp = SInstrp();

            String trad = instr.trad;
            String decl = instr.decl;

            if (!sInstrp.trad.isEmpty()) {
                if (!trad.isEmpty()) {
                    trad += ";\n" + sInstrp.trad;
                } else {
                    trad = sInstrp.trad;
                }
            }

            if (!sInstrp.decl.isEmpty()) {
                if (!decl.isEmpty()) {
                    decl += ";\n" + sInstrp.decl;
                } else {
                    decl = sInstrp.decl;
                }
            }

            resultado.trad = trad;
            resultado.decl = decl;
        }
        // Si es epsilon, se devuelve un objeto Atributos vacío

        return resultado;
    }

    // Instr -> Bloque | id asig E pyc | if pari E pard Instr | Tipo id Init
    private Atributos Instr() {
        Atributos resultado = new Atributos("", "", 0);

        if (token.tipo == Token.LLAVEI) {
            Atributos bloque = Bloque();
            resultado.trad = "begin\n" + bloque.trad + "\nend";
            resultado.decl = bloque.decl;
        } else if (token.tipo == Token.ID) {
            String id = token.lexema;
            int idFila = token.fila;
            int idColumna = token.columna;
            emparejar(Token.ID);

            // Buscar el identificador en la tabla de símbolos
            Simbolo simbolo = tabla.buscar(id);
            if (simbolo == null) {
                errorSemantico(2, id, idFila, idColumna); // Error: identificador no declarado
            }

            emparejar(Token.ASIG);
            int asigFila = token.fila;
            int asigColumna = token.columna - 1;  // Guardamos la posición del '='
            Atributos e = E();
            emparejar(Token.PYC);

            // Comprobar compatibilidad de tipos
            if (simbolo.tipo == Simbolo.ENTERO && e.tipo == Simbolo.REAL) {
                errorSemantico(3, "=", asigFila, asigColumna); // Error: tipos incompatibles
            }

            // Generar la traducción de la asignación
            String expr = e.trad;
            if (simbolo.tipo == Simbolo.REAL && e.tipo == Simbolo.ENTERO) {
                expr = "itor(" + expr + ")";
            }

            resultado.trad = simbolo.trad + " := " + expr;
        } else if (token.tipo == Token.IF) {
            emparejar(Token.IF);
            emparejar(Token.PARI);
            Atributos e = E();
            emparejar(Token.PARD);
            Atributos instr = Instr();

            // Generar la traducción del if
            resultado.trad = "if " + e.trad + " then\n";

            if (instr.trad.isEmpty()) {
                resultado.trad += "doNothing";
            } else {
                resultado.trad += instr.trad;
            }

            resultado.decl = instr.decl;
        } else if (token.tipo == Token.INT || token.tipo == Token.FLOAT) {
            Atributos tipo = Tipo();

            String id = token.lexema;
            int idFila = token.fila;
            int idColumna = token.columna;
            emparejar(Token.ID);

            // Generar el nombre traducido para la tabla de símbolos
            String nombreTraducido = generarNombreTraducido(id);

            // Comprobar si ya existe en el ámbito actual
            if (!tabla.nuevoSimbolo(new Simbolo(id, tipo.tipo, nombreTraducido))) {
                errorSemantico(1, id, idFila, idColumna); // Error: identificador ya existe
            }

            // Añadir la declaración
            String tipoPascal = (tipo.tipo == Simbolo.ENTERO) ? "integer" : "real";
            resultado.decl = "   " + nombreTraducido + ":" + tipoPascal;

            Atributos init = Init();

            // Si hay inicialización, añadir la asignación
            if (!init.trad.isEmpty()) {
                if (tipo.tipo == Simbolo.ENTERO && init.tipo == Simbolo.REAL) {
                    errorSemantico(3, "=", init.fila, init.columna - 1); // Error: tipos incompatibles
                }

                String expr = init.trad;
                if (tipo.tipo == Simbolo.REAL && init.tipo == Simbolo.ENTERO) {
                    expr = "itor(" + expr + ")";
                }

                resultado.trad = nombreTraducido + " := " + expr;
            }
        } else {
            errorSintactico();
        }

        return resultado;
    }

    // Init -> pyc | asig E pyc
    private Atributos Init() {
        Atributos resultado = new Atributos("", "", 0);

        if (token.tipo == Token.PYC) {
            emparejar(Token.PYC);
        } else if (token.tipo == Token.ASIG) {
            int asigFila = token.fila;
            int asigColumna = token.columna;
            emparejar(Token.ASIG);
            Atributos e = E();
            emparejar(Token.PYC);

            resultado.trad = e.trad;
            resultado.tipo = e.tipo;
            resultado.fila = asigFila;
            resultado.columna = asigColumna;
        } else {
            errorSintactico();
        }

        return resultado;
    }

    // E -> T Ep
    private Atributos E() {
        Atributos t = T();
        Atributos ep = Ep(t);

        return new Atributos(ep.trad, "", ep.tipo, ep.fila, ep.columna);
    }

    // Ep -> opas T Ep | epsilon
    private Atributos Ep(Atributos heredado) {
        if (token.tipo == Token.OPAS) {
            String operador = token.lexema;
            int opasFila = token.fila;
            int opasColumna = token.columna;
            emparejar(Token.OPAS);
            Atributos t = T();

            // Determinar el tipo resultante y la traducción
            int tipoResultante;
            String traduccion;

            if (heredado.tipo == Simbolo.REAL || t.tipo == Simbolo.REAL) {
                tipoResultante = Simbolo.REAL;

                // Conversión de tipos si es necesario
                String izq = heredado.trad;
                String der = t.trad;

                if (heredado.tipo == Simbolo.ENTERO) {
                    izq = "itor(" + izq + ")";
                }

                if (t.tipo == Simbolo.ENTERO) {
                    der = "itor(" + der + ")";
                }

                traduccion = izq + " " + operador + "r " + der;
            } else {
                tipoResultante = Simbolo.ENTERO;
                traduccion = heredado.trad + " " + operador + "i " + t.trad;
            }

            Atributos resultado = new Atributos(traduccion, "", tipoResultante, opasFila, opasColumna);
            Atributos epPrima = Ep(resultado);
            return epPrima;
        }
        // Si es epsilon, se devuelve el atributo heredado
        return heredado;
    }

    // T -> numentero | numreal | id
    private Atributos T() {
        Atributos resultado;

        if (token.tipo == Token.ENTERO) {
            int enteroFila = token.fila;
            int enteroColumna = token.columna;
            String valor = token.lexema;
            emparejar(Token.ENTERO);
            resultado = new Atributos(valor, "", Simbolo.ENTERO, enteroFila, enteroColumna);
        } else if (token.tipo == Token.REAL) {
            int realFila = token.fila;
            int realColumna = token.columna;
            String valor = token.lexema;
            emparejar(Token.REAL);
            resultado = new Atributos(valor, "", Simbolo.REAL, realFila, realColumna);
        } else if (token.tipo == Token.ID) {
            String id = token.lexema;
            int idFila = token.fila;
            int idColumna = token.columna;

            // Buscar el identificador en la tabla de símbolos
            Simbolo simbolo = tabla.buscar(id);
            if (simbolo == null) {
                errorSemantico(2, id, idFila, idColumna); // Error: identificador no declarado
            }

            emparejar(Token.ID);
            resultado = new Atributos(simbolo.trad, "", simbolo.tipo, idFila, idColumna);
        } else {
            errorSintactico();
            resultado = new Atributos("", "", 0);  // Nunca se ejecutará este código pero el compilador lo necesita
        }

        return resultado;
    }
}