package TP4.EXAMPLE;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Client {

    public static void main(String[] args) throws Exception {

        Registry r = LocateRegistry.getRegistry("localhost", 1099);
        P2_Interface i = (P2_Interface) r.lookup("Ref_p");

        i.Aff("Hi everyone");
        int n = i.Addition(1, 2);
        System.out.println("n: "+n);

    }

}