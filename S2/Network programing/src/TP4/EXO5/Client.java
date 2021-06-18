package TP4.EXO5;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Client {

    public static void main(String[] args) throws Exception {

        Registry r = LocateRegistry.getRegistry("localhost", 1099);
        Chat Chat = (Chat) r.lookup("Ref_p");
        Chat.makeNote("Client Name");
        System.out.println(Chat.getList());

    }

}