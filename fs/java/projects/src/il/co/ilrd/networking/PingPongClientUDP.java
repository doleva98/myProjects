/* shani */

package il.co.ilrd.networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

import il.co.ilrd.utility.ColorsFont;

public class PingPongClientUDP {
    public PingPongClientUDP(int toPort) {
        try (Scanner scan = new Scanner(System.in);
                DatagramSocket ds = new DatagramSocket();) {
            InetAddress ip = InetAddress.getLocalHost();
            byte[] buf = null;
            byte[] receive = new byte[65535];

            DatagramPacket outputDatagramPacket = null;
            DatagramPacket inputDatagramPacket = null;

            System.out.println(ColorsFont.ANSI_CYAN + "********" + ColorsFont.ANSI_RESET);
            System.out.println("send ping or pong");
            String line = scan.nextLine();

            while (line.equals("ping") || line.equals("pong")) {
                buf = line.getBytes();
                outputDatagramPacket = new DatagramPacket(buf, buf.length, ip, toPort);
                ds.send(outputDatagramPacket);

                inputDatagramPacket = new DatagramPacket(receive, receive.length);
                ds.receive(inputDatagramPacket);

                line = ByteArrayToString.byteArrayToString(receive);
                if (line.equals("ping")) {
                    System.out.println("client got ping");
                } else if (line.equals("pong")) {
                    System.out.println("client got pong");
                }

                System.out.println(ColorsFont.ANSI_CYAN + "********" + ColorsFont.ANSI_RESET);
                System.out.println("send ping or pong");
                line = scan.nextLine();
            }
            System.out.println("exiting");
            buf = "exit".getBytes();
            outputDatagramPacket = new DatagramPacket(buf, buf.length, ip, toPort);
            ds.send(outputDatagramPacket);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        @SuppressWarnings("unused")
        PingPongClientUDP client = new PingPongClientUDP(1234);
    }
}
