package il.co.ilrd.IOTinfrastructure;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

import il.co.ilrd.utility.ColorsFont;

public class ConnectionClientTCP {
    public ConnectionClientTCP(String address, int toPort) {
        String line = "";
        try (Scanner scan = new Scanner(System.in);) {
            while (!line.equals("exit")) {

                try (Socket socket = new Socket(address, toPort);
                        DataInputStream in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
                        DataOutputStream out = new DataOutputStream(socket.getOutputStream());) {
                    System.out.println("TCP connection established");
                    System.out.println(ColorsFont.ANSI_CYAN + "********" + ColorsFont.ANSI_RESET);
                    System.out.println("send key and value");
                    line = scan.nextLine();
                    out.writeUTF(line);
                    System.out.println(in.readUTF());

                }

                catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        new ConnectionClientTCP("localhost", 1234);
    }
}
/*
 * C:\\Users\\dolev\\Desktop\\git\\dolev-arev\\fs\\java\\projects\\src\\il\\co\\
 * ilrd\\finalproject\\dir
 */