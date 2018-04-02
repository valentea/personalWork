import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class PlayerClient extends Thread {

    private BufferedReader br;
    private PrintWriter pw;
    private Scanner userInput;

    public PlayerClient(String hostname, int port, Scanner userInput) throws IOException{
        this.userInput = userInput;
        Socket s = new Socket(hostname, port);
        System.out.println("Connected to " + hostname + ":" + port);
        System.out.println();
        try {
            br = new BufferedReader(new InputStreamReader(s.getInputStream()));
            pw = new PrintWriter(s.getOutputStream(), true);
        } catch (Exception ex) {
            throw new RuntimeException(ex);
        }
    }

    public void run() {
        int numeberOfPlayers = startGame(userInput);
        System.out.println("Starting Game...");
        System.out.println();
        selectBrawlers();
        if(numeberOfPlayers == 1){
            battle();
            System.out.println("End of Game");
        }else if(numeberOfPlayers == 2){
            battle();
        }


    }

    private void battle() {
        try {
            System.out.println(br.readLine()); //Excellent!
            while (true) {
                String stringYourBrawIndex = br.readLine();
                int yourBrawIndex = Integer.parseInt(stringYourBrawIndex);

                String stringOpBrawIndex = br.readLine();
                int opBrawIndex = Integer.parseInt(stringOpBrawIndex);

                String stringYourOldIndex = br.readLine();
                int yourOldIndex = Integer.parseInt(stringYourOldIndex);

                String stringOpOldIndex = br.readLine();
                int opOldIndex = Integer.parseInt(stringOpOldIndex);

                String stringBattleState = br.readLine();
                int battleState = Integer.parseInt(stringBattleState);

                if(battleState == 1){
                    System.out.println();
                }

                if (yourBrawIndex == 3 || opBrawIndex == 3) {
                    if (yourBrawIndex == 3) {
                        System.out.println(br.readLine());  //you are out of braw
                        System.out.println(br.readLine());
                        System.out.println(br.readLine());  //you loose
                        break;
                    } else if (opBrawIndex == 3) {
                        System.out.println(br.readLine()); //op out of braw
                        System.out.println(br.readLine());
                        System.out.println(br.readLine()); //you win
                        break;
                    }
                }
                if(yourOldIndex != yourBrawIndex || opOldIndex != opBrawIndex) {
                    if (yourOldIndex != yourBrawIndex) {
                        System.out.println(br.readLine()); //you send next braw
                    }
                    if (opOldIndex != opBrawIndex) {
                        System.out.println(br.readLine()); //op send next braw
                    }
                }else if(battleState == 2 || battleState == 3){
                    System.out.println();
                    System.out.println(br.readLine());  //braw was defeated
                }else if (battleState == 1) {
                    pickMove();
                    System.out.println();
                    attack();
                    String stringStillAlive = br.readLine();
                    int stillAlive = Integer.parseInt(stringStillAlive);
                    if(stillAlive == 1){
                        System.out.println();
                        System.out.println(br.readLine()); //curBraw has X health
                    }else if(stillAlive == 0){
                        br.readLine();
                    }
                }

            }

        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private void attack() {
        try {
            System.out.println(br.readLine()); // person used attack
            getDamage();
            System.out.println(br.readLine()); //it did X damage
            String stringOtherIsAlive = br.readLine();
            int otherIsAlive = Integer.parseInt(stringOtherIsAlive);
            if(otherIsAlive == 1){
                System.out.println(br.readLine()); // person used attack
                getDamage();
                System.out.println(br.readLine()); //it did X damage
            }

        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private void getDamage(){
        try {
            String stringDamageType = br.readLine();
            int damageType = Integer.parseInt(stringDamageType);
            if(damageType == 1){
                System.out.println(br.readLine()); //effective or not very
            } //if not special at all, dont print anythnig
        } catch (Exception ex){
            ex.printStackTrace();
        }
    }

    private void pickMove() {
        try {
            while (true) {
                String stringNumberOfChoicesForCurBrawler = br.readLine();
                int numberOfChoicesForCurBrawler = Integer.parseInt(stringNumberOfChoicesForCurBrawler);
                System.out.println(br.readLine()); //choose a move
                String movesList = br.readLine();
                String new1 =  movesList.replace("||", "\n");
                System.out.print(new1);
                while(true) {
                    int moveChoice = userInput.nextInt();
                    if (moveChoice > 0 && moveChoice <= numberOfChoicesForCurBrawler) {
                        moveChoice--;
                        pw.println(Integer.toString(moveChoice));
                        break;
                    } else {
                        System.out.println("Invalid!");
                    }
                }
                break;
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }

    }

    private int startGame(Scanner userInput) {
        try {
            System.out.println("Please make a choice:");
            System.out.println("1) Start Game");
            System.out.println("2) Join Game");
            int choice = -1;
            while(true) {
                choice = userInput.nextInt();
                if(choice == 1 || choice == 2){
                    break;
                }
                System.out.println("Invalid!");
            }
            pw.println(String.valueOf(choice));
            userInput.nextLine(); //removes '/n' that is left by userInput.nextInt() above
            if (choice == 1) {
                while (true) { //keep going till proper game name entered
                    System.out.println("What is your game name?");
                    String name = userInput.nextLine();
                    pw.println(name);
                    try {
                        String response = br.readLine();
                        if (response.equals("1")) {
                            break;
                        } else {
                            System.out.println(response);
                        }
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }
                }
                int numberOfPlayers;
                while (true) { //keep going till proper number of players is entered
                    System.out.println("How many players?");
                    numberOfPlayers = userInput.nextInt();
                    userInput.nextLine();
                    if (numberOfPlayers == 1) {
                        pw.println(numberOfPlayers);
                        break;
                    } else if(numberOfPlayers == 2){
                        pw.println(Integer.toString(numberOfPlayers));
                        System.out.println(br.readLine());
                        System.out.println(br.readLine()); // player two has  connected
                        String done = br.readLine();
                        break;
                    } else {
                        System.out.println("Enter valid number of players.");
                    }
                }
                return numberOfPlayers;
            } else if (choice == 2) {
                while (true) {
                    System.out.println("What is the name of the game;");
                    String name = userInput.nextLine();
                    pw.println(name);
                    String gameStat = br.readLine();
                    if (gameStat.equals("E")) {
                        System.out.println("Joining game...");
                        break;
                    } else {
                        System.out.println("This game does not exist.");
                    }
                }
                return 2;
            }
        } catch (IOException ioe) {
            System.out.println("ioe in ChatClient constructor: " + ioe.getMessage());
        }
        return -1;
    }

    private boolean selectBrawlers() {
        try {
            System.out.println(br.readLine()); //chose 3 brawlers
            String brawlerListAsString = br.readLine();
            List<String> brawlerList = Arrays.asList(brawlerListAsString.split("\\s*,\\s*"));
            brawlerListAsString = brawlerListAsString.replace(",", "\n");
            String posSpaceChoices;
            String choices;
            while(true) {
                System.out.print(brawlerListAsString);
                boolean badSelection = true;

                posSpaceChoices = userInput.nextLine();
                choices = posSpaceChoices.replace(", ", ",");
                List<Integer> choiceList = Stream.of(choices.split(",")).map(Integer::parseInt).collect(Collectors.toList());

                if(choiceList.size() == 3){
                    int checkint = 0;
                    for(int temp : choiceList){
                        if(temp >= 1 && temp <= brawlerList.size()){
                            checkint++;
                        }
                    }
                    if(checkint == 3){
                        badSelection = false;
                    }
                }
                if(badSelection){
                    System.out.println("Invalid");
                }else {
                    break;
                }
            }
            pw.println(choices);
            System.out.println();
            return this.getBrawlers();
        } catch (Exception ex) {
            ex.printStackTrace();
            return true;
        }
    }

    private boolean getBrawlers(){
        try{
            String badIfEql1 = br.readLine();
            if(badIfEql1.equals("1")){
                System.out.println("Invalid!");
                return false;
            }
            return true;
        }catch (Exception ex){
            ex.printStackTrace();
            return true;
        }

    }

    public static void main(String[] args) {
        PlayerClient playerClient;
        while(true) {
            try {
                System.out.println("Please enter an IP address:");
                Scanner userInput = new Scanner(System.in);
//                String hostIP = userInput.nextLine();
        String hostIP = "localhost";
                System.out.println("Please enter a port: ");
//                int port = userInput.nextInt();
        int port = 6789;
                playerClient = new PlayerClient(hostIP, port, userInput);
                break;
            }catch (IOException ioe){
                System.out.println("Unable to connect!");
            }
        }
        playerClient.start();
    }

}
