package TP1.EXO4;

public class Main {
    public static void main(String[] args) {
        Fichier fichier=new Fichier("./text.txt");
        fichier.copyLines("./text1.txt");
        fichier.copyChars("./text2.txt");
    }
}
