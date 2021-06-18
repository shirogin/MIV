package TP3.EXO1;
import java.net.Socket;
import java.io.*;
import java.util.Date;

public class RequestHandler extends Thread{

    private final Socket socket;
    RequestHandler( Socket socket )
    {
        this.socket = socket;
    }

    @Override
    public void run() {
        try
        {
            System.out.println( "Received a connection" );

            // Get input and output streams
            BufferedReader in = new BufferedReader( new InputStreamReader( socket.getInputStream() ) );
            PrintWriter out = new PrintWriter( socket.getOutputStream() );

            // Write out server date and time to the client
            out.println((new Date()).toString());
            out.flush();

            // read in client @IP in the server;
            String line = in.readLine();
            System.out.println( "@IP : " + line );

            // Close our connection
            in.close();
            out.close();
            socket.close();

            System.out.println( "Connection closed" );
        }
        catch( Exception e )
        {
            e.printStackTrace();
        }
    }
}
