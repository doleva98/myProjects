package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Random;
import java.util.Scanner;

import il.co.ilrd.utility.ColorsFont;

public class MultiprotocolClient {

    private String name = null;
    private Socket socket = null;
    private DataInputStream in = null;
    private DataOutputStream out = null;

    public MultiprotocolClient(String address, int toPort) {
        try (Scanner scan = new Scanner(System.in);) {
            DatagramSocket ds = new DatagramSocket();
            InetAddress ip = InetAddress.getByName(address);
            byte[] buf = null;
            byte[] receive = new byte[65535];

            DatagramPacket outputDatagramPacket = null;
            DatagramPacket inputDatagramPacket = null;

            System.out.println(ColorsFont.ANSI_CYAN + "********" + ColorsFont.ANSI_RESET);
            System.out.println("do you want to use char or ping");
            String line = scan.nextLine();

            if (line.equals("ping")) {
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

            } else if (line.equals("chat")) {

                socket = new Socket(address, toPort);
                in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
                out = new DataOutputStream(socket.getOutputStream());
                System.out.println("connected");

                Random rnd = new Random(ColorsFont.numberOfColorFonts);
                String color = ColorsFont.ColorFontsArray[rnd.nextInt(ColorsFont.numberOfColorFonts)];
                System.out.println(color + "********" + ColorsFont.ANSI_RESET);

                System.out.println("what is your name?");
                name = scan.nextLine();

                Thread t = new Thread(() -> {
                    while (true) {
                        try {
                            System.out.println(in.readUTF());
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                });
                t.start();

                while (!line.equals("exit")) {
                    line = scan.nextLine();
                    out.writeUTF(color + name + ColorsFont.ANSI_RESET + " " + line);
                }
                System.out.println("exiting!");
                out.close();
                in.close();
                socket.close();

            } else {
                System.out.println("invalid input");
            }
            ds.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new MultiprotocolClient("localhost", 5000);
    }
}
