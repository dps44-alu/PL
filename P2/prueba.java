import java.io.RandomAccessFile;
import java.io.FileNotFoundException;

class prueba {
    public static void main(String[] args) {
        try {
            RandomAccessFile entrada = new RandomAccessFile("fuentes/p01.txt","r");
            AnalizadorLexico al = new AnalizadorLexico(entrada);
            AnalizadorSintacticoSLR aslr = new AnalizadorSintacticoSLR(al);

            aslr.analizar();
        }
        catch (FileNotFoundException e) {
            System.out.println("Error, fichero no encontrado: " + args[0]);
        }
    }
}

