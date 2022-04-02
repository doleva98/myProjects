/* shani */

package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MultiprotocolServer {
    private List<Socket> listOfSockets = new ArrayList<>();
    private ServerSocket server = null;
    private DatagramPacket inputDatagramPacket = null;
    private DatagramSocket ds = null;
    private byte[] receive = null;
    private DataInputStream in = null;
    private Map<String, Service> mapServices = new HashMap<>();
    private ExecutorService executor;
    private String key = null;

    public MultiprotocolServer(int port) {
        try {
            startMap();

            server = new ServerSocket(port);
            executor = Executors.newCachedThreadPool();
            /* for the TCP clients */
            executor.submit(() -> {
                String line = "";
                while (!server.isClosed()) {
                    try {
                        Socket socket = server.accept();
                        listOfSockets.add(socket);
                        in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
                        line = in.readUTF();
                        key = line.split(" ")[0];
                        String valueString = line.split(" ")[1];
                        executor.submit(() -> {
                            try {
                                mapServices.get(key).startService(new TCPResponder(new DataOutputStream(
                                        socket.getOutputStream())),
                                        valueString);
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                        });

                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            });

            /* for the datagram */
            ds = new DatagramSocket(port);
            receive = new byte[65535];

            executor.submit(() -> {
                String line = "";
                while (ds.isConnected()) {
                    inputDatagramPacket = new DatagramPacket(receive, receive.length);
                    try {
                        ds.receive(inputDatagramPacket);
                        line = ByteArrayToString.byteArrayToString(receive);
                        mapServices.get(line).startService(
                                new UDPResponder(inputDatagramPacket.getAddress(), inputDatagramPacket.getPort()),
                                line.split(" ")[1]);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            });

        } catch (IOException e) {
            e.printStackTrace();
        }
        mapServices = new HashMap<>();

    }

    private void startMap() {

        mapServices.put("TCPPingPong", new TCPServicePingPong());
        mapServices.put("UDPPingPong", new UDPServicePingPong());

    }

    private interface Service {
        public void startService(Responder responder, String message);
    }

    private class TCPServicePingPong implements Service {

        /*   public TCPServicePingPong() {
        
        } */

        @Override
        public void startService(Responder responder, String message) {
            System.out.println("you are now in TCP ping pong");
            System.out.println("enter ping or pong");
            if (message.equals("ping")) {
                System.out.println("server got ping");
                System.out.println("server sends pong");
                responder.respond("pong");
            } else if (message.equals("pong")) {
                System.out.println("server got pong");
                System.out.println("server sends ping");
                responder.respond("ping");
            }
        }

    }

    private class UDPServicePingPong implements Service {

        @Override
        public void startService(Responder responder, String message) {

        }

    }

    private interface Responder {
        public void respond(String str);
    }

    private class TCPResponder implements Responder {
        private DataOutputStream dos = null;

        public TCPResponder(DataOutputStream dos) {
            this.dos = dos;
        }

        @Override
        public void respond(String str) {
            try {
                dos.writeUTF(str);
            } catch (IOException e) {
                e.printStackTrace();
            }

        }
    }

    private class UDPResponder implements Responder {
        private InetAddress ip;
        private int port;

        public UDPResponder(InetAddress ip, int port) {
            this.ip = ip;
            this.port = port;
        }

        @Override
        public void respond(String str) {
            byte[] buf = str.getBytes();
            DatagramPacket outputDatagramPacket = new DatagramPacket(buf, buf.length, ip,
                    port);
            try {
                ds.send(outputDatagramPacket);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        new MultiprotocolServer(1234);
    }
}
