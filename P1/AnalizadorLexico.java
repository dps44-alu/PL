import java.io.EOFException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;

public class AnalizadorLexico
{
    //////////////////////////////////////////////////////////////////////
    // ATRIBUTOS PRIVADOS
    //////////////////////////////////////////////////////////////////////
    private boolean EOF;                            // Atributo para controlar el fin del fichero
    private final RandomAccessFile fichero;         // Fichero a leer
    private int pos;                                // Posición de la lectura en el archivo
    private int fila;                               // Fila del fichero en la que se está leyenda
    private int columna;                            // Columna del ficherp en la que se está leyendo
    private final StringBuilder palabra_actual;     // Palabra actual que será el lexema del token final
    private boolean comentario;                     // Atributo para controlar si se está leyendo en un comentario
    private boolean error;                          // Atributo para controlar si se ha dado un error léxico
    private final ArrayList<Integer> estados;       // Almacena los estados que se están recorriendo para el token
    private char c;                                 // Variable utilizada para leer el fichero
    private boolean sintactico;                     // Conprueba si se está ejecutando desde un analizador sintáctico


    //////////////////////////////////////////////////////////////////////
    // CONTRUCTORES
    //////////////////////////////////////////////////////////////////////
    public AnalizadorLexico (RandomAccessFile entrada)
    {
        EOF = false;
        fichero = entrada;
        pos = columna = 0;
        fila = 1;
        palabra_actual = new StringBuilder();
        comentario = false;
        error = false;
        estados = new ArrayList<Integer>();
        c = '\u0000';
        sintactico = false;
    }


    //////////////////////////////////////////////////////////////////////
    // FUNCIONES PRIVADAS
    //////////////////////////////////////////////////////////////////////
    // Lee el siguiente caracter del fichero
    private char leerCaracter ()
    {
        char c;
        try
        {
            c = (char) fichero.readByte();
            pos++;
            columna++;
            return c;
        }
        catch (EOFException e)
        {
            EOF = true;
            if (palabra_actual.isEmpty())   return 'ç';
            else                            return ' ';
        }
        catch (IOException e)
        {
            return ' ';
        }
    }

    // Evita que se seleccionen estados sobre caracteres vacíos
    private void saltarCaracteresVacios ()
    {
        while (c == '\n' || c == ' ')
        {
            if (c == '\n')
            {
                fila++;
                columna = 0;
            }
            c = leerCaracter();
        }
    }

    // Comprueba si se ha llegado al fin del comentario
    private void comprobarFinComentario ()
    {
        if (c == '*')
        {
            c = leerCaracter();
            if (c == '/')
            {
                comentario = false;
                c = leerCaracter();
                saltarCaracteresVacios();
                palabra_actual.append(c);
            }
        }
    }

    // Comprueba si se está entrando en un comentario
    private void comprobarInicioComentario ()
    {
        if (c == '/')
        {
            c = leerCaracter();
            if (c == '*')
            {
                comentario = true;
                palabra_actual.setLength(0);
            }
            else
            {
                retroceder();
            }
        }
    }

    // Retrocede en un caracter la lectura del archivo
    private void retroceder ()
    {
        try {
            columna--;
            pos--;
            fichero.seek(pos);  // Retrocede en un caracter la lectura del fichero
            palabra_actual.deleteCharAt(palabra_actual.length() - 1);   // Elimina el último caracter
        }
        catch (IOException e)
        {
            System.exit(-1);
        }
    }

    // Decide cuál es el siguiente estado dependiendo de en cuál está y el valor del siguiente caracter
    private int siguienteEstado (int estado)
    {
        if (comentario) return 0;   // Dentro de un comentario no hay avances de estado
        switch (estado)
        {
            case 0:
                if (Character.isLetter(c))  if      (c == 'i')  return 10;
                else if (c == 'f')  return 18;
                else                return 14;

                else if (Character.isDigit(c))  return 24;
                else if (c == '(')              return 1;
                else if (c == ')')              return 2;
                else if (c == ',')              return 3;
                else if (c == '&')              return 4;
                else if (c == '{')              return 5;
                else if (c == '}')              return 6;
                else if (c == '=')              return 7;
                else if (c == ';')              return 8;
                else if (c == '+' || c == '-')  return 9;
                else if (c == ' ')              return 0;
                else    // No reconocido
                {
                    error = true;
                    return estado;
                }

            case 10:
                if      (c == 'n')                                      return 11;
                else if (c == 'f')                                      return 13;
                else if (Character.isLetter(c) || Character.isDigit(c)) return 14;
                else                                                    return 17;

            case 11:
                if      (c == 't')                                      return 12;
                else if (Character.isLetter(c) || Character.isDigit(c)) return 14;
                else                                                    return 17;

            case 12:
                if  (!Character.isLetter(c) && !Character.isDigit(c))   return 15;
                else                                                    return 14;

            case 13:
                if  (!Character.isLetter(c) && !Character.isDigit(c))   return 16;
                else                                                    return 14;

            case 14:
                if  (!Character.isLetter(c) && !Character.isDigit(c))   return 17;
                else                                                    return 14;

            case 18:
                if      (c == 'l')                                      return 19;
                else if (Character.isLetter(c) || Character.isDigit(c)) return 14;
                else                                                    return 17;

            case 19:
                if      (c == 'o')                                      return 20;
                else if (Character.isLetter(c) || Character.isDigit(c)) return 14;
                else                                                    return 17;

            case 20:
                if      (c == 'a')                                      return 21;
                else if (Character.isLetter(c) || Character.isDigit(c)) return 14;
                else                                                    return 17;

            case 21:
                if      (c == 't')                                      return 22;
                else if (Character.isLetter(c) || Character.isDigit(c)) return 14;
                else                                                    return 17;

            case 22:
                if  (!Character.isLetter(c) && !Character.isDigit(c))   return 23;
                else                                                    return 14;

            case 24:
                if      (Character.isDigit(c))  return 24;
                else if (c == '.')              return 26;
                else                            return 25;

            case 26:
                if  (Character.isDigit(c))  return 27;
                else
                {
                    error = true;
                    return estado;
                }

            case 27:
                if  (Character.isDigit(c))  return 27;
                else                        return 28;

            default:
                error = true;
                return estado;
        }
    }

