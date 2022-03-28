/* shani */

package il.co.ilrd.networking;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

import il.co.ilrd.utility.ColorsFont;

public class PingPongServerUDP {
    public PingPongServerUDP(int port) {
        try (DatagramSocket ds = new DatagramSocket(port);) {
            byte[] receive = new byte[65535];
            String line = "";
            DatagramPacket inputDatagramPacket = null;
            DatagramPacket outputDatagramPacket = null;

            String output = "";
            byte[] buf = null;

            System.out.println("server started");

            while (!line.equals("exit")) {
                System.out.println("waiting for a packet");
                System.out.println(ColorsFont.ANSI_PURPLE + "********" + ColorsFont.ANSI_RESET);

                inputDatagramPacket = new DatagramPacket(receive, receive.length);
                ds.receive(inputDatagramPacket);

                System.out.println("server got a packet");
                line = ByteArrayToString.byteArrayToString(receive);

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

            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        @SuppressWarnings("unused")
        PingPongServerUDP server = new PingPongServerUDP(1234);
    }
}
