package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

import il.co.ilrd.utility.ColorsFont;

public class MultiprotocolClient1 {

    private String name = null;
    private Socket socket = null;
    private DataInputStream in = null;
    private DataOutputStream out = null;

    public MultiprotocolClient1(String address, int toPort) {

        try (Scanner scan = new Scanner(System.in);) {
            socket = new Socket(address, toPort);
            in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
            out = new DataOutputStream(socket.getOutputStream());
            System.out.println("connected");

            System.out.println("what is your name?");
            name = scan.nextLine();

            System.out.println(ColorsFont.ANSI_CYAN + "********" + ColorsFont.ANSI_RESET);
            System.out.println("TCP or UDP");
            String line = scan.nextLine();

            while (!line.equals("TCP") || !line.equals("UDP")) {
                System.out.println("try again");
                line = scan.nextLine();
            }

            out.writeUTF(line);

            String inputFromServer = "";
            if (line.equals("TCP")) {
                System.out.println("send ping, pong, or exit");
                line = scan.nextLine();
                out.writeUTF(line);
                while (!line.equals("exit")) {
                    System.out.println(ColorsFont.ANSI_CYAN + "********" + ColorsFont.ANSI_RESET);
                    inputFromServer = in.readUTF();
                    if (inputFromServer.equals("pong")) {
                        System.out.println("client got pong");
                    } else if (inputFromServer.equals("ping")) {
                        System.out.println("client got ping");
                    }
                    if (inputFromServer.equals("exit")) {
                        break;
                    }
                    System.out.println("send ping, pong, or exit");
                    line = scan.nextLine();
                    out.writeUTF(line);
                }
                System.out.println("exiting!");
                out.writeUTF("exit");
            } else if (line.equals("UDP")) {
                
            }

        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

    }
}
