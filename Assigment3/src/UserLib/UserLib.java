package UserLib;

import java.util.ArrayList;
import java.util.concurrent.ThreadPoolExecutor;

public class UserLib {
    private ArrayList<String> read;

    public ArrayList<String> getRead() {
        return this.read;
    }

    public void setRead(ArrayList<String> read) {
        this.read = read;
    }

    private ArrayList<String> favorite;

    public void addBook(String title, String Type){
        if (Type.equals("favorite")){
            favorite.add(title);
        }else if(Type.equals("read")){
            read.add(title);
        }
    }

    public ArrayList<String> getFavorite() {
        return this.favorite;
    }

    public void setFavorite(ArrayList<String> favorite) {
        this.favorite = favorite;
    }

    private ArrayList<String> totalLib;
}