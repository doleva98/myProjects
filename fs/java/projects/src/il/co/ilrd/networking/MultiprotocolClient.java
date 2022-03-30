/* shani */
package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

import il.co.ilrd.utility.ColorsFont;

public class MultiprotocolClient {

/*     private String name = null;
    private Socket socket = null;
    private DataInputStream in = null;
    private DataOutputStream out = null; */

    public MultiprotocolClient(String address, int toPort) {
        try (Scanner scan = new Scanner(System.in);
                Socket socket = new Socket(address, toPort);
                DataInputStream in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
                DataOutputStream out = new DataOutputStream(socket.getOutputStream());) {
            System.out.println("connected");
            System.out.println(ColorsFont.ANSI_CYAN + "********" + ColorsFont.ANSI_RESET);
            System.out.println("send key and value");
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
        new MultiprotocolClient("localhost", 1234);
    }
}
