package il.co.ilrd.networking;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketPermission;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MultiprotocolServer1 {
    private List<Socket> socketList = null;
    private ServerSocket server = null;
    private DataInputStream in = null;

    public MultiprotocolServer1(int port) {
        try {
            server = new ServerSocket(port);
            socketList = new ArrayList<>();

            Map<String, ServiceInterface> services = new HashMap<>();
            services.put("CHAT_TCP", new chatSereverInNewThread);
            services.put("PING_UDP", new pingServerInNewThread);

            Socket socket = null;
            String input = "";
            while (true) {
                socket = server.accept();
                in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
                input = in.readUTF();
                socketList.add(socket);

                services.get(input).put(socket);

                ThreadImp threadImp = new ThreadImp(socket);
                threadImp.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private interface ServiceInterface {

    }
}
