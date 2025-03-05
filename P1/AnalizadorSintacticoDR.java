import java.io.FileNotFoundException;
import java.io.RandomAccessFile;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class AnalizadorSintacticoDR
{
    //////////////////////////////////////////////////////////////////////
    // ATRIBUTOS PRIVADOS
    //////////////////////////////////////////////////////////////////////
    AnalizadorLexico al;        // AnalizadorLéxico para obtener los tokens
    boolean show;               // Flag para inidicar si mostrar o no la solución
    StringBuilder sol;          // Solución de que reglas se han aplicado
    Queue<Token> tokens;        // Estructura que alamacena los tokens


    //////////////////////////////////////////////////////////////////////
    // CONTRUCTORES
    //////////////////////////////////////////////////////////////////////
    public AnalizadorSintacticoDR (AnalizadorLexico lexico)
    {
        show = true;
        sol = new StringBuilder();
        al = lexico;
        al.setSintactico(true);
        tokens = new LinkedList<Token>();
    }


    //////////////////////////////////////////////////////////////////////
    // FUNCIONES PRIVADAS
    //////////////////////////////////////////////////////////////////////
    // Genera el mensaje en caso de error
    // id, int, float, pari, pard, coma, amp, llavei, llaved, asig, pyc, if, opas, numentero, numreal
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
    private Token obtenerToken()
    {
        Token t = tokens.poll();
        if (t == null)
        {
            t = new Token();
            t.tipo = Token.EOF;
        }
        return t;
    }

    // Obtiene el elemento más antiguo de la queue sin eliminarlo
    private Token verToken()
    {
        Token t = tokens.peek();
        if (t == null)
        {
            t = new Token();
            t.tipo = Token.EOF;
        }
        return t;
    }

    // 2. Tipo -> int
    // 3. Tipo -> float
    private void Tipo ()
    {
        Token t = obtenerToken();                           // int || float
        if (t.tipo == Token.INT)        sol.append(" 2");   // Int
        else if (t.tipo == Token.FLOAT) sol.append(" 3");   // FLoat
        else                            errorSintactico(t, "'int' 'float'");
    }

    // 4. Args -> pari LArgs pard
    private void Args ()
    {
        sol.append(" 4");
        Token t = obtenerToken();   // (
        if (t.tipo == Token.PARI)   LArgs();
        else                        errorSintactico(t, "(");

        t = obtenerToken();         // )
        if (t.tipo != Token.PARD)   errorSintactico(t, ")");
    }

    // 5. LArgs -> A MasArgs
    // 6. LArgs -> ϵ
    private void LArgs ()
    {
        Token t = verToken();
        if (!")".equals(t.lexema))
        {
            if (t.tipo == Token.INT || t.tipo == Token.FLOAT)   // PRIM(A)
            {
                sol.append(" 5");
                A();
                MasArgs();
            }
            else    errorSintactico(t, "'int' 'float' )");
        }
        else    sol.append(" 6");

    }

    // 7. MasArgs -> coma A MasArgs
    // 8. MasArgs -> ϵ
    private void MasArgs ()
    {
        Token t = verToken();
        if (",".equals(t.lexema))
        {
            sol.append(" 7");
            tokens.poll();      // ,
            A();
            MasArgs();
        }
        else if (t.tipo == Token.PARD)  sol.append(" 8");  // SIG(MasArgs)
        else                            errorSintactico(t, ") ,");
    }

    // 9. A -> Tipo Var
    private void A ()
    {
        sol.append(" 9");
        Tipo();
        Var();
    }

    // 10. Var -> amp id
    // 11. Var -> id
    private void Var ()
    {
        Token t = obtenerToken();       // amp || id
        if (t.tipo == Token.AMP)        // amp
        {
            sol.append(" 10");
            t = obtenerToken();         // id
            if (t.tipo != Token.ID) errorSintactico(t, "identificador");
        }
        else if (t.tipo == Token.ID)    // id
        {
            sol.append(" 11");
        }
        else    errorSintactico(t, "identificador &");
    }

    // 12. Bloque -> llavei SInstr llaved
    private void Bloque ()
    {
        sol.append(" 12");
        Token t = obtenerToken();       // llavei
        if (t.tipo != Token.LLAVEI) errorSintactico(t, "{");
        SInstr();
        t = obtenerToken();             // llaved
        if (t.tipo != Token.LLAVED) errorSintactico(t, "}");
    }

    // 13. SInstr -> Instr SInstrp
    private void SInstr ()
    {
        sol.append(" 13");
        Instr();
        SInstrp();
    }

    // 14. SInstrp -> Instr SInstrp
    // 15. SInstrp -> ϵ
    private void SInstrp ()
    {
        Token t = verToken();
        if (t.tipo == Token.LLAVEI || t.tipo == Token.ID || t.tipo == Token.IF || t.tipo == Token.INT || t.tipo == Token.FLOAT) // PRIM(SInstrp)
        {
            sol.append(" 14");
            Instr();
            SInstrp();
        }
        else if (t.tipo == Token.LLAVED)    sol.append(" 15");  // SIG(SInstrp)
        else                                errorSintactico(t, "identificador 'int' 'float' { } 'if'");
    }

    // 16. Instr -> Bloque
    // 17. Instr -> id asig E pyc
    // 18. Instr -> if pari E pard Instr
    // 19. Instr -> Tipo id Init
    private void Instr ()
    {
        Token t = verToken();
        if (t.tipo == Token.LLAVEI)
        {
            sol.append(" 16");
            Bloque();
        }
        else if (t.tipo == Token.ID)
        {
            sol.append(" 17");
            tokens.poll();  // id
            t = obtenerToken(); // asig
            if (t.tipo != Token.ASIG)   errorSintactico(t, "=");
            E();
            t = obtenerToken(); // pyc
            if (t.tipo != Token.PYC)    errorSintactico(t, ";");
        }
        else if (t.tipo == Token.IF)
        {
            sol.append(" 18");
            tokens.poll();  // if
            t = obtenerToken(); // pari
            if (t.tipo != Token.PARI)   errorSintactico(t, "(");
            E();
            t = obtenerToken(); // pard
            if (t.tipo != Token.PARD)   errorSintactico(t, ")");
            Instr();
        }
        else if (t.tipo == Token.INT || t.tipo == Token.FLOAT)
        {
            sol.append(" 19");
            Tipo();
            t = obtenerToken(); // id
            if (t.tipo != Token.ID) errorSintactico(t, "identificador");
            Init();
        }
        else    errorSintactico(t, "identificador ( ) = ;");
    }

    // 20. Init -> pyc
    // 21. Init -> asig E pyc
    private void Init ()
    {
        Token t = obtenerToken();
        if (t.tipo == Token.PYC)    sol.append(" 20");
        else if (t.tipo == Token.ASIG)
        {
            sol.append(" 21");
            E();
            t = obtenerToken();
            if (t.tipo != Token.PYC)    errorSintactico(t, ";");
        }
        else errorSintactico(t, "= ;");
    }

    // 22. E -> T Ep
    private void E ()
    {
        sol.append(" 22");
        T();
        Ep();
    }

    // 23. Ep -> opas T Ep
    // 24. Ep -> ϵ
    private void Ep ()
    {
        Token t = verToken();
        if (t.tipo == Token.OPAS)
        {
            sol.append(" 23");
            tokens.poll();  // opas
            T();
            Ep();
        }
        else if (t.tipo == Token.PYC || t.tipo == Token.PARD)   sol.append(" 24");   // SIG(Ep)
        else    errorSintactico(t, ") ; + -");
    }

    // 25. T -> numentero
    // 26. T -> numreal
    // 27. T -> id
    private void T ()
    {
        Token t = obtenerToken();   // numentero || numreal || id
        if (t.tipo == Token.ENTERO)     sol.append(" 25");
        else if (t.tipo == Token.REAL)  sol.append(" 26");
        else if (t.tipo == Token.ID)    sol.append(" 27");
        else                            errorSintactico(t, "identificador numero entero numero real");
    }

    // Guarda los tokens en la estructura Queue<Token> tokens
    private void obtenerTokens()
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


    //////////////////////////////////////////////////////////////////////
    // FUNCIONES PÚBLICAS
    //////////////////////////////////////////////////////////////////////
    // Fun -> Tipo id Args Bloque
    public void Fun ()
    {
        obtenerTokens();
        sol.append(" 1");
        Tipo();
        tokens.poll();  // id
        Args();
        Bloque();
    }

    // Imprime la solución (o no)
    public void comprobarFinFichero ()
    {
        if (show)   System.out.println(sol.toString());
    }
}
