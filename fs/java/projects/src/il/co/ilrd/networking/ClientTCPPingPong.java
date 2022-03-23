package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

class ClientTCPPingPong {
    private Socket socket = null;
    private DataInputStream in = null;
    private DataOutputStream out = null;

    ClientTCPPingPong(String address, int port) {
        try {
            socket = new Socket(address, port);
            System.out.println("connected");
            out = new DataOutputStream(socket.getOutputStream());
            System.out.println("client sends ping");
            out.writeUTF("ping");
            while (true) {
                in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
                if (in.readUTF().equals("pong")) {
                    System.out.println("client got pong");
                }
                out = new DataOutputStream(socket.getOutputStream());
                System.out.println("client sends ping");
                out.writeUTF("ping");
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                out.close();
                in.close();
                socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }

    public static void main(String[] args) {
        @SuppressWarnings("unused")
        ClientTCPPingPong client = new ClientTCPPingPong("127.0.0.1", 5000);
    }

}
