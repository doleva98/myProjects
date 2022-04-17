package il.co.ilrd.IOTinfrastructure;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Scanner;

import il.co.ilrd.networking.ByteArrayToString;
import il.co.ilrd.utility.ColorsFont;

public class ConnectionClientUDP {
    public ConnectionClientUDP(String address, int toPort) throws SocketException {
        try (Scanner scan = new Scanner(System.in);
                DatagramSocket ds = new DatagramSocket();) {
            try {
                InetAddress ip = InetAddress.getByName(address);

                byte[] receive = new byte[65535];

                DatagramPacket outputDatagramPacket = null;
                DatagramPacket inputDatagramPacket = null;
                String line = "";

                while (!line.equals("exit")) {
                    byte[] buf = null;

                    System.out.println(ColorsFont.ANSI_CYAN + "********" + ColorsFont.ANSI_RESET);
                    System.out.println("send key and value");
                    line = scan.nextLine();
                    buf = line.getBytes();
                    outputDatagramPacket = new DatagramPacket(buf, line.length(), ip, toPort);
                    try {
                        ds.send(outputDatagramPacket);
                        inputDatagramPacket = new DatagramPacket(receive, receive.length);
                        ds.receive(inputDatagramPacket);
                        line = ByteArrayToString.byteArrayToString(receive);
                        System.out.println(line);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            } catch (UnknownHostException e1) {
                e1.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        try {
            new ConnectionClientUDP("localhost", 1234);
        } catch (SocketException e) {
            e.printStackTrace();
        }
    }
}
