package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

import il.co.ilrd.utility.ColorsFont;

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
            out = new DataOutputStream(socket.getOutputStream());
            in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
            String line = "";
            while (!line.equals("exit")) {
                System.out.println(ColorsFont.ANSI_PURPLE + "********" + ColorsFont.ANSI_RESET);
                line = in.readUTF();
                if (line.equals("ping")) {
                    System.out.println("server got ping");
                    System.out.println("server sends pong");
                    out.writeUTF("pong");
                } else if (line.equals("pong")) {
                    System.out.println("server got pong");
                    System.out.println("server sends ping");
                    out.writeUTF("ping");
                } else {
                    System.out.println("exit, didn't got ping or pong");
                    line = "exit";
                    out.writeUTF(line);
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