package UserList;

import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Arrays;

import User.*;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;

@WebListener
public class UserList implements ServletContextListener {
    private static UserList instance;

    public static UserList getInstance(){
        return instance;
    }

    private static String filePath;

    public UserList(){}

    @Override
    public void contextInitialized(ServletContextEvent sce) {
        ServletContext context = sce.getServletContext();
        try {
            filePath = context.getResource("/WEB-INF/test.json").getFile();
            instance = new UserList(filePath);
        }catch (Exception ex){
            ex.getStackTrace();
        }
    }

    @Override
    public void contextDestroyed(ServletContextEvent sce) {

    }

    private UserList(String resource){
        try {
            InputStream jsonData = new FileInputStream(resource);
            ObjectMapper mapper = new ObjectMapper();
            UserList userList = mapper.readValue(jsonData, UserList.class);
            this.userList = userList.getUsers();
        }catch (Exception ex){
            System.out.println(Arrays.toString(ex.getStackTrace()));
        }
    }

    private ArrayList<User> userList;

    public ArrayList<User> getUsers() {
        return this.userList;
    }

    public void setUsers(ArrayList<User> Users){
        this.userList = Users;
    }

    public void addNewUser(User newUser){
        userList.add(newUser);
        this.save();

    }

    public void follow(User currentUser, String username){
        for(User temp : userList){
            if(temp.getUsername().equals(username)){
                currentUser.follow(temp);
                temp.gainFollower(currentUser);
                this.save();
            }
        }
    }

    public void unfollow(User currentUser, String username){
        for(User temp : userList){
            if(temp.getUsername().equals(username)){
                currentUser.unfollow(temp);
                temp.loseFollower(currentUser);
                this.save();
            }
        }
    }

    public void addATitle(User currentUser, String title, String type){
        currentUser.addToLib(title, type);
        this.save();

    }

    private void save(){
        try (OutputStream jsonData = new FileOutputStream(filePath)){
            ObjectMapper mapper = new ObjectMapper();
            mapper.writeValue(jsonData, this);
        }catch (Exception ex){
            System.out.println(Arrays.toString(ex.getStackTrace()));
        }
    }

}