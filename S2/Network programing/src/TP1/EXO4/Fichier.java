package TP1.EXO4;

import java.io.*;
import java.util.Scanner;

public class Fichier {
    private final String name;
    private final File file;

    public Fichier(String name) {
        this.name = name;
        this.file = new File(name);
    }

    public void afficherFichier() {
        InputStream is;
        try {
            is = new FileInputStream(this.name);
            byte[] b = new byte[50];
            while (is.read(b) != -1) {
                System.out.println(new String(b));
            }
            is.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void ecrireFichier(String s) {
        OutputStream os;
        try {
            os = new FileOutputStream(this.name);
            s = s + "\n";
            os.write(s.getBytes());
            os.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void afficherObjectFichier() {
        ObjectInputStream ois;
        try {
            ois = new ObjectInputStream(new FileInputStream(name));
            Object o;
            o = ois.readObject();
            System.out.println(o);
            ois.close();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public void ecrireObjectFichier(Object o) {
        ObjectOutputStream oos;
        try {
            oos = new ObjectOutputStream(new FileOutputStream(this.name));
            oos.writeObject(o);
            oos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void copyLines(String newName) {
        try {
            Scanner myReader = new Scanner(this.file);
            FileWriter file1 = new FileWriter(newName);
            while (myReader.hasNextLine()) {
                file1.write(myReader.nextLine());
                file1.write("\n");
            }
            file1.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void copyChars(String newName) {
        try {
            FileReader myReader = new FileReader(this.file);
            FileWriter file1 = new FileWriter(newName);
            int content;
            while ((content = myReader.read()) != -1) {
                file1.write((char) content);
            }
            file1.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
