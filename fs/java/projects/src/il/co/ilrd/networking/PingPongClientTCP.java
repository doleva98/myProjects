/* shani */

package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;
import il.co.ilrd.utility.ColorsFont;

class PingPongClientTCP {

    PingPongClientTCP(String address, int port) {
        try (Scanner scan = new Scanner(System.in);
                Socket socket = new Socket(address, port);
                DataInputStream in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
                DataOutputStream out = new DataOutputStream(socket.getOutputStream());) {
            System.out.println("connected");
            System.out.println(ColorsFont.ANSI_CYAN + "********" + ColorsFont.ANSI_RESET);
            System.out.println("client send ping or pong");
            String line = scan.nextLine();

            out.writeUTF(line);
            String inputFromServer = "";
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

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public static void main(String[] args) {
        @SuppressWarnings("unused")
        PingPongClientTCP client = new PingPongClientTCP("127.0.0.1", 5000);
    }

}
