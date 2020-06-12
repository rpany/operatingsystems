package problemset1;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerSocketExample {
	
	

	public static void main(String[] args) throws IOException, ClassNotFoundException {
		// TODO Auto-generated method stub
		
		if(args.length < 1) throw new IllegalArgumentException("You need to provide a port number");
		
		
		Integer port = Integer.parseInt(args[0]);
		
		ServerSocket serverSocket = new ServerSocket(port);
		
		while(true) {
			 System.out.println("Waiting for the client request");
	            //creating socket and waiting for client connection
	            Socket socket = serverSocket.accept();
	            //read from socket to ObjectInputStream object
	            ObjectInputStream ois = new ObjectInputStream(socket.getInputStream());
	            //convert ObjectInputStream object to String
	            String message = (String) ois.readObject();
	            System.out.println("Message Received: " + message);
	            //create ObjectOutputStream object
	            ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
	            //write object to Socket
	            oos.writeObject("Hi Client "+message);
	            //close resources
	            ois.close();
	            oos.close();
	            socket.close();
	            //terminate the server if client sends exit request
	            if(message.equalsIgnoreCase("exit")) break;
			
			
		}

	}

}
