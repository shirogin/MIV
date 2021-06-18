package TP3.EXO1;
import java.net.Socket;
import java.net.InetAddress;
import java.io.*;
public class Client extends Thread {
    public Client(String server, int port){
        try
        {
            // Connect to the server
            Socket socket = new Socket( server, port );
            // Create input and output streams to read from and write to the server
            PrintStream out = new PrintStream( socket.getOutputStream() );
            BufferedReader in = new BufferedReader( new InputStreamReader( socket.getInputStream() ) );

            out.println( InetAddress.getLocalHost().getHostAddress() );
            out.println();

            // Read data from the server until we finish reading the document
            String line = in.readLine();
            while( line != null )
            {
                System.out.println( "Server Date and time : "+line );
                line = in.readLine();
            }

            // Close our streams
            in.close();
            out.close();
            socket.close();
        }
        catch( Exception e )
        {
            e.printStackTrace();
        }
    }
}
