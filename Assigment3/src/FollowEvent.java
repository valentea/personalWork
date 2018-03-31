import User.User;
import UserList.UserList;
import com.apple.eawt.AppEvent;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.List;

@WebServlet("/FollowEvent")
public class FollowEvent extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String event = request.getParameter("followButton");
        String username = request.getParameter("username");
        UserList userList = UserList.getInstance();

        HttpSession session = request.getSession();
        User currentUser = (User) session.getAttribute("currentUserObject");

        if(event.equals("Follow")){
            userList.follow(currentUser, username);
        }else if(event.equals("Unfollow")){
            userList.unfollow(currentUser, username);

        }

    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }
}
