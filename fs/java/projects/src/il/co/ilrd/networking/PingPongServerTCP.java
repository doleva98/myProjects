/* shani */

package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

import il.co.ilrd.utility.ColorsFont;

class PingPongServerTCP {

    public PingPongServerTCP(int port) {
        try (ServerSocket server = new ServerSocket(port);) {
            System.out.println("server started");
            System.out.println("waiting for client...");
            try (Socket socket = server.accept();
                    DataInputStream in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
                    DataOutputStream out = new DataOutputStream(socket.getOutputStream());) {

                System.out.println("client accepted");
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
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        @SuppressWarnings("unused")
        PingPongServerTCP server = new PingPongServerTCP(5000);
    }
}