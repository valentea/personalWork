import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.FileInputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class ServerMain {
    private ServerSocket ss;

    ServerMain(int port) throws  IOException{
        ss = new ServerSocket(port);
        System.out.println("Success at port " + port + "!");
    }

    public void runServer(BrawlerTypes brawlerTypes) {
        List<GameServer> serverThreads = new ArrayList<>();
        try {
            while (true) {
                Socket s = ss.accept(); // blocking
                System.out.println("Connection from: " + s.getInetAddress());
                GameServer st = new GameServer(s, brawlerTypes);
                serverThreads.add(st);
            }
        } catch (IOException ioe) {
            System.out.println("ioe in Game constructor: " + ioe.getMessage());
        }
    }

    public static void main(String[] args) {
        BrawlerTypes brawlerTypes;
        Scanner userInput = new Scanner(System.in);
        while (true) {
            System.out.println("Please enter a valid file:");
//            String jsonDataFileName = userInput.nextLine();
            String jsonDataFileName = "test.json";
            try (FileInputStream jsonData = new FileInputStream(jsonDataFileName)) {
                ObjectMapper brawlerMapper = new ObjectMapper();
                brawlerTypes = brawlerMapper.readValue(jsonData, BrawlerTypes.class);
                break;
            } catch (Exception ex) {
                System.out.println("Error with Json File");
            }
        }
        ServerMain serverMain;
        while(true) {
            try {
                System.out.println("Please enter a valid port: ");
//                int port = userInput.nextInt();
              int port = 6789;
                serverMain = new ServerMain(port);
                break;
            } catch (IOException ioe) {
                System.out.println("Invalid Port!");
            }
        }
        serverMain.runServer(brawlerTypes);
    }
}
