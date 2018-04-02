import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class GameServer extends Thread {

    private PrintWriter pw;
    private BufferedReader br;
    private BrawlerTypes brawlerTypes;
    private static Map<String, Game> gameList = new HashMap<>();
    private Socket s;

    public GameServer(Socket s, BrawlerTypes brawlerTypes) {
        this.s = s;
        Scanner userInput = new Scanner(System.in);
        try {
            this.brawlerTypes = brawlerTypes;
            pw = new PrintWriter(s.getOutputStream(), true);
            br = new BufferedReader(new InputStreamReader(s.getInputStream()));
            this.start();
        } catch (IOException ioe) {
            System.out.println("ioe in ServerThread constructor: " + ioe.getMessage());
        }
    }

    public void sendMessage(String message) {
        pw.println(message);
        pw.flush();
    }

    public void run() {
        try {
            Game currentGame = startGame();
            currentGame.play();
            System.out.println("End of game " + currentGame.getGameName());
            while(true){


            }
        }catch (Exception ex){
            ex.printStackTrace();
        }
    }

    private Game startGame(){
        try {
            int choice = Integer.parseInt(br.readLine());
            String name = br.readLine();
            if (choice == 1) {   //creating a new game
                Player player1 = new Player(s, true);
                while (true) { //keep going till good name entered;
                    if (getGame(name) == null) {
                        pw.println("1"); //can make game.
                        break;
                    } else {
                        pw.println("This game name already exists.");
                        pw.flush();
                    }
                }
                int numberOfPlayers = Integer.parseInt(br.readLine());
                Game game = createGame(name, numberOfPlayers, player1);
                System.out.println("Game " + name + " has been created.");
                if(numberOfPlayers == 2){
                    synchronized (game){
                        pw.println("Waiting for player to connect...");
                        game.wait();
                        pw.println("Player two connected!");
                        pw.println("Waiting for player to connect...Done");
                    }
                }
                return game;
            }else if (choice == 2) { //join game
                Player player2 = new Player(s, true);
                System.out.println("Someone joining game " + name);
                Game joinGame;
                while (true) {
                    joinGame = getGame(name);
                    if (joinGame != null) {
                        pw.println("E"); //game Exists and we can join
                        break;
                    } else {
                        pw.println("DNE");
                    }
                }
                synchronized (joinGame){
                    joinGame.notify();
                }
                joinGame.addPlayer2(player2);
                return joinGame;
            }else {
                System.out.println("SOmething wrong happend. choice: " + choice);
            }
        }catch(Exception ex){
            ex.printStackTrace();
        }
        return null;
    }

    private Game createGame(String name, int numberOfPlayers, Player player1){
        synchronized (gameList){
            if(gameList.containsKey(name)){
                return null;
            }
            Game newGame = new Game(brawlerTypes, numberOfPlayers, name, player1, numberOfPlayers == 2);
            gameList.put(name, newGame);
            return newGame;
        }

    }

    private Game getGame(String name){
        synchronized (gameList) {
            return gameList.get(name);
        }

    }
}
