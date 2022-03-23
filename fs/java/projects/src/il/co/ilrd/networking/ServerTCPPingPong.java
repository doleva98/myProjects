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
    private DataOutputStream out = null;

    public ServerTCPPingPong(int port) {
        try {
            server = new ServerSocket(port);
            System.out.println("server started");
            System.out.println("waiting for client...");

            socket = server.accept();
            System.out.println("client accepted");
            while (true) {
                in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
                if (in.readUTF().equals("ping")) {
                    System.out.println("server got ping");
                    out = new DataOutputStream(socket.getOutputStream());
                    System.out.println("server sends pong");
                    out.writeUTF("pong");
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                out.close();
                in.close();
                socket.close();
                server.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        @SuppressWarnings("unused")
        ServerTCPPingPong server = new ServerTCPPingPong(5000);
    }
}