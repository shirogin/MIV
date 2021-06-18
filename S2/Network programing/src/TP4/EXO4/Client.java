package TP4.EXO4;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Client {

    public static void main(String[] args) throws Exception {

        Registry r = LocateRegistry.getRegistry("localhost", 1099);
        eEventLogger eEventLogger = (eEventLogger) r.lookup("Ref_p");
        eEventLogger.makeNote("Client Name");
        System.out.println(eEventLogger.getList());

    }

}