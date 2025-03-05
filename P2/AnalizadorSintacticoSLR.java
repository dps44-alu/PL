import java.util.LinkedList;
import java.util.Queue;

public class AnalizadorSintacticoSLR
{
    //////////////////////////////////////////////////////////////////////
    // ATRIBUTOS PRIVADOS
    //////////////////////////////////////////////////////////////////////
    AnalizadorLexico al;        // AnalizadorLéxico para obtener los tokens
    boolean show;               // Flag para inidicar si mostrar o no la solución
    StringBuilder sol;          // Solución de que reglas se han aplicado
    Queue<Token> tokens;        // Estructura que alamacena los tokens


    //////////////////////////////////////////////////////////////////////
    // CONSTRUCTORES
    //////////////////////////////////////////////////////////////////////
    public AnalizadorSintacticoSLR (AnalizadorLexico lexico)
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
    // pari, pard, llavei, llaved, asig, pyc, opas, int, float, if, id, entero, real.
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
    // Analiza el archivo
    public void analizar ()
    {
        obtenerTokens();
        sol.append(" 1");
    }
}
