package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

import il.co.ilrd.utility.ColorsFont;

public class MultiprotocolServer {
    private List<Socket> socketList = null;
    private ServerSocket server = null;

    public MultiprotocolServer(int port) {
        try (DatagramSocket ds = new DatagramSocket(port);) {
            byte[] receive = new byte[65535];
            String line = "";
            DatagramPacket inputDatagramPacket = null;
            DatagramPacket outputDatagramPacket = null;
            server = new ServerSocket(port);
            System.out.println("server started");
            System.out.println("waiting for client...");
            String output = "";
            byte[] buf = null;

            System.out.println(ColorsFont.ANSI_PURPLE + "********" + ColorsFont.ANSI_RESET);

            inputDatagramPacket = new DatagramPacket(receive, receive.length);
            ds.receive(inputDatagramPacket);

            System.out.println("server got a packet");
            line = ByteArrayToString.byteArrayToString(receive);
            if (line.equals("ping")) {

                while (!line.equals("exit")) {
                    if (line.equals("ping")) {
                        System.out.println("server got ping");
                        System.out.println("sends pong");
                        output = "pong";
                    } else if (line.equals("pong")) {
                        System.out.println("server got pong");
                        System.out.println("sends ping");
                        output = "ping";
                    } else {
                        System.out.println("exiting");
                        break;
                    }
                    buf = output.getBytes();
                    outputDatagramPacket = new DatagramPacket(buf, buf.length, inputDatagramPacket.getAddress(),
                            inputDatagramPacket.getPort());
                    ds.send(outputDatagramPacket);

                    inputDatagramPacket = new DatagramPacket(receive, receive.length);
                    ds.receive(inputDatagramPacket);

                    System.out.println("server got a packet");
                    line = ByteArrayToString.byteArrayToString(receive);
                }
            } else if (line.equals("chat")) {
                try {

                    socketList = new ArrayList<>();
                    Socket socket = null;
                    while (true) {
                        socket = server.accept();
                        socketList.add(socket);
                        ThreadImp threadImp = new ThreadImp(socket);
                        threadImp.start();
                    }

                } catch (IOException e) {
                    e.printStackTrace();
                }
            } else {
                System.out.println("exiting");
            }
        } catch (IOException e) {
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
        new MultiprotocolServer(1234);
    }
}
