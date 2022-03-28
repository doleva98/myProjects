/* shani */
package il.co.ilrd.networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import il.co.ilrd.utility.ColorsFont;

public class PingPongClientBroadcast {
    public PingPongClientBroadcast() {

        try (Scanner scan = new Scanner(System.in);
                DatagramSocket ds = new DatagramSocket();
                Scanner scan2 = new Scanner(System.in)) {

            List<Integer> listOfPorts = new ArrayList<>();
            System.out.println("enter port numbers or -1 to quit");
            int portNumber = scan.nextInt();
            while (portNumber != -1) {
                listOfPorts.add(portNumber);
                portNumber = scan.nextInt();
            }
            InetAddress ip = InetAddress.getLocalHost();
            byte[] buf = null;
            byte[] receive = new byte[65535];

            DatagramPacket outputDatagramPacket = null;
            DatagramPacket inputDatagramPacket = null;

            System.out.println(ColorsFont.ANSI_CYAN + "********" + ColorsFont.ANSI_RESET);
            System.out.println("send ping or pong");
            String line = "";

            line = scan2.nextLine();

            while (line.equals("ping") || line.equals("pong")) {
                buf = line.getBytes();
                for (int port : listOfPorts) {
                    outputDatagramPacket = new DatagramPacket(buf, buf.length, ip, port);
                    ds.send(outputDatagramPacket);

                }

                for (int port : listOfPorts) {

                    inputDatagramPacket = new DatagramPacket(receive, receive.length);
                    ds.receive(inputDatagramPacket);
                    System.out.println("received a packet from the server with port " + port);
                    line = ByteArrayToString.byteArrayToString(receive);
                    if (line.equals("ping")) {
                        System.out.println("client got ping");
                    } else if (line.equals("pong")) {
                        System.out.println("client got pong");
                    }
                }

                System.out.println(ColorsFont.ANSI_CYAN + "********" + ColorsFont.ANSI_RESET);
                System.out.println("send ping or pong");
                line = scan2.nextLine();
            }
            System.out.println("exiting");
            buf = "exit".getBytes();
            for (int port : listOfPorts) {
                outputDatagramPacket = new DatagramPacket(buf, buf.length, ip, port);
                ds.send(outputDatagramPacket);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        @SuppressWarnings("unused")
        PingPongClientBroadcast client = new PingPongClientBroadcast();
    }
}
