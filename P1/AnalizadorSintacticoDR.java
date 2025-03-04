import java.io.FileNotFoundException;
import java.io.RandomAccessFile;

public class AnalizadorSintacticoDR
{
    //////////////////////////////////////////////////////////////////////
    // ATRIBUTOS PRIVADOS
    //////////////////////////////////////////////////////////////////////
    AnalizadorLexico al;
    boolean show;
    StringBuilder regla;

    //////////////////////////////////////////////////////////////////////
    // CONTRUCTORES
    //////////////////////////////////////////////////////////////////////
    public AnalizadorSintacticoDR (AnalizadorLexico lexico)
    {
        show = false;
        regla = null;
        al = lexico;
    }


    //////////////////////////////////////////////////////////////////////
    // FUNCIONES PRIVADAS
    //////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////
    // FUNCIONES PÚBLICAS
    //////////////////////////////////////////////////////////////////////
    public void Fun ()
    {
        Token t;
        while ((t = al.siguienteToken()).tipo != Token.EOF) {
            switch (t.tipo) {
                case Token.ID:

                    break;

                case Token.INT:

                    break;

                case Token.FLOAT:

                    break;

                case Token.PARI:

                    break;

                case Token.PARD:

                    break;

                case Token.COMA:

                    break;

                case Token.AMP:

                    break;

                case Token.LLAVEI:

                    break;

                case Token.LLAVED:

                    break;

                case Token.ASIG:

                    break;

                case Token.PYC:

                    break;

                case Token.IF:

                    break;

                case Token.OPAS:

                    break;

                case Token.ENTERO:

                    break;

                case Token.REAL:

                    break;
            }
        }
    }

    public void comprobarFinFichero ()
    {

    }
}
