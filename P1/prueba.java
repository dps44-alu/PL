import java.io.RandomAccessFile;
import java.io.FileNotFoundException;

class prueba
{
    public static void main(String[] args)
    {
        try
        {
            RandomAccessFile entrada = new RandomAccessFile("fuentes/p04.txt","r");
            AnalizadorLexico al = new AnalizadorLexico(entrada);
            AnalizadorSintacticoDR asdr = new AnalizadorSintacticoDR(al);

            asdr.Fun(); // simbolo inicial de la gramatica
            asdr.comprobarFinFichero();
        }
        catch (FileNotFoundException e)
        {
            System.out.println("Error, fichero no encontrado");
        }
    }
}

