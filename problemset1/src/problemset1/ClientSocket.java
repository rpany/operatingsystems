package problemset1;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class ClientSocket {
	
	
	
	public static void main(String[] args) throws IOException, InterruptedException, ClassNotFoundException {
		
		// the first parameter is the host ip, the second the port number
		if(args.length < 2) throw new IllegalArgumentException("You need to provide both a hostname and port number");
		
		String hostname = args[0];
		Integer port = Integer.parseInt(args[1]);
		
		
		System.out.println("The hostname is " + hostname + "\n");
		System.out.println("The port number is " + port + "\n");
		
		InetAddress host = InetAddress.getLocalHost();
		
		Socket socket = null;
		
		
		ObjectOutputStream oos = null;
		ObjectInputStream ois = null;
		
		
            //establish socket connection to server
            socket = new Socket(host.getHostName(), port);
            //write to socket using ObjectOutputStream
            oos = new ObjectOutputStream(socket.getOutputStream());
            System.out.println("Sending request to Socket Server");
            oos.writeObject("Hellow World");
            
            //read the server response message
            ois = new ObjectInputStream(socket.getInputStream());
            String message = (String) ois.readObject();
            System.out.println("Message: " + message);
            //close resources
            ois.close();
            oos.close();
            Thread.sleep(100);
        
           socket.close();
		
		
			
		
	}

}
