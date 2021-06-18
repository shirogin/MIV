package TP1.EXO1;

import java.io.*;

public class Fichier {
    static private String name = "test.txt";

    public static void afficherFichier() {
        InputStream is;
        try {
            is = new FileInputStream(name);
            byte[] b = new byte[50];
            while (is.read(b) != -1) {
                System.out.println(new String(b));
            }
            is.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void ecrireFichier(String s) {
        OutputStream os;
        try {
            os = new FileOutputStream(name);
            s = s + "\n";
            os.write(s.getBytes());
            os.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static Object afficherObjectFichier() {
        ObjectInputStream ois;
        try {
            ois = new ObjectInputStream(new FileInputStream(name));
            Object o;
            o = ois.readObject();
            System.out.println(o);
            ois.close();
            return o;
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void ecrireObjectFichier(Object o) {
        ObjectOutputStream oos;
        try {
            oos = new ObjectOutputStream(new FileOutputStream(name));
            oos.writeObject(o);
            oos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
