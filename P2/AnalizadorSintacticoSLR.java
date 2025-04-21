import java.util.*;
import java.util.AbstractMap.SimpleEntry;

public class AnalizadorSintacticoSLR {
    //////////////////////////////////////////////////////////////////////
    // ATRIBUTOS PRIVADOS
    //////////////////////////////////////////////////////////////////////
    AnalizadorLexico al;                                    // AnalizadorLéxico para obtener los tokens
    boolean show;                                           // Flag para inidicar si mostrar o no la solución
    List<Integer> sol;                                      // String que guarda la solución a mostrar
    Stack<Integer> pila;                                    // Solución de que reglas se han aplicado (push añade arriba, pop eliminar arriba)
    Queue<Token> tokens;                                    // Estructura que alamacena los tokens
    List<List<SimpleEntry<Character, Integer>>> accion;     // Tabla Acción
    List<List<Integer>> ir_a;                               // Tabla Ir_A
    List<SimpleEntry<String, List<String>>> reglas;         // Tabla Reglas (key -> primero, value -> segundo)


    //////////////////////////////////////////////////////////////////////
    // CONTRUCTORES
    //////////////////////////////////////////////////////////////////////
    public AnalizadorSintacticoSLR (AnalizadorLexico lexico)
    {
        show = true;
        sol = new ArrayList<>();
        pila = new Stack<>();
        al = lexico;
        al.setSintactico(true);
        tokens = new LinkedList<>();

        // Tabla Acción
        crearTablaAccion();

        // Tabla Ir_A
        crearTablaIr_A();

        // Tabla Reglas
        crearTablaReglas();
    }


    //////////////////////////////////////////////////////////////////////
    // FUNCIONES PRIVADAS
    //////////////////////////////////////////////////////////////////////

