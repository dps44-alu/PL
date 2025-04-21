import java.io.RandomAccessFile;
import java.io.FileNotFoundException;
import java.io.IOException;

class prueba {
    public static void main(String[] args) {

        String file = "fuentes/p02.txt";

        try {
            RandomAccessFile entrada = new RandomAccessFile(file,"r");
            AnalizadorLexico al = new AnalizadorLexico(entrada);
            TraductorDR tdr = new TraductorDR(al);

            String trad = tdr.Fun(); // simbolo inicial de la gramatica
            tdr.comprobarFinFichero();
            System.out.println(trad);
        }
        catch (FileNotFoundException e) {
            System.out.println("Error, fichero no encontrado: " + file);
        }
    }
}


