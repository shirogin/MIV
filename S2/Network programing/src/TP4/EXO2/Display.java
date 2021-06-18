package TP4.EXO2;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Display extends Remote {
    public int somme(int x,int y) throws RemoteException ;
    public int différence(int x,int y) throws RemoteException ;
    public int produit(int x,int y) throws RemoteException ;
    public int division(int x,int y) throws RemoteException ;
}
