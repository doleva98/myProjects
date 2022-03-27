/* shani */
package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

import il.co.ilrd.utility.ColorsFont;

public class ServerChat {
    private List<Socket> socketList = null;
    private ServerSocket server = null;

    public ServerChat(int port) {
        try {
            server = new ServerSocket(port);

            System.out.println("server started");
            System.out.println("waiting for client...");
            socketList = new ArrayList<>();
            Socket socket = null;
            while (true) {
                socket = server.accept();
                socketList.add(socket);
                ThreadImp threadImp = new ThreadImp(socket);
                threadImp.start();
            }

        } catch (IOException e) {
            try {
                server.close();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
            e.printStackTrace();
        }
    }

    private class ThreadImp extends Thread {
        private Socket socket = null;
        private DataInputStream in = null;
        private DataOutputStream out = null;

        public ThreadImp(Socket socket) {
            this.socket = socket;
        }

        public void run() {
            System.out.println("client accepted");
            try {
                in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));

                String line = "";
                while (!line.equals("exit")) {
                    System.out.println(ColorsFont.ANSI_PURPLE + "********" + ColorsFont.ANSI_RESET);
                    line = in.readUTF();
                    System.out.println(line);
                    for (Socket so : socketList) {
                        if (!so.equals(socket)) {
                            out = new DataOutputStream(so.getOutputStream());
                            out.writeUTF(line);
                        }
                    }
                }
                for (Socket so : socketList) {
                    if (!so.equals(socket)) {
                        out = new DataOutputStream(so.getOutputStream());
                        out.writeUTF(line);
                    }
                }
                in.close();
                out.close();
                socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        @SuppressWarnings("unused")
        ServerChat server = new ServerChat(5000);
    }
}