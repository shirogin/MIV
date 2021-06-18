package TP4.EXAMPLE;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface P2_Interface extends Remote {

    int Addition(int a, int b) throws RemoteException ;
    void Aff(String str) throws RemoteException ;

}
