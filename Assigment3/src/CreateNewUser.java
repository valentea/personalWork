import User.*;
import UserList.*;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.sun.tools.internal.xjc.reader.xmlschema.bindinfo.BIConversion;
import javafx.util.Pair;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@WebServlet("/CreateNewUser")
public class CreateNewUser extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {



    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        ServletContext context = getServletContext();

        String username = request.getParameter("newUsername");
        String password = request.getParameter("newPassword");
        String imageURL = request.getParameter("newImageURL");
        UserList userDB = UserList.getInstance();
        List<User> userList = userDB.getUsers();
        boolean badEntry = false;
        Map<String, Object> errorMap = new HashMap<>();


        if(username.equals("")){
            errorMap.put("usernameBool",true);
            badEntry = true;
        }
        if(password.equals("")){
            errorMap.put("passwordBool",true);
            badEntry = true;
        }
        if(imageURL.equals("")){
            errorMap.put("imageURLBool",true);
            badEntry = true;
        }
        if(!username.equals("")){
            for(User temp : userList){
                if(temp.getUsername().toLowerCase().equals(username.toLowerCase())){
                    errorMap.put("usernameTakenBool", true);
                    badEntry = true;
                }
            }
        }
        if(!badEntry) {
            User newUser = new User(username, password, imageURL);
            userDB.addNewUser(newUser);
            HttpSession session = request.getSession();
            session.setAttribute("currentImage", newUser.getImageURL());
            session.setAttribute("currentUsername", newUser.getUsername());
            session.setAttribute("loggedIn", true);
            ObjectMapper outputMapper = new ObjectMapper();
            String currUserJsonString = outputMapper.writeValueAsString(newUser);
            session.setAttribute("currentUserObject", currUserJsonString);
        }
        System.out.println(badEntry);
        errorMap.put("valid", badEntry);

        ObjectMapper mapper = new ObjectMapper();
        response.setContentType("application/json");
        OutputStream output =  response.getOutputStream();
        mapper.writeValue(output, errorMap);
        output.flush();
    }
}
