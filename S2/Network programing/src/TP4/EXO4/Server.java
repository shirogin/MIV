package TP4.EXO4;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;


public class Server extends UnicastRemoteObject implements eEventLogger {
    ArrayList<String> notesList=new ArrayList<String>();
    public Server() throws RemoteException {
        System.out.println("Server has been Created.");
    }
    public void makeNote(String note) throws RemoteException{
        this.notesList.add(note);
        System.out.println("Note has been added : "+note);
    }
    public String getList() throws RemoteException{
        StringBuilder stringBuilder=new StringBuilder("");
        for (String s : this.notesList) {
            stringBuilder.append(s).append("\n");
        }
        return stringBuilder.toString();
    }

    public static void main(String[] args) throws Exception {

        Server p = new Server();

        System.out.println("Registry creation.");
        Registry r = LocateRegistry.createRegistry(1099);
        r.rebind("Ref_p", p);

    }

}
