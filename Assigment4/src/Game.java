import java.io.BufferedReader;
import java.io.PrintWriter;
import java.time.Year;
import java.util.*;

import static java.lang.Math.abs;

public class Game {
    private int numberOfPlayers;
    private BrawlerTypes brawlerTypes;
    private Player player1;
    private Player player2;
    private String gameName;


    public String getGameName() {
        return gameName;
    }

    public int getNumberOfPlayers() {
        return numberOfPlayers;
    }

    public void setNumberOfPlayers(int numberOfPlayers) {
        this.numberOfPlayers = numberOfPlayers;
    }

    public BrawlerTypes getBrawlerTypes() {
        return brawlerTypes;
    }

    public void setBrawlerTypes(BrawlerTypes brawlerTypes) {
        this.brawlerTypes = brawlerTypes;
    }


    Game(BrawlerTypes brawlerTypes, int numberOfPlayers, String gameName, Player player1, boolean human) {
        this.gameName = gameName;
        this.player1 = player1;
        if (!human) {
            this.player2 = new Player(player1.getSocket(), false);
        }
        setNumberOfPlayers(numberOfPlayers);
        setBrawlerTypes(brawlerTypes);
    }

    public void addPlayer2(Player player2){
        this.player2 = player2;
    }

    public void play() {
        if (numberOfPlayers == 1) {
            Player playerOne = this.player1;
            Player computer = this.player2;
            playerOne.selectBrawlers(brawlerTypes);
            computer.selectBrawlers(brawlerTypes);
            battle(playerOne, computer);
        } else if (numberOfPlayers == 2) {
            Player playerOne = player1;
            Player playerTwo = player2;
            playerOne.selectBrawlers(brawlerTypes);
            playerTwo.selectBrawlers(brawlerTypes);
            twoPlayerBattle(playerOne, playerTwo);
        }

    }

    private void twoPlayerBattle(Player player1, Player player2){
        player1.pw.println("Excellent");
        player2.pw.println("Excellent");
        int yourBrawlerIndex = 0;
        int opponentBrawlerInedx = 0;
        int oldYouIndex = -1;
        int oldOpIndex = -1;
        Brawler yourCurBrawler = null;
        Brawler opCurBrawler = null;
        while (true) {
            player1.pw.println(Integer.toString(yourBrawlerIndex));
            player1.pw.println(Integer.toString(opponentBrawlerInedx));
            player1.pw.println(Integer.toString(oldYouIndex));
            player1.pw.println(Integer.toString(oldOpIndex));

            player2.pw.println(Integer.toString(yourBrawlerIndex));
            player2.pw.println(Integer.toString(opponentBrawlerInedx));
            player2.pw.println(Integer.toString(oldYouIndex));
            player2.pw.println(Integer.toString(oldOpIndex));

            if (yourCurBrawler == null && opCurBrawler == null) {
                player1.pw.println("1");
                player2.pw.println("1");
            } else if (yourCurBrawler.isAlive() && opCurBrawler.isAlive()) {
                player1.pw.println("1");  //this is battle state in client
                player2.pw.println("1");  //this is battle state in client
            } else if (!yourCurBrawler.isAlive()) {
                player1.pw.println("2");  //this is battle state in client
                player2.pw.println("2");  //this is battle state in client
            } else if (!opCurBrawler.isAlive()) {
                player1.pw.println("3");  //this is battle state in client
                player2.pw.println("3");  //this is battle state in client
            }
            if (yourBrawlerIndex == 3 || opponentBrawlerInedx == 3) {
                if (yourBrawlerIndex == 3) {
                    player1.pw.println("You are out of Brawlers!");
                    player1.pw.println("");
                    player1.pw.println("You Loose!");

                    player2.pw.println("You are out of Brawlers!");
                    player2.pw.println("");
                    player2.pw.println("You Loose!");
                    break;
                } else if (opponentBrawlerInedx == 3) {
                    player1.pw.println("Your opponent is out of Brawlers!");
                    player1.pw.println("");
                    player1.pw.println("You Win!");

                    player2.pw.println("Your opponent is out of Brawlers!");
                    player2.pw.println("");
                    player2.pw.println("You Win!");
                    break;
                }

                if (oldYouIndex != yourBrawlerIndex || oldOpIndex != opponentBrawlerInedx) {
                    if (oldYouIndex != yourBrawlerIndex) {
                        yourCurBrawler = player1.getChosenBrawlers().get(yourBrawlerIndex);
                        player1.pw.println("You Send " + yourCurBrawler.getType().getName() + "!");
                        player2.pw.println("You Send " + yourCurBrawler.getType().getName() + "!");
                        oldYouIndex = yourBrawlerIndex;
                    }
                    if (oldOpIndex != opponentBrawlerInedx) {
                        opCurBrawler = player2.getChosenBrawlers().get(opponentBrawlerInedx);
                        player1.pw.println("Your opponent plays " + opCurBrawler.getType().getName() + "!");
                        player2.pw.println("Your opponent plays " + opCurBrawler.getType().getName() + "!");
                        oldOpIndex = opponentBrawlerInedx;
                    }
                } else if (!yourCurBrawler.isAlive()) { //for client (battle state 2)
                    player1.pw.println(yourCurBrawler.getType().getName() + " was defeated!");
                    player2.pw.println(yourCurBrawler.getType().getName() + " was defeated!");
                    yourBrawlerIndex++;
                } else if (!opCurBrawler.isAlive()) {   //for client (battle state 3)
                    player1.pw.println(opCurBrawler.getType().getName() + " was defeated!");
                    player2.pw.println(opCurBrawler.getType().getName() + " was defeated!");
                    opponentBrawlerInedx++;
                } else if (yourCurBrawler.isAlive() && opCurBrawler.isAlive()) {   //for client (battle state 1)
                    Ability yourMove = player1.pickMove(yourCurBrawler);
                    Ability opponentMove = player2.pickMove(opCurBrawler);
                    attack(yourCurBrawler, yourMove, opCurBrawler, opponentMove);
                    if (yourCurBrawler.isAlive()) {
                        player1.pw.println("1");
                        player1.pw.println(yourCurBrawler.getType().getName() + " has " + yourCurBrawler.getHealth() + " health.");
                        player2.pw.println("1");
                        player2.pw.println(yourCurBrawler.getType().getName() + " has " + yourCurBrawler.getHealth() + " health.");
                    } else {
                        player1.pw.println("0");
                        player1.pw.println("empty");
                        player2.pw.println("0");
                        player2.pw.println("empty");
                    }
                }
            }

        }
    }