    private void crearTablaAccion ()
    {
        accion = new ArrayList<>(33);

        for (int i = 0; i < 33; i++) {
            accion.add(new ArrayList<>(14));
            for (int j = 0; j < 14; j++) {
                accion.get(i).add(null);
            }
        }

        accion.get(0).set(Token.INT, new SimpleEntry<>('d', 3));
        accion.get(0).set(Token.FLOAT, new SimpleEntry<>('d', 4));

        accion.get(1).set(Token.EOF, new SimpleEntry<>('a', -1));

        accion.get(2).set(Token.ID, new SimpleEntry<>('d', 5));

        accion.get(3).set(Token.ID, new SimpleEntry<>('r', 2));

        accion.get(4).set(Token.ID, new SimpleEntry<>('r', 3));

        accion.get(5).set(Token.PARI, new SimpleEntry<>('d', 6));

        accion.get(6).set(Token.PARD, new SimpleEntry<>('d', 7));

        accion.get(7).set(Token.LLAVEI, new SimpleEntry<>('d', 9));

        accion.get(8).set(Token.EOF, new SimpleEntry<>('r', 1));

        accion.get(9).set(Token.INT, new SimpleEntry<>('d', 3));
        accion.get(9).set(Token.FLOAT, new SimpleEntry<>('d', 4));
        accion.get(9).set(Token.ID, new SimpleEntry<>('d', 13));
        accion.get(9).set(Token.IF, new SimpleEntry<>('d', 14));
        accion.get(9).set(Token.LLAVEI, new SimpleEntry<>('d', 9));

        accion.get(10).set(Token.INT, new SimpleEntry<>('d', 3));
        accion.get(10).set(Token.FLOAT, new SimpleEntry<>('d', 4));
        accion.get(10).set(Token.ID, new SimpleEntry<>('d', 13));
        accion.get(10).set(Token.IF, new SimpleEntry<>('d', 14));
        accion.get(10).set(Token.LLAVEI, new SimpleEntry<>('d', 9));
        accion.get(10).set(Token.LLAVED, new SimpleEntry<>('d', 16));

        accion.get(11).set(Token.INT, new SimpleEntry<>('r', 6));
        accion.get(11).set(Token.FLOAT, new SimpleEntry<>('r', 6));
        accion.get(11).set(Token.ID, new SimpleEntry<>('r', 6));
        accion.get(11).set(Token.IF, new SimpleEntry<>('r', 6));
        accion.get(11).set(Token.LLAVEI, new SimpleEntry<>('r', 6));
        accion.get(11).set(Token.LLAVED, new SimpleEntry<>('r', 6));

        accion.get(12).set(Token.INT, new SimpleEntry<>('r', 7));
        accion.get(12).set(Token.FLOAT, new SimpleEntry<>('r', 7));
        accion.get(12).set(Token.ID, new SimpleEntry<>('r', 7));
        accion.get(12).set(Token.IF, new SimpleEntry<>('r', 7));
        accion.get(12).set(Token.LLAVEI, new SimpleEntry<>('r', 7));
        accion.get(12).set(Token.LLAVED, new SimpleEntry<>('r', 7));

        accion.get(13).set(Token.ASIG, new SimpleEntry<>('d', 18));

        accion.get(14).set(Token.PARI, new SimpleEntry<>('d', 19));

        accion.get(15).set(Token.ID, new SimpleEntry<>('d', 20));

        accion.get(16).set(Token.INT, new SimpleEntry<>('r', 4));
        accion.get(16).set(Token.FLOAT, new SimpleEntry<>('r', 4));
        accion.get(16).set(Token.ID, new SimpleEntry<>('r', 4));
        accion.get(16).set(Token.IF, new SimpleEntry<>('r', 4));
        accion.get(16).set(Token.LLAVEI, new SimpleEntry<>('r', 4));
        accion.get(16).set(Token.LLAVED, new SimpleEntry<>('r', 4));
        accion.get(16).set(Token.EOF, new SimpleEntry<>('r', 4));

        accion.get(17).set(Token.INT, new SimpleEntry<>('r', 5));
        accion.get(17).set(Token.FLOAT, new SimpleEntry<>('r', 5));
        accion.get(17).set(Token.ID, new SimpleEntry<>('r', 5));
        accion.get(17).set(Token.IF, new SimpleEntry<>('r', 5));
        accion.get(17).set(Token.LLAVEI, new SimpleEntry<>('r', 5));
        accion.get(17).set(Token.LLAVED, new SimpleEntry<>('r', 5));

        accion.get(18).set(Token.ID, new SimpleEntry<>('d', 25));
        accion.get(18).set(Token.ENTERO, new SimpleEntry<>('d', 23));
        accion.get(18).set(Token.REAL, new SimpleEntry<>('d', 24));

        accion.get(19).set(Token.ID, new SimpleEntry<>('d', 25));
        accion.get(19).set(Token.ENTERO, new SimpleEntry<>('d', 23));
        accion.get(19).set(Token.REAL, new SimpleEntry<>('d', 24));

        accion.get(20).set(Token.PYC, new SimpleEntry<>('d', 27));

        accion.get(21).set(Token.PYC, new SimpleEntry<>('d', 28));
        accion.get(21).set(Token.OPAS, new SimpleEntry<>('d', 29));

        accion.get(22).set(Token.OPAS, new SimpleEntry<>('r', 12));
        accion.get(22).set(Token.PYC, new SimpleEntry<>('r', 12));
        accion.get(22).set(Token.PARD, new SimpleEntry<>('r', 12));

        accion.get(23).set(Token.OPAS, new SimpleEntry<>('r', 13));
        accion.get(23).set(Token.PYC, new SimpleEntry<>('r', 13));
        accion.get(23).set(Token.PARD, new SimpleEntry<>('r', 13));

        accion.get(24).set(Token.OPAS, new SimpleEntry<>('r', 14));
        accion.get(24).set(Token.PYC, new SimpleEntry<>('r', 14));
        accion.get(24).set(Token.PARD, new SimpleEntry<>('r', 14));

        accion.get(25).set(Token.OPAS, new SimpleEntry<>('r', 15));
        accion.get(25).set(Token.PYC, new SimpleEntry<>('r', 15));
        accion.get(25).set(Token.PARD, new SimpleEntry<>('r', 15));

        accion.get(26).set(Token.PARD, new SimpleEntry<>('d', 30));
        accion.get(26).set(Token.OPAS, new SimpleEntry<>('d', 29));

        accion.get(27).set(Token.INT, new SimpleEntry<>('r', 10));
        accion.get(27).set(Token.FLOAT, new SimpleEntry<>('r', 10));
        accion.get(27).set(Token.ID, new SimpleEntry<>('r', 10));
        accion.get(27).set(Token.IF, new SimpleEntry<>('r', 10));
        accion.get(27).set(Token.LLAVEI, new SimpleEntry<>('r', 10));
        accion.get(27).set(Token.LLAVED, new SimpleEntry<>('r', 10));

        accion.get(28).set(Token.INT, new SimpleEntry<>('r', 8));
        accion.get(28).set(Token.FLOAT, new SimpleEntry<>('r', 8));
        accion.get(28).set(Token.ID, new SimpleEntry<>('r', 8));
        accion.get(28).set(Token.IF, new SimpleEntry<>('r', 8));
        accion.get(28).set(Token.LLAVEI, new SimpleEntry<>('r', 8));
        accion.get(28).set(Token.LLAVED, new SimpleEntry<>('r', 8));

        accion.get(29).set(Token.ID, new SimpleEntry<>('d', 25));
        accion.get(29).set(Token.ENTERO, new SimpleEntry<>('d', 23));
        accion.get(29).set(Token.REAL, new SimpleEntry<>('d', 24));

        accion.get(30).set(Token.INT, new SimpleEntry<>('d', 3));
        accion.get(30).set(Token.FLOAT, new SimpleEntry<>('d', 4));
        accion.get(30).set(Token.ID, new SimpleEntry<>('d', 13));
        accion.get(30).set(Token.IF, new SimpleEntry<>('d', 14));
        accion.get(30).set(Token.LLAVEI, new SimpleEntry<>('d', 9));

        accion.get(31).set(Token.OPAS, new SimpleEntry<>('r', 11));
        accion.get(31).set(Token.PYC, new SimpleEntry<>('r', 11));
        accion.get(31).set(Token.PARD, new SimpleEntry<>('r', 11));

        accion.get(32).set(Token.INT, new SimpleEntry<>('r', 9));
        accion.get(32).set(Token.FLOAT, new SimpleEntry<>('r', 9));
        accion.get(32).set(Token.ID, new SimpleEntry<>('r', 9));
        accion.get(32).set(Token.IF, new SimpleEntry<>('r', 9));
        accion.get(32).set(Token.LLAVEI, new SimpleEntry<>('r', 9));
        accion.get(32).set(Token.LLAVED, new SimpleEntry<>('r', 9));
    }

