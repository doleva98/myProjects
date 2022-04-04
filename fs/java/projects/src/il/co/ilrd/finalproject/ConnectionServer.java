package il.co.ilrd.finalproject;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.net.InetAddress;
import il.co.ilrd.networking.ByteArrayToString;

public class ConnectionServer {
    private List<Socket> listOfSockets = new ArrayList<>();
    private ServerSocket server = null;
    private DatagramPacket inputDatagramPacket = null;
    private DatagramSocket ds = null;
    private DataInputStream in = null;
    private ExecutorService executor;
    private final int port;
    private OperationManager operationManager = null;

    public ConnectionServer(int port, String databasePath) {
        this.port = port;
        operationManager = new OperationManager(databasePath);
    }

    public void start() {

        /* TCP connection */
        try {
            server = new ServerSocket(port);

            executor = Executors.newCachedThreadPool();
            /* for the TCP clients */
            executor.submit(() -> {
                String line = "";

                while (!server.isClosed()) {
                    try {
                        Socket socket = server.accept();
                        System.out.println("TCP connection is established");
                        listOfSockets.add(socket);
                        in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
                        System.out.println("waiting for input from client");
                        line = in.readUTF();
                        operationManager.handleRequest(line, new Responder() {
                            private DataOutputStream out = new DataOutputStream(socket.getOutputStream());

                            @Override
                            public void respond(String message) {
                                try {
                                    out.writeUTF(message);
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }

                        });

                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            });

        } catch (IOException e2) {
            e2.printStackTrace();
        }

        /* for the datagram */
        try {
            ds = new DatagramSocket(port);

            executor.submit(() -> {
                String line = "";

                while (true) {
                    byte[] receive = new byte[65535];
                    inputDatagramPacket = new DatagramPacket(receive, receive.length);
                    try {
                        ds.receive(inputDatagramPacket);
                        System.out.println("got UDP packet");
                        line = ByteArrayToString.byteArrayToString(receive);
                        operationManager.handleRequest(line, new Responder() {
                            private InetAddress ip = inputDatagramPacket.getAddress();
                            private int port = inputDatagramPacket.getPort();

                            @Override
                            public void respond(String massage) {
                                byte[] buf = massage.getBytes();
                                try {
                                    ds.send(new DatagramPacket(buf, massage.length(), ip, port));
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }

                            }

                        });
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            });
        } catch (SocketException e1) {
            e1.printStackTrace();
        }
    }

    public void stop() {
    }

    public static void main(String[] args) {
        ConnectionServer connectionServer = new ConnectionServer(1234,
                "C:\\Users\\dolev\\Desktop\\git\\dolev-arev\\fs\\java\\projects\\src\\il\\co\\ilrd\\finalproject");
        connectionServer.start();
    }
}
