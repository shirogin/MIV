package TP4.EXO2;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class Server extends UnicastRemoteObject implements Display {

    public Server() throws RemoteException {
        System.out.println("Server has been Created.");
    }
    public int somme(int x,int y) throws RemoteException {
        return x+y;
    }
    public int différence(int x,int y) throws RemoteException {
        return x-y;
    }
    public int produit(int x,int y) throws RemoteException {
        return x*y;
    }
    public int division(int x,int y) throws RemoteException {
        return x/y;
    }

    public static void main(String[] args) throws Exception {

        Server p = new Server();

        System.out.println("Registry creation.");
        Registry r = LocateRegistry.createRegistry(1099);
        r.rebind("Ref_p", p);

    }

}
