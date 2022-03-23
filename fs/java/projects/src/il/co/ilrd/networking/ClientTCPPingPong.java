package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;
import il.co.ilrd.utility.ColorsFont;

class ClientTCPPingPong {
    private Socket socket = null;
    private DataInputStream in = null;
    private DataOutputStream out = null;
    private DataInputStream keyboardInput = null;

    ClientTCPPingPong(String address, int port) {
        Scanner scan = new Scanner(System.in);
        try {
            socket = new Socket(address, port);
            System.out.println("connected");

            out = new DataOutputStream(socket.getOutputStream());

            out = new DataOutputStream(socket.getOutputStream());
            System.out.println(ColorsFont.ANSI_CYAN + "********" + ColorsFont.ANSI_RESET);
            System.out.println("client send ping or pong");
            String line = scan.nextLine();

            out.writeUTF(line);
            String inputFromServer = "";
            in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
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
        } finally {
            try {
                out.close();
                in.close();
                socket.close();
                scan.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }

    public static void main(String[] args) {
        @SuppressWarnings("unused")
        ClientTCPPingPong client = new ClientTCPPingPong("127.0.0.1", 5000);
    }

}