    private void battle(Player you, Player opponent) {
        player1.pw.println("Excellent");
        int yourBrawlerIndex = 0;
        int opponentBrawlerInedx = 0;
        int oldYouIndex = -1;
        int oldOpIndex = -1;
        Brawler yourCurBrawler = null;
        Brawler opCurBrawler = null;
        while (true) {
            player1.pw.println(Integer.toString(yourBrawlerIndex));
            player1.pw.println(Integer.toString(opponentBrawlerInedx));
            player1.pw.println(Integer.toString(oldYouIndex));
            player1.pw.println(Integer.toString(oldOpIndex));
            if (yourCurBrawler == null && opCurBrawler == null) {
                player1.pw.println("1");
            } else if (yourCurBrawler.isAlive() && opCurBrawler.isAlive()) {
                player1.pw.println("1");  //this is battle state in client
            } else if (!yourCurBrawler.isAlive()) {
                player1.pw.println("2");  //this is battle state in client
            } else if (!opCurBrawler.isAlive()) {
                player1.pw.println("3");  //this is battle state in client
            }
            if (yourBrawlerIndex == 3 || opponentBrawlerInedx == 3) {
                if (yourBrawlerIndex == 3) {
                    player1.pw.println("You are out of Brawlers!");
                    player1.pw.println("");
                    player1.pw.println("You Loose!");
                    break;
                } else if (opponentBrawlerInedx == 3) {
                    player1.pw.println("Your opponent is out of Brawlers!");
                    player1.pw.println("");
                    player1.pw.println("You Win!");
                    break;
                }
            }
            if (oldYouIndex != yourBrawlerIndex || oldOpIndex != opponentBrawlerInedx) {
                if (oldYouIndex != yourBrawlerIndex) {
                    yourCurBrawler = player1.getChosenBrawlers().get(yourBrawlerIndex);
                    player1.pw.println("You Send " + yourCurBrawler.getType().getName() + "!");
                    oldYouIndex = yourBrawlerIndex;
                }
                if (oldOpIndex != opponentBrawlerInedx) {
                    opCurBrawler = opponent.getChosenBrawlers().get(opponentBrawlerInedx);
                    player1.pw.println("Your opponent plays " + opCurBrawler.getType().getName() + "!");
                    oldOpIndex = opponentBrawlerInedx;
                }
            } else if (!yourCurBrawler.isAlive()) { //for client (battle state 2)
                player1.pw.println(yourCurBrawler.getType().getName() + " was defeated!");
                yourBrawlerIndex++;
            } else if (!opCurBrawler.isAlive()) {   //for client (battle state 3)
                player1.pw.println(opCurBrawler.getType().getName() + " was defeated!");
                opponentBrawlerInedx++;
            } else if (yourCurBrawler.isAlive() && opCurBrawler.isAlive()) {   //for client (battle state 1)
                Ability yourMove = player1.pickMove(yourCurBrawler);
                Ability opponentMove = opponent.pickMove(opCurBrawler);
                attack(yourCurBrawler, yourMove, opCurBrawler, opponentMove);
                if (yourCurBrawler.isAlive()) {
                    player1.pw.println("1");
                    player1.pw.println(yourCurBrawler.getType().getName() + " has " + yourCurBrawler.getHealth() + " health.");
                } else {
                    player1.pw.println("0");
                    player1.pw.println("empty");
                }
            }
        }

    }

