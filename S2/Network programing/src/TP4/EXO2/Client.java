package TP4.EXO2;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Client {

    public static void main(String[] args) throws Exception {

        Registry r = LocateRegistry.getRegistry("localhost", 1099);
        Display hello = (Display) r.lookup("Ref_p");
        /*String response = hello.sayHello();
        System.out.println(response);*/

    }

}