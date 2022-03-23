package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

class ServerTCPPingPong {
    private Socket socket = null;
    private ServerSocket server = null;
    private DataInputStream in = null;

    public ServerTCPPingPong(int port) {
        try {
            server = new ServerSocket(port);
            System.out.println("server started");
            System.out.println("waiting for client...");

            socket = server.accept();
            System.out.println("client accepted");
            in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
            String line = in.readUTF();
            if (line.equals("ping")) {
                System.out.println("got ping");
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                in.close();
                socket.close();
                server.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        ServerTCPPingPong server = new ServerTCPPingPong(5000);
    }
}