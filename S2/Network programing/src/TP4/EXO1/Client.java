package TP4.EXO1;

import java.io.IOException;
import java.rmi.Naming;
import java.rmi.RMISecurityManager;

public class Client {
    public static void main(String[] argv) throws IOException {
        if (argv.length != 2) {
            System.out.println("Usage : java Client <nombre> <operation>");
            System.exit(1);
        }
// operation = 1: credit, 2: dedit
        System.setSecurityManager(new RMISecurityManager());
        double valeur = Double.parseDouble(argv[0]);
        int operation = Integer.parseInt(argv[1]);
        try {
            CompteInterface cpt = (CompteInterface) Naming.lookup("//localhost/CompteCourant");
            if (operation == 1) cpt.crediter(valeur);
            if (operation == 2) cpt.debiter(valeur);
            System.out.println("Votre solde courant = " +
                    cpt.lire_solde() + " euros");

        } catch (Exception e) {
            System.out.println("Erreur d'acces a un objet distant");
            System.out.println(e.toString());
        }
    }
}
