package TP4.EXAMPLE;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Server extends java.rmi.server.UnicastRemoteObject  implements P2_Interface {

    public Server() throws RemoteException { System.out.println("Yooo whassup its your booi p2"); }

    public int Addition(int a, int b) throws RemoteException { return a+b; }

    public void Aff(String str) throws RemoteException { System.out.println(str); }

    public static void main(String[] args) throws RemoteException {

        Server p = new Server();

        System.out.println("Registry creation.");
        Registry r = LocateRegistry.createRegistry(1099);
        r.rebind("Ref_p", p);

    }

}