    private void crearTablaIr_A ()
    {
        ir_a = new ArrayList<>(33);

        for (int i = 0; i < 33; i++) {
            ir_a.add(new ArrayList<>(14));
            for (int j = 0; j < 7; j++) {
                ir_a.get(i).add(null);
            }
        }

        // 0 -> Fun     2 -> Bloque     4 -> Instr      6 -> T
        // 1 -> Tipo    3 -> SInstr     5 -> E
        ir_a.get(0).set(0, 1);
        ir_a.get(0).set(1, 2);

        ir_a.get(7).set(2, 8);

        ir_a.get(9).set(1, 15);
        ir_a.get(9).set(2, 12);
        ir_a.get(9).set(3, 10);
        ir_a.get(9).set(4, 11);

        ir_a.get(10).set(1, 15);
        ir_a.get(10).set(2, 12);
        ir_a.get(10).set(4, 17);

        ir_a.get(18).set(5, 21);
        ir_a.get(18).set(6, 22);

        ir_a.get(19).set(5, 26);
        ir_a.get(19).set(6, 22);

        ir_a.get(29).set(6, 31);

        ir_a.get(30).set(1, 15);
        ir_a.get(30).set(2, 12);
        ir_a.get(30).set(4, 32);
    }

    private void crearTablaReglas ()
    {
        reglas = new ArrayList<>();

        reglas.add(new SimpleEntry<>("Fun", List.of("Tipo", "id", "pari", "pard", "Bloque")));  // 1
        reglas.add(new SimpleEntry<>("Tipo", List.of("int")));                              // 2
        reglas.add(new SimpleEntry<>("Tipo", List.of("float")));                            // 3
        reglas.add(new SimpleEntry<>("Bloque", List.of("llavei", "SInstr", "llaved")));         // 4
        reglas.add(new SimpleEntry<>("SInstr", List.of("SInstr", "Instr")));                    // 5
        reglas.add(new SimpleEntry<>("SInstr", List.of("Instr")));                          // 6
        reglas.add(new SimpleEntry<>("Instr", List.of("Bloque")));                          // 7
        reglas.add(new SimpleEntry<>("Instr", List.of("id", "asig", "E", "pyc")));              // 8
        reglas.add(new SimpleEntry<>("Instr", List.of("if", "pari", "E", "pard", "Instr")));    // 9
        reglas.add(new SimpleEntry<>("Instr", List.of("Tipo", "id", "pyc")));                   // 10
        reglas.add(new SimpleEntry<>("E", List.of("E", "opas", "T")));                          // 11
        reglas.add(new SimpleEntry<>("E", List.of("T")));                                   // 12
        reglas.add(new SimpleEntry<>("T", List.of("numentero")));                           // 13
        reglas.add(new SimpleEntry<>("T", List.of("numreal")));                             // 14
        reglas.add(new SimpleEntry<>("T", List.of("id")));                                  // 15
    }


