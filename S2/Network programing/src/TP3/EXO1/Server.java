package TP3.EXO1;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server extends Thread{
    private ServerSocket serverSocket;
    private final int port;
    private boolean running = false;
    public Server(int port){
        this.port=port;
        try{
            this.serverSocket=new ServerSocket(this.port);
            System.out.println( "Listening for a connection at port "+this.port );
            this.start();
        }catch (IOException e){
            e.printStackTrace();
        }
    }
    public void stopServer()
    {
        running = false;
        this.interrupt();
    }
    @Override
    public void run() {
        this.running=true;
        while (running){
            try {
                Socket socket = this.serverSocket.accept();
                RequestHandler requestHandler = new RequestHandler( socket );
                requestHandler.start();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
