package TP4.EXO1;

import java.rmi.Naming;

public class Serveur {
    public static void main(String[] args) {
        try {
            System.out.println("Serveur : Construction de l’implémentation");
            Compte cpt = new Compte(15.50);
            System.out.println("Objet Compte enregistré dans RMIregistry");
            System.out.println("Attente des invocations des clients ");
        } catch (Exception e) {
            System.out.println("Erreur de liaison de l'objet Compte");
            e.printStackTrace();
        }
    } // fin du main
}