    // Genera el mensaje en caso de error
    // pari, pard, llavei, llaved, asig, pyc, opas, int, float, if, id, entero, real
    private void errorSintactico (Token token, String msg)
    {
        show = false;
        if (token.tipo == Token.EOF)
        {
            System.err.printf("Error sintactico: encontrado fin de fichero, esperaba %s\n", msg);
        }
        else
        {
            System.err.printf("Error sintactico (%d,%d): encontrado '%s', esperaba %s\n", token.fila, token.columna, token.lexema, msg);
        }
        System.exit(-1);
    }

    // Obtiene y elimina el elemento más antiguo de la queue
    private Token obtenerToken ()
    {
        Token t = tokens.poll();
        if (t == null)
        {
            t = new Token();
            t.tipo = Token.EOF;
        }
        return t;
    }

    // Guarda los tokens en la estructura Queue<Token> tokens
    private void obtenerTokens ()
    {
        Token t;
        try
        {
            while ((t = al.siguienteToken()).tipo != Token.EOF) tokens.offer(t);
        }
        catch (Exception e)
        {
            // Los tokens correctos se mantienen
        }
    }

    // Devuelve el número de la siguiente tabla del grafo
    private int Ir_A (int estado, String no_terminal)
    {
        int numero_no_terminal = -1;
        switch (no_terminal)
        {
            case "Fun":
                numero_no_terminal = 0;
                break;

            case "Tipo":
                numero_no_terminal = 1;
                break;

            case "Bloque":
                numero_no_terminal = 2;
                break;

            case "SInstr":
                numero_no_terminal = 3;
                break;

            case "Instr":
                numero_no_terminal = 4;
                break;

            case "E":
                numero_no_terminal = 5;
                break;

            case "T":
                numero_no_terminal = 6;
                break;

            default:
                break;
        }

        // IR_A[estado (0 - 32)][numero_no_terminal = noTerminal] = siguiente_estado (0 - 32)
        return ir_a.get(estado).get(numero_no_terminal);
    }

    // Imprime el resultado
    private void imprimir ()
    {
        Collections.reverse(sol);
        for (Integer s : sol)
        {
            System.out.print(s + " ");
        }
        System.out.print("\n");
    }


    //////////////////////////////////////////////////////////////////////
    // FUNCIONES PÚBLICAS
    //////////////////////////////////////////////////////////////////////
    // Analiza los tokens
    public void analizar ()
    {
        boolean fin = false;
        obtenerTokens();

        pila.push(0);                // push(0)
        Token token = obtenerToken();
        while (!fin)
        {
            int estado_actual = pila.peek();     // Estado en la cima (0 - 32)
            if (accion.get(estado_actual).get(token.tipo) != null)
            {
                char tipo_movimiento = accion.get(estado_actual).get(token.tipo).getKey();      // d / r / a
                int siguiente_estado = accion.get(estado_actual).get(token.tipo).getValue();    // 1 - 15 / 0 - 32 / -1

                if (tipo_movimiento == 'd')  // desplazamiento
                {
                    pila.push(siguiente_estado);     // push(j)
                    token = obtenerToken();
                }
                else if (tipo_movimiento == 'r')    // retroceso
                {
                    sol.add(siguiente_estado);

                    // Como es r, siguiente_estado -> 1 - 15
                    // reglas -> 1 - 15
                    // Cantidad de elementos de la parte derecha de la regla
                    int longitud_parte_derecha = reglas.get(siguiente_estado - 1).getValue().size();
                    for (int i = 0; i < longitud_parte_derecha; i++)
                    {
                        pila.pop();
                    }

                    // 0 -> Fun     2 -> Bloque     4 -> Instr      6 -> T
                    // 1 -> Tipo    3 -> SInstr     5 -> E
                    // Parte izquierda de la regla
                    // siguiente_estado = número de regla -> 1 - 15 / reglas (0 - 14)
                    String no_terminal = reglas.get(siguiente_estado - 1).getKey();

                    // 1. Cima de la pila
                    // 2. Parte izquierda de la regla número = siguiente_estado
                    pila.push(Ir_A(pila.peek(), no_terminal));   // push del siguiente estado
                }
                else if (tipo_movimiento == 'a')     // aceptar
                {
                    fin = true;
                }
            }
            else
            {
                StringBuilder siguientes_esperados = new StringBuilder();
                for (int i = 0; i < accion.get(estado_actual).size(); i++)
                {
                    if (accion.get(estado_actual).get(i) != null)
                    {
                        Token t = new Token();
                        t.tipo = i;
                        siguientes_esperados.append(t.toString()).append(" ");
                    }
                }
                errorSintactico(token, siguientes_esperados.toString());
            }
        }

        imprimir();
    }
}
