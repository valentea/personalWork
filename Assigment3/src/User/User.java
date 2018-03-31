package User;

import UserLib.*;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.util.ArrayList;


public class User {
    public User(){}

    public User(String newUsername, String newPassword, String newImageURL){
        this.setUsername(newUsername);
        this.setPassword(newPassword);
        this.setImageURL(newImageURL);
    }
    private String username;

    public String getUsername() {
        return this.username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    private String password;

    public String getPassword() {
        return this.password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    private String imageURL;

    public String getImageURL() {
        return this.imageURL;
    }

    public void setImageURL(String imageURL) {
        this.imageURL = imageURL;
    }

    private ArrayList<String> followers;

    public ArrayList<String> getFollowers() {
        return this.followers;
    }

    public void setFollowers(ArrayList<String> followers) {
        this.followers = followers;
    }

    public void gainFollower(User temp){
        followers.add(temp.getUsername());
    }

    public void loseFollower(User temp){
        followers.remove(temp.getUsername());
    }

    private ArrayList<String> following;

    public ArrayList<String> getFollowing() {
        return this.following;
    }

    public void setFollowing(ArrayList<String> following) {
        this.following = following;
    }

    public void follow(User temp){
        following.add(temp.getUsername());
    }

    public void unfollow(User temp){
        following.remove(temp.getUsername());
    }

    private UserLib library;

    public void addToLib(String title, String Type){
        this.library.addBook(title, Type);
    }

    public UserLib getLibrary() {
        return this.library;
    }

    public void setLibrary(UserLib library) {
        this.library = library;
    }

    public String asJson(){
        ObjectMapper outputMapper = new ObjectMapper();
        try {
            String currUserJsonString = outputMapper.writeValueAsString(this);
            return currUserJsonString;
        }catch (Exception ex){
            ex.printStackTrace();
            return "";
        }
    }
}