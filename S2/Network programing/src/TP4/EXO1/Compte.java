package TP4.EXO1;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Compte extends UnicastRemoteObject implements CompteInterface {
    private double solde;

    public Compte(double s) throws RemoteException {
        super();
        solde = s;
    }

    public void crediter(double montant) throws RemoteException {
        solde = solde + montant;
    }

    public void debiter(double montant) throws RemoteException {
        solde = solde - montant;
    }

    public double lire_solde() throws RemoteException {
        return solde;
    }
}
