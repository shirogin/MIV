package TP4.EXO3;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class Server extends UnicastRemoteObject implements Hello {

    public Server() throws RemoteException {
        System.out.println("Server has been Created.");
    }


    public String sayHello() throws RemoteException {
        return "Hello Client";
    }

    public static void main(String[] args) throws Exception {

        Server p = new Server();

        System.out.println("Registry creation.");
        Registry r = LocateRegistry.createRegistry(1099);
        r.rebind("Ref_p", p);

    }

}
