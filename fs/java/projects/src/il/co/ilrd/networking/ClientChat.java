/* shani */

package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Random;
import java.util.Scanner;
import il.co.ilrd.utility.ColorsFont;

public class ClientChat {
    private String name = null;
    private Socket socket = null;
    private DataInputStream in = null;
    private DataOutputStream out = null;

    ClientChat(String address, int port) {
        try (Scanner scan = new Scanner(System.in);) {
            socket = new Socket(address, port);
            in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
            out = new DataOutputStream(socket.getOutputStream());
            System.out.println("connected");

            Random rnd = new Random(ColorsFont.numberOfColorFonts);
            String color = ColorsFont.ColorFontsArray[rnd.nextInt(ColorsFont.numberOfColorFonts)];
            System.out.println(color + "********" + ColorsFont.ANSI_RESET);

            System.out.println("what is your name?");
            name = scan.nextLine();

            String line = "";
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
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        @SuppressWarnings("unused")
        ClientChat client = new ClientChat("localhost", 5000);
    }

}
