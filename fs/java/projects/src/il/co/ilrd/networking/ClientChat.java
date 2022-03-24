package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;
import il.co.ilrd.utility.ColorsFont;

public class ClientChat {
    private String name;
    Socket socket = null;

    ClientChat(String address, int port) {
        try (Scanner scan = new Scanner(System.in);) {
            socket = new Socket(address, port);
            DataInputStream in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
            DataOutputStream out = new DataOutputStream(socket.getOutputStream());
            System.out.println("connected");
            System.out.println(ColorsFont.ANSI_CYAN + "********" + ColorsFont.ANSI_RESET);
            System.out.println("what is your name?");
            name = scan.nextLine();

            InputThreadImp t = new InputThreadImp(in);
            t.start();

            String line = "";

            while (!line.equals("exit")) {
                line = scan.nextLine();
                out.writeUTF(ColorsFont.ANSI_RED + name + ColorsFont.ANSI_RESET + " " + line);
            }
            System.out.println("exiting!");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private class InputThreadImp extends Thread {
        DataInputStream in = null;

        public InputThreadImp(DataInputStream in) {
            this.in = in;
        }

        public void run() {
            while (true) {
                try {
                    System.out.println(in.readUTF());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

    }

    public static void main(String[] args) {
        @SuppressWarnings("unused")
        ClientChat client = new ClientChat("localhost", 5000);
    }

}
