import com.sun.org.apache.bcel.internal.generic.BREAKPOINT;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.nio.channels.SocketChannel;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import static java.lang.Math.abs;

public class Player {
    private List<Brawler> chosenBrawlers;
    private boolean human;
    private Socket s;


    public PrintWriter pw;
    public BufferedReader br;


    public List<Brawler> getChosenBrawlers(){
        return this.chosenBrawlers;
    }

    public Socket getSocket() {
        return s;
    }

    Player(Socket s, boolean human) {
        this.human = human;
        this.s = s;
        try {
            this.br = new BufferedReader(new InputStreamReader(s.getInputStream()));
            this.pw = new PrintWriter(s.getOutputStream(), true);
        }catch (Exception ex){
            throw new RuntimeException(ex);
        }
    }

    public void selectBrawlers(BrawlerTypes brawlerTypes) {
        if(human) {
            pw.println("Choose 3 Brawlers:");
            while (true) {
                try {
                    int i = 1;
                    String output = "";
                    for (BrawlerType temp : brawlerTypes.getTypes()) {
                        output += (i + ")" + temp.getName() + ",");
                        i++;
                    }
                    pw.println(output);
                    String posSpaceChoice = br.readLine();
                    System.out.println(posSpaceChoice + " from client");
                    String choice = posSpaceChoice.replace(", ", ",");
                    List<Integer> list = Stream.of(choice.split(",")).map(Integer::parseInt).collect(Collectors.toList());
                    boolean badSelection = false;
                    for (int test : list) {
                        if (test > brawlerTypes.getTypes().size()) {
                            badSelection = true;
                        }
                    }
                    Set<Integer> testSet = new HashSet();
                    for (Integer myInt : list) {
                        if (!testSet.add(myInt)) {
                            badSelection = true;
                        }
                    }
                    chosenBrawlers = getBrawlers(list, badSelection, brawlerTypes);
                    if (chosenBrawlers != null) {
                        break;
                    }
                }catch (Exception ex){
                    ex.printStackTrace();
                }
            }
        }else{
            while(true) {
                ArrayList<BrawlerType> choiceList = new ArrayList<>();
                Random randomChoice = new Random();
                ArrayList<Integer> list = new ArrayList<>();
                for (int i = 0; i < 3; i++) {
                    int randomeInt = randomChoice.nextInt();
                    randomeInt = abs(randomeInt % brawlerTypes.getTypes().size());
                    randomeInt++;
                    list.add(randomeInt);
                }
                boolean badSelection = false;
                Set<Integer> testSet = new HashSet();
                for (Integer myInt : list) {
                    if (!testSet.add(myInt)) {
                        badSelection = true;
                    }
                }
                chosenBrawlers = getBrawlers(list, badSelection, brawlerTypes);
                if (chosenBrawlers != null){
                    break;
                }

            }
        }
    }

    private List<Brawler> getBrawlers(List<Integer> list, boolean badSelection, BrawlerTypes brawlerTypes) {
        if (list.size() == 3 && !badSelection) {
            if(human) {
                pw.println("0");
            }
            ArrayList<Brawler> chosenList = new ArrayList<>();
            for (int j : list) {
                Brawler temp = new Brawler(brawlerTypes.getTypes().get(j - 1));
                chosenList.add(temp);
            }
            return chosenList;
        } else {
            if(human) {
                pw.println("1");
            }
        }
        return null;
    }

    public Ability pickMove(Brawler currentBrawler){
        if(human){
            while(true) {
                try {
                    int size = currentBrawler.getType().getAbilities().size();
                    pw.println(Integer.toString(size));
                    pw.println("Choose a Move:");

                    int i = 1;
                    String output = "";
                    for (Ability temp : currentBrawler.getType().getAbilities()) {
                        output += (i + ") " + temp.getName() + ", " + temp.getType() + ", " + temp.getDamage()) + "||";
                        i++;
                    }
                    pw.println(output);
                    String stringMoveChoice = br.readLine();
                    int moveChoice = Integer.parseInt(stringMoveChoice);
                    return currentBrawler.getType().getAbilities().get(moveChoice);
                }catch (Exception ex){
                    ex.printStackTrace();
                }
            }
        }else{
            while(true) {
                Random randomMoveChoice = new Random();
                int choice = randomMoveChoice.nextInt();
                choice = choice % currentBrawler.getType().getAbilities().size();
                if(choice >=0 && choice < currentBrawler.getType().getAbilities().size()) {
                    return currentBrawler.getType().getAbilities().get(choice);
                }
            }
        }
    }
}

