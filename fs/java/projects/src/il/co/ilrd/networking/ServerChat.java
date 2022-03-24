package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

import il.co.ilrd.utility.ColorsFont;

public class ServerChat {
    private List<Socket> socketList = null;
    private ServerSocket server = null;

    private volatile boolean runOutputThread = false;
    OutputThread outThread = null;

    public ServerChat(int port) {
        try {
            server = new ServerSocket(port);

            System.out.println("server started");
            System.out.println("waiting for client...");
            socketList = new ArrayList<>();
            outThread = new OutputThread();
            outThread.start();
            while (true) {
                Socket socket = server.accept();
                socketList.add(socket);
                ThreadImp threadImp = new ThreadImp(socket);
                threadImp.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private class ThreadImp extends Thread {
        private Socket socket;

        public ThreadImp(Socket socket) {
            this.socket = socket;
        }

        public void run() {
            System.out.println("client accepted");
            try (DataInputStream in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));) {

                String line = "";
                while (true) {
                    System.out.println(ColorsFont.ANSI_PURPLE + "********" + ColorsFont.ANSI_RESET);
                    line = in.readUTF();
                    writeToAllNow(line, socket);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }

    private void writeToAllNow(String line, Socket socket) {
        outThread.set(line, socket);
    }

    private class OutputThread extends Thread {
        ReentrantLock lock = new ReentrantLock();
        Condition cond = lock.newCondition();
        String line = null;
        Socket socket = null;

        private void set(String line, Socket socket) {
            this.line = line;
            this.socket = socket;
            runOutputThread = true;
        }

        public void run() {
            while (true) {
                if (runOutputThread) {
                    writeToAll();
                }
            }
        }

        private void writeToAll() {
            socketList.forEach((currSocket) -> {
                try (DataOutputStream out = new DataOutputStream(currSocket.getOutputStream());) {
                    if (!currSocket.equals(socket)) {
                        out.writeUTF(line);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });
            runOutputThread = false;
        }
    }

    public static void main(String[] args) {
        @SuppressWarnings("unused")
        ServerChat server = new ServerChat(5000);
    }
}