    private void attack(Brawler yourBrawler, Ability yourMove, Brawler opBrawler, Ability opMove) {
        int damage;
        if (yourBrawler.getType().getStats().getSpeed() > opBrawler.getType().getStats().getSpeed()) {   //you attack them first
            player1.pw.println(yourBrawler.getType().getName() + " used " + yourMove.getName() + "!");
            damage = getDamage(yourMove, yourBrawler, opBrawler);
            opBrawler.takeDamage(damage);
            player1.pw.println("It did " + damage + " damage!");

            if (opBrawler.isAlive()) {
                player1.pw.println("1");
                player1.pw.println(opBrawler.getType().getName() + " used " + opMove.getName() + "!");
                damage = getDamage(opMove, opBrawler, yourBrawler);
                yourBrawler.takeDamage(damage);
                player1.pw.println("It did " + damage + " damage!");
            } else {
                player1.pw.println("0");
            }
        } else if (yourBrawler.getType().getStats().getSpeed() < opBrawler.getType().getStats().getSpeed()) {  //they attack you first
            player1.pw.println(opBrawler.getType().getName() + " used " + opMove.getName() + "!");
            damage = getDamage(opMove, opBrawler, yourBrawler);
            yourBrawler.takeDamage(damage);
            player1.pw.println("It did " + damage + " damage!");

            if (yourBrawler.isAlive()) {
                player1.pw.println("1");
                player1.pw.println(yourBrawler.getType().getName() + " used " + yourMove.getName() + "!");
                damage = getDamage(yourMove, yourBrawler, opBrawler);
                opBrawler.takeDamage(damage);
                player1.pw.println("It did " + damage + " damage!");
            } else {
                player1.pw.println("0");
            }
        } else { //speed is the same and choose random order
            Random random = new Random();
            int choice = random.nextInt();
            choice = choice % 2;
            choice = Math.abs(choice);
            if (choice == 0) {  //you attack them first
                player1.pw.println(yourBrawler.getType().getName() + " used " + yourMove.getName() + "!");
                damage = getDamage(yourMove, yourBrawler, opBrawler);
                opBrawler.takeDamage(damage);
                player1.pw.println("It did " + damage + " damage!");

                if (opBrawler.isAlive()) {
                    player1.pw.println("1");
                    player1.pw.println(opBrawler.getType().getName() + " used " + opMove.getName() + "!");
                    damage = getDamage(opMove, opBrawler, yourBrawler);
                    yourBrawler.takeDamage(damage);
                    player1.pw.println("It did " + damage + " damage!");
                } else {
                    player1.pw.println("0");
                }
            } else if (choice == 1) {  //they attack you first
                player1.pw.println(opBrawler.getType().getName() + " used " + opMove.getName() + "!");
                damage = getDamage(opMove, opBrawler, yourBrawler);
                yourBrawler.takeDamage(damage);
                player1.pw.println("It did " + damage + " damage!");

                if (yourBrawler.isAlive()) {
                    player1.pw.println("1");
                    player1.pw.println(yourBrawler.getType().getName() + " used " + yourMove.getName() + "!");
                    damage = getDamage(yourMove, yourBrawler, opBrawler);
                    opBrawler.takeDamage(damage);
                    player1.pw.println("It did " + damage + " damage!");
                } else {
                    player1.pw.println("0");
                }
            }
        }

    }

    private int getDamage(Ability attackingMove, Brawler attackingBrawler, Brawler receivingBrawler) {
        double attackStat = attackingBrawler.getType().getStats().getAttack();
        double abilDamage = attackingMove.getDamage();
        double opDefence = receivingBrawler.getType().getStats().getDefense();
        double effectMult = getEffectivness(attackingMove, receivingBrawler);
        double damage = (attackStat * (abilDamage / opDefence)) / 5 * (effectMult);
        return (int) damage;
    }

    private double getEffectivness(Ability move, Brawler enimy) {
        CircularArrayList<String> damageMult = new CircularArrayList<>();
        damageMult.addAll(Arrays.asList("water", "fire", "air", "earth", "lightning"));
        try {
            for (int i = 0; i <= damageMult.size(); i++) {
                int a = i;
                int b = i;
                if (damageMult.get(i).equals(move.getType())) {
                    if (enimy.getType().getType().equals(damageMult.get(++a))) {
                        player1.pw.println("1");
                        player1.pw.println("It was super effective!");
                        return 2;
                    } else if (enimy.getType().getType().equals(damageMult.get(--b))) {
                        player1.pw.println("1");
                        player1.pw.println("Not Very Effective.");
                        return .5;
                    } else {
                        player1.pw.println("2");
                        return 1;
                    }
                }
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        return -1;
    }


}