    // Comprueba si el estado actual es final y reajusta la lectura en caso de ser necesario
    private boolean esFinal (int estado)
    {
        if (estado == 1 || estado == 2 || estado == 3 || estado == 4 || estado == 5 || estado == 6 || estado == 7 || estado == 8 || estado == 9)
        {
            return true;
        }
        else if (estado == 15 || estado == 16 || estado == 17 || estado == 23 || estado == 25 || estado == 28)
        {
            retroceder();
            return true;
        }
        return false;
    }

    // Crea el token y le asgina el valor a sus atributos
    private Token tokenAsociado (int estado)
    {
        Token token = new Token();
        token.lexema = palabra_actual.toString();
        token.fila = fila;
        switch (estado)
        {
            case 1:
                token.columna = columna;
                token.tipo = Token.PARI;
                break;

            case 2:
                token.columna = columna;
                token.tipo = Token.PARD;
                break;

            case 3:
                token.columna = columna;
                token.tipo = Token.COMA;
                break;

            case 4:
                token.columna = columna;
                token.tipo = Token.AMP;
                break;

            case 5:
                token.columna = columna;
                token.tipo = Token.LLAVEI;
                break;

            case 6:
                token.columna = columna;
                token.tipo = Token.LLAVED;
                break;

            case 7:
                token.columna = columna;
                token.tipo = Token.ASIG;
                break;

            case 8:
                token.columna = columna;
                token.tipo = Token.PYC;
                break;

            case 9:
                token.columna = columna;
                token.tipo = Token.OPAS;
                break;

            case 15:
                token.columna = columna - palabra_actual.length() + 1;
                token.tipo = Token.INT;
                break;

            case 16:
                token.columna = columna - palabra_actual.length() + 1;
                token.tipo = Token.IF;
                break;

            case 17:
                token.columna = columna - palabra_actual.length() + 1;
                token.tipo = Token.ID;
                break;

            case 23:
                token.columna = columna - palabra_actual.length() + 1;
                token.tipo = Token.FLOAT;
                break;

            case 25:
                token.columna = columna - palabra_actual.length() + 1;
                token.tipo = Token.ENTERO;
                break;

            case 28:
                token.columna = columna - palabra_actual.length() + 1;
                token.tipo = Token.REAL;
                break;

            default:
                token.tipo = Token.EOF;
                break;
        }
        palabra_actual.setLength(0);    // Vaciar la palabra para el siguiente token
        return token;
    }


    //////////////////////////////////////////////////////////////////////
    // FUNCIONES PÚBLICAS
    //////////////////////////////////////////////////////////////////////
    // Cambia el valor de la variable sintactico
    public void setSintactico (Boolean s)
    {
        sintactico = s;
    }

    // Sigue leyendo el fichero hasta obtener el siguiente token
    public Token siguienteToken ()
    {
        estados.add(0);
        c = leerCaracter();
        // Comprueba que la búsqueda del token anterior no hubiese acabado encontrando un error léxico
        if (error)
        {
            if (sintactico) throw new RuntimeException();
            System.err.printf("Error lexico (%d,%d): caracter '%c' incorrecto\n", fila, columna - palabra_actual.length(), c);
            System.exit(-1);
        }
        saltarCaracteresVacios();   // Evitar empezar con ' ' o '\n'
        do
        {
            // Primero comprobar que no se haya acabado el archivo
            if (EOF)
            {
                if (comentario)
                {
                    System.err.println("Error lexico: fin de fichero inesperado");
                    System.exit(-1);
                }
                if (c == 'ç')
                {
                    Token token = new Token();
                    token.tipo = Token.EOF;
                    return token;
                }
            }
            if (!comentario) palabra_actual.append(c);
            if (comentario)
            {
                comprobarFinComentario();
            }
            if (palabra_actual.toString().equals("/"))
            {
                comprobarInicioComentario();
            }
            int nuevo = siguienteEstado(estados.get(estados.size() - 1));
            estados.add(nuevo);
            if (error)
            {
                if (estados.get(estados.size() - 1) == 26)  // Caso 9.a
                {
                    retroceder();
                    retroceder();
                    estados.remove(estados.size() - 1);
                    estados.remove(estados.size() - 1);
                    return tokenAsociado(25);           // ENTERO
                }
            }
            if (esFinal(nuevo))
            {
                if (EOF) leerCaracter();
                estados.clear();
                return tokenAsociado(nuevo);
            }
            else
            {
                if (c == 'ç')
                {
                    Token token = new Token();
                    token.tipo = Token.EOF;
                    return token;
                }
                c = leerCaracter();
            }
        } while (true);
    }
}

/*
    1 = PARI, 2 = PARD, 3 = COMA, 4 = AMP, 5 = LLAVEI, 6 = LLAVED, 7 = ASIG,
    8 = PYC, 9 = OPAS, 15 = INT, 16 = IF, 17 = ID, 23 = FLOAT, 25 = ENTERO, 28 = REAL
*/