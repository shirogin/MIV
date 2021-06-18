package TP3.EXO1;

import java.net.InetAddress;
import java.net.UnknownHostException;

public class main {
    public static void main(String[] args) {
        final int port = 3200;
        final String address;
        try {
            address = InetAddress.getLocalHost().getHostAddress();
            System.out.println(address);
            System.out.println("Start server on port: " + port);
            Server server = new Server(port);
            Client client1 = new Client(address, port),
                    client2 = new Client(address, port);

            Thread.sleep(60000);
            server.stopServer();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}