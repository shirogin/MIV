package TP1.EXO1;

public class Main {
    static public void main(String[] args) {
        // Question 5 a
        Fichier.ecrireFichier("bonjour");
        Fichier.afficherFichier();
        // Question 5 b
        Object o = new String("toto");
        Fichier.ecrireObjectFichier(o);
        String s = (String) Fichier.afficherObjectFichier();
        System.out.println(s);

    }
}
