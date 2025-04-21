import java.io.*;


class prueba {

    public static String toString(Token t){
        return "("+t.fila+","+t.columna+"): "+t.lexema+" es de tipo "+t.tipo+'\n';
    }


    public static void main(String[] args) {
        AnalizadorLexico al;
        Token t;

        RandomAccessFile entrada = null;

        try {
            entrada = new RandomAccessFile("nu-fuentes/pc02.txt","r");
            al = new AnalizadorLexico(entrada);

            while ((t=al.siguienteToken()).tipo != Token.EOF) {
                System.out.println("Token: "+ t.fila + ","
                        + t.columna+ " "
                        + t.lexema+ "  -> "
                        + toString(t));
            }
        }
        catch (FileNotFoundException e) {
            System.out.println("Error, fichero no encontrado: " + args[0]);
        }
    }
